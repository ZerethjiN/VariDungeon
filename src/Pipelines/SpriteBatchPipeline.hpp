#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include <unordered_map>

#include <Zerengine.hpp>

class SpriteBatchPipeline: public IGraphicsPipeline {
private:
    struct VertexPushConstant {
        glm::mat4 proj;
    };

    struct FragmentPushConstant {
        glm::vec4 ambientColor;
        int nbLights;
    };

    struct StorageBufferObject {
    public:
        StorageBufferObject(const std::array<SSBOVertex, 4>& newVertices, const glm::mat4& newModel, const glm::vec4& newColor, int newTextureIdx, int newIsUnlit):
            vertices(newVertices),
            model(newModel),
            color(newColor),
            textureIdx(newTextureIdx),
            isUnlit(newIsUnlit) {
        }

    public:
        std::array<SSBOVertex, 4> vertices;
        glm::mat4 model;
        glm::vec4 color;
        int textureIdx;
        int isUnlit;
        int padding2;
        int padding3;
    };

    struct SSBOLight {
    public:
        SSBOLight(const glm::vec2& newPos, float newRadius, float newIntensity, const glm::vec4& newColor):
            pos(newPos),
            radius(newRadius),
            intensity(newIntensity),
            color(newColor) {
        }

    public:
        glm::vec2 pos;
        float radius;
        float intensity;
        glm::vec4 color;
    };

public:
    SpriteBatchPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                .offset = 0,
                .size = sizeof(VertexPushConstant)
            },
            {
                .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                .offset = sizeof(VertexPushConstant),
                .size = sizeof(FragmentPushConstant)
            }
        }),
        lastVertexStorageBufferSizes{0},
        lastFragmentStorageBufferSizes{0} {
        createDescriptorSetLayout(
            // Bindings
            {
                VkDescriptorSetLayoutBinding {
                    .binding = 0,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .descriptorCount = 1,
                    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                    .pImmutableSamplers = nullptr
                },
                VkDescriptorSetLayoutBinding {
                    .binding = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .descriptorCount = 1,
                    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .pImmutableSamplers = nullptr
                },
                VkDescriptorSetLayoutBinding {
                    .binding = 2,
                    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                    .descriptorCount = 65536,
                    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .pImmutableSamplers = nullptr
                }
            },
            // Flags
            {
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT,
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT,
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
            },
            // Set Index
            0
        );
        createGraphicsPipeline(newRenderPass, "shaders/InGameShaderVert.spv", "shaders/InGameShaderFrag.spv");
        createDescriptorPool(0, {
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            },
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            },
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .descriptorCount = 65536 * static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            }
        });
        createDescriptorSet(0);
    }

    ~SpriteBatchPipeline() {
        vkDeviceWaitIdle(engine.device);

        for (std::uint32_t i = 0; i < VulkanEngine::MAX_FRAMES_IN_FLIGHT; i++) {
            if (lastVertexStorageBufferSizes[i] > 0) {
                vkDestroyBuffer(engine.device, vertexStorageBuffers[i], nullptr);
                vkFreeMemory(engine.device, vertexStorageBuffersMemory[i], nullptr);
            }

            if (lastFragmentStorageBufferSizes[i] > 0) {
                vkDestroyBuffer(engine.device, fragmentStorageBuffers[i], nullptr);
                vkFreeMemory(engine.device, fragmentStorageBuffersMemory[i], nullptr);
            }
        }
    }

public:
    void beginLight(std::size_t newNbLights) {
        lights[engine.getCurFrame()].clear();
        lights[engine.getCurFrame()].reserve(newNbLights);
    }

    void addLight(const PointLight& light, const Transform& transform) {
        lights[engine.getCurFrame()].emplace_back(
            transform.getPosition(),
            light.radius,
            light.intensity,
            light.color / 255.f
        );
    }

    void beginSprite(std::size_t newNbSprites) {
        sprites[engine.getCurFrame()].clear();
        sprites[engine.getCurFrame()].reserve(newNbSprites);
        textures[engine.getCurFrame()].clear();
        textureHashs[engine.getCurFrame()].clear();
    }

    void addSprite(const Sprite& sprite, Transform& transform) {
        std::uint32_t textureIdx = 0;
        if (auto textureHashsIt = textureHashs[engine.getCurFrame()].find(sprite.texture.textureImage); textureHashsIt != textureHashs[vulkanEngine.getCurFrame()].end()) {
            textureIdx = textureHashsIt->second;
        } else {
            textureIdx = textures[engine.getCurFrame()].size();
            textureHashs[engine.getCurFrame()].emplace(
                sprite.texture.textureImage,
                textureIdx
            );
            textures[engine.getCurFrame()].emplace_back(
                &sprite.texture
            );
        }
        sprites[engine.getCurFrame()].emplace_back(
            sprite.vertices,
            transform.getModel(),
            sprite.color / 255.f,
            textureIdx,
            0
        );
    }

    void addTileMap(const TileMap& tileMap, Transform& transform) {
        std::uint32_t textureIdx = 0;
        if (auto textureHashsIt = textureHashs[engine.getCurFrame()].find(tileMap.texture.textureImage); textureHashsIt != textureHashs[vulkanEngine.getCurFrame()].end()) {
            textureIdx = textureHashsIt->second;
        } else {
            textureIdx = textures[engine.getCurFrame()].size();
            textureHashs[engine.getCurFrame()].emplace(
                tileMap.texture.textureImage,
                textureIdx
            );
            textures[engine.getCurFrame()].emplace_back(
                &tileMap.texture
            );
        }
        for (const auto& quad: tileMap.vertices) {
            sprites[engine.getCurFrame()].emplace_back(
                quad,
                transform.getModel(),
                tileMap.color / 255.f,
                textureIdx,
                0
            );
        }
    }

    void addView(const glm::mat4& view) {
        vertexPushConstant[engine.getCurFrame()] = {
            .proj = view
        };
    }

    void addAmbientColor(const glm::vec4& newAmbientColor) {
        fragmentPushConstant[engine.getCurFrame()] = {
            .ambientColor = newAmbientColor / 255.f,
            .nbLights = static_cast<int>(lights[engine.getCurFrame()].size())
        };
    }

    void end() {
        if (sprites[engine.getCurFrame()].size() > lastVertexStorageBufferSizes[engine.getCurFrame()]) {
            if (lastVertexStorageBufferSizes[engine.getCurFrame()] > 0) {
                vkDestroyBuffer(engine.device, vertexStorageBuffers[engine.getCurFrame()], nullptr);
                vkFreeMemory(engine.device, vertexStorageBuffersMemory[engine.getCurFrame()], nullptr);
            }

            VkDeviceSize bufferSize = sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject);

            createBuffer(engine.physicalDevice, engine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexStorageBuffers[vulkanEngine.getCurFrame()], vertexStorageBuffersMemory[vulkanEngine.getCurFrame()]);
            
            vkMapMemory(engine.device, vertexStorageBuffersMemory[engine.getCurFrame()], 0, sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject), 0, &vertexStorageBuffersMapped[vulkanEngine.getCurFrame()]);

            lastVertexStorageBufferSizes[engine.getCurFrame()] = sprites[engine.getCurFrame()].size();
        }

        memcpy(vertexStorageBuffersMapped[engine.getCurFrame()], sprites[engine.getCurFrame()].data(), sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject));

        if (lights[engine.getCurFrame()].size() > lastFragmentStorageBufferSizes[engine.getCurFrame()]) {
            if (lastFragmentStorageBufferSizes[engine.getCurFrame()] > 0) {
                vkDestroyBuffer(engine.device, fragmentStorageBuffers[engine.getCurFrame()], nullptr);
                vkFreeMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], nullptr);
            }

            VkDeviceSize bufferSize = lights[engine.getCurFrame()].size() * sizeof(SSBOLight);

            createBuffer(engine.physicalDevice, engine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, fragmentStorageBuffers[vulkanEngine.getCurFrame()], fragmentStorageBuffersMemory[vulkanEngine.getCurFrame()]);

            vkMapMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], 0, lights[engine.getCurFrame()].size() * sizeof(SSBOLight), 0, &fragmentStorageBuffersMapped[vulkanEngine.getCurFrame()]);
        
            lastFragmentStorageBufferSizes[engine.getCurFrame()] = lights[engine.getCurFrame()].size();
        }

        memcpy(fragmentStorageBuffersMapped[engine.getCurFrame()], lights[engine.getCurFrame()].data(), lights[engine.getCurFrame()].size() * sizeof(SSBOLight));
    }

    void updateDescriptorSets() {
        VkDescriptorBufferInfo storageInfoVertex {
            .buffer = vertexStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(StorageBufferObject) * sprites[engine.getCurFrame()].size()
        };

        VkDescriptorBufferInfo storageInfoFragment {
            .buffer = fragmentStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(SSBOLight) * lights[engine.getCurFrame()].size()
        };

        std::vector<VkDescriptorImageInfo> imageInfos;
        imageInfos.reserve(textures[engine.getCurFrame()].size());

        for (const auto* texture: textures[engine.getCurFrame()]) {
            imageInfos.emplace_back(VkDescriptorImageInfo {
                .sampler = texture->textureSampler,
                .imageView = texture->textureImageView,
                .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            });
        }

        std::vector<VkWriteDescriptorSet> descriptorWrites;

        if (sprites[engine.getCurFrame()].size() > 0) {
            descriptorWrites.emplace_back(
                VkWriteDescriptorSet {
                    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                    .pNext = nullptr,
                    .dstSet = descriptorSets[0][engine.getCurFrame()],
                    .dstBinding = 0,
                    .dstArrayElement = 0,
                    .descriptorCount = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .pImageInfo = nullptr,
                    .pBufferInfo = &storageInfoVertex,
                    .pTexelBufferView = nullptr
                }
            );
        }

        if (lights[engine.getCurFrame()].size() > 0) {
            descriptorWrites.emplace_back(
                VkWriteDescriptorSet {
                    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                    .pNext = nullptr,
                    .dstSet = descriptorSets[0][engine.getCurFrame()],
                    .dstBinding = 1,
                    .dstArrayElement = 0,
                    .descriptorCount = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .pImageInfo = nullptr,
                    .pBufferInfo = &storageInfoFragment,
                    .pTexelBufferView = nullptr
                }
            );
        }

        for (std::uint32_t i = 0; i < imageInfos.size(); i++) {
            descriptorWrites.emplace_back(VkWriteDescriptorSet {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext = nullptr,
                .dstSet = descriptorSets[0][engine.getCurFrame()],
                .dstBinding = 2,
                .dstArrayElement = i,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .pImageInfo = &imageInfos[i],
                .pBufferInfo = nullptr,
                .pTexelBufferView = nullptr
            });
        }

        vkUpdateDescriptorSets(engine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void updatePushConstants() {
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(VertexPushConstant), &vertexPushConstant[vulkanEngine.getCurFrame()]);
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(VertexPushConstant), sizeof(FragmentPushConstant), &fragmentPushConstant[vulkanEngine.getCurFrame()]);
    }

    void draw() {
        vkCmdBindPipeline(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
        vkCmdBindDescriptorSets(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[0][vulkanEngine.getCurFrame()], 0, nullptr);
        updateDescriptorSets();
        updatePushConstants();
        vkCmdDraw(engine.commandBuffers[engine.getCurFrame()], 4, sprites[engine.getCurFrame()].size(), 0, 0);
    }

private:
    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastVertexStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMapped;

    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastFragmentStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMapped;

    std::array<std::vector<StorageBufferObject>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> sprites;
    std::array<std::vector<const Texture*>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textures;
    std::array<std::unordered_map<VkImage, std::size_t>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textureHashs;
    std::array<std::vector<SSBOLight>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lights;
    std::array<VertexPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexPushConstant;
    std::array<FragmentPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentPushConstant;
};