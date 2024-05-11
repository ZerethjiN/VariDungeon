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

class TextBatchPipeline: public IGraphicsPipeline {
private:
    struct VertexPushConstant {
        glm::mat4 proj;
    };

    struct StorageBufferObject {
    public:
        StorageBufferObject(const std::array<SSBOVertex, 4>& newVertices, const glm::mat4& newModel, const glm::vec4& newColor, int newTextureIdx):
            vertices(newVertices),
            model(newModel),
            color(newColor),
            textureIdx(newTextureIdx) {
        }

    public:
        std::array<SSBOVertex, 4> vertices;
        glm::mat4 model;
        glm::vec4 color;
        int textureIdx;
        int padding1;
        int padding2;
        int padding3;
    };

public:
    TextBatchPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                .offset = 0,
                .size = sizeof(VertexPushConstant)
            }
        }),
        lastVertexStorageBufferSizes{0} {
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
                    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                    .descriptorCount = 65536,
                    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .pImmutableSamplers = nullptr
                }
            },
            // Flags
            {
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT,
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
            },
            0
        );
        createGraphicsPipeline(newRenderPass, "shaders/TextShaderVert.spv", "shaders/TextShaderFrag.spv");
        createDescriptorPool(0, {
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = static_cast<uint32_t>(vulkanEngine.MAX_FRAMES_IN_FLIGHT)
            },
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .descriptorCount = 65536 * static_cast<uint32_t>(vulkanEngine.MAX_FRAMES_IN_FLIGHT)
            }
        });
        createDescriptorSet(0);
    }

    ~TextBatchPipeline() {
        vkDeviceWaitIdle(vulkanEngine.device);

        for (std::uint32_t i = 0; i < VulkanEngine::MAX_FRAMES_IN_FLIGHT; i++) {
            if (lastVertexStorageBufferSizes[i] > 0) {
                vkDestroyBuffer(vulkanEngine.device, vertexStorageBuffers[i], nullptr);
                vkFreeMemory(vulkanEngine.device, vertexStorageBuffersMemory[i], nullptr);
            }
        }
    }

public:
    void beginText(std::size_t newNbSprites) {
        sprites[vulkanEngine.getCurFrame()].clear();
        sprites[vulkanEngine.getCurFrame()].reserve(newNbSprites);
        textures[vulkanEngine.getCurFrame()].clear();
        textureHashs[vulkanEngine.getCurFrame()].clear();
    }

    void addText(Text& ui, Transform& transform) {
        ui.updateVertices();
        int i = 0;
        for (const auto* texture: ui.textures) {
            if (texture != nullptr) {
                std::uint32_t textureIdx = 0;
                if (auto textureHashsIt = textureHashs[vulkanEngine.getCurFrame()].find(texture->textureImage); textureHashsIt != textureHashs[vulkanEngine.getCurFrame()].end()) {
                    textureIdx = textureHashsIt->second;
                } else {
                    textureIdx = textures[vulkanEngine.getCurFrame()].size();
                    textureHashs[vulkanEngine.getCurFrame()].emplace(
                        texture->textureImage,
                        textureIdx
                    );
                    textures[vulkanEngine.getCurFrame()].emplace_back(
                        texture
                    );
                }

                sprites[vulkanEngine.getCurFrame()].emplace_back(
                    std::array<SSBOVertex, 4>{
                        ui.vertices[i * 4 + 0],
                        ui.vertices[i * 4 + 1],
                        ui.vertices[i * 4 + 2],
                        ui.vertices[i * 4 + 3]
                    },
                    transform.getModel(),
                    ui.color / 255.f,
                    textureIdx
                );
            }
            i++;
        }
    }

    void addView(const glm::mat4& view) {
        vertexPushConstant[engine.getCurFrame()] = {
            .proj = view
        };
    }

    void endText() {
        if (sprites[vulkanEngine.getCurFrame()].size() > lastVertexStorageBufferSizes[vulkanEngine.currentFrame]) {
            if (lastVertexStorageBufferSizes[vulkanEngine.currentFrame] > 0) {
                vkDestroyBuffer(vulkanEngine.device, vertexStorageBuffers[vulkanEngine.currentFrame], nullptr);
                vkFreeMemory(vulkanEngine.device, vertexStorageBuffersMemory[vulkanEngine.currentFrame], nullptr);
            }

            VkDeviceSize bufferSize = sprites[vulkanEngine.getCurFrame()].size() * sizeof(StorageBufferObject);

            createBuffer(vulkanEngine.physicalDevice, vulkanEngine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexStorageBuffers[vulkanEngine.currentFrame], vertexStorageBuffersMemory[vulkanEngine.currentFrame]);

            vkMapMemory(vulkanEngine.device, vertexStorageBuffersMemory[vulkanEngine.currentFrame], 0, bufferSize, 0, &vertexStorageBuffersMapped[vulkanEngine.currentFrame]);
        
            lastVertexStorageBufferSizes[engine.getCurFrame()] = sprites[engine.getCurFrame()].size();
        } 

        memcpy(vertexStorageBuffersMapped[vulkanEngine.currentFrame], sprites[vulkanEngine.getCurFrame()].data(), sprites[vulkanEngine.getCurFrame()].size() * sizeof(StorageBufferObject));
    }

    void updateDescriptorSets() {
        VkDescriptorBufferInfo storageInfoVertex {
            .buffer = vertexStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(StorageBufferObject) * sprites[engine.getCurFrame()].size()
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

        for (std::uint32_t i = 0; i < imageInfos.size(); i++) {
            descriptorWrites.emplace_back(VkWriteDescriptorSet {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext = nullptr,
                .dstSet = descriptorSets[0][engine.getCurFrame()],
                .dstBinding = 1,
                .dstArrayElement = i,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .pImageInfo = &imageInfos[i],
                .pBufferInfo = nullptr,
                .pTexelBufferView = nullptr
            });
        }

        vkUpdateDescriptorSets(vulkanEngine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void draw() {
        vkCmdBindPipeline(vulkanEngine.commandBuffers[vulkanEngine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
        vkCmdBindDescriptorSets(vulkanEngine.commandBuffers[vulkanEngine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[0][vulkanEngine.getCurFrame()], 0, nullptr);
        updateDescriptorSets();
        vkCmdDraw(vulkanEngine.commandBuffers[vulkanEngine.getCurFrame()], 4, sprites[vulkanEngine.getCurFrame()].size(), 0, 0);
    }

public:
    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastVertexStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMapped;

public:
    std::array<std::vector<StorageBufferObject>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> sprites;
    std::array<std::vector<const Texture*>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textures;
    std::array<std::unordered_map<VkImage, std::size_t>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textureHashs;
    std::array<VertexPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexPushConstant;
};