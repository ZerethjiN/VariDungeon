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
#include <bit>

#include <Zerengine.hpp>

class UIBatchPipeline: public IGraphicsPipeline {
private:
    struct VertexPushConstant {
        glm::mat4 proj;
    };

    struct StorageBufferObject {
    public:
        StorageBufferObject(const std::array<SSBOVertex, 4>& newVertices, const glm::mat4& newModel, const glm::vec4& newColor, int newTextureIdx, int newIsText):
            vertices(newVertices),
            model(newModel),
            color(newColor),
            textureIdx(newTextureIdx),
            isText(newIsText) {
        }

    public:
        std::array<SSBOVertex, 4> vertices;
        glm::mat4 model;
        glm::vec4 color;
        int textureIdx;
        int isText;
        int padding2;
        int padding3;
    };

public:
    UIBatchPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                .offset = 0,
                .size = sizeof(VertexPushConstant)
            }
        }),
        lastVertexStorageBufferSizes{0},
        needRefreshTextures({
            std::pair(false, 0),
            std::pair(false, 0)
        }) {
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
            // Set Index
            0
        );
        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachements {
            VkPipelineColorBlendAttachmentState {
                .blendEnable = VK_TRUE,
                .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                .colorBlendOp = VK_BLEND_OP_ADD,
                .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                .alphaBlendOp = VK_BLEND_OP_ADD,
                .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
            }
        };
        createGraphicsPipeline(newRenderPass, "shaders/UIShaderVert.spv", "shaders/UIShaderFrag.spv", 1, colorBlendAttachements, 0);
        createDescriptorPool(0, {
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

    ~UIBatchPipeline() {
        vkDeviceWaitIdle(engine.device);

        for (std::uint32_t i = 0; i < VulkanEngine::MAX_FRAMES_IN_FLIGHT; i++) {
            if (lastVertexStorageBufferSizes[i] > 0) {
                vkDestroyBuffer(engine.device, vertexStorageBuffers[i], nullptr);
                vkFreeMemory(engine.device, vertexStorageBuffersMemory[i], nullptr);
            }
        }
    }

public:
    void beginUI() {
        sprites[engine.getCurFrame()].clear();
    }

    void addUI(const UI& ui, Transform2D& transform, const ZreView& view) {
        std::uint32_t textureIdx = 0;
        if (auto textureHashsIt = textureHashs.find(ui.texture->textureImage); textureHashsIt != textureHashs.end()) {
            textureIdx = textureHashsIt->second;
        } else {
            textureIdx = textures.size();
            textureHashs.emplace(
                ui.texture->textureImage,
                textureIdx
            );
            textures.emplace_back(
                ui.texture
            );
            for (auto& needRefreshPair: needRefreshTextures) {
                needRefreshPair.first = true;
            }
        }

        glm::mat4 newTrans = glm::mat4(1.0f);
        auto newCenter = transform.getPosition() + view.getCenter();

        switch (ui.anchor) {
            case UIAnchor::TOP_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::TOP_CENTER:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::TOP_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::CENTER_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y, 0));
                break;
            case UIAnchor::CENTER_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y, 0));
                break;
            case UIAnchor::BOTTOM_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::BOTTOM_CENTER:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::BOTTOM_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            default:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y, 0));
                break;
        }

        newTrans = glm::rotate(newTrans, glm::radians(transform.getRotation()), glm::vec3(0, 0, 1));
        newTrans = glm::scale(newTrans, glm::vec3(transform.getScale(), 0));

        sprites[engine.getCurFrame()].emplace_back(
            ui.vertices,
            newTrans,
            ui.color / 255.f,
            textureIdx,
            0
        );
    }

    void addTextUI(TextUI& ui, Transform2D& transform, const ZreView& view) {
        glm::mat4 newTrans = glm::mat4(1.0f);
        auto newCenter = transform.getPosition() + view.getCenter();

        switch (ui.anchor) {
            case UIAnchor::TOP_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::TOP_CENTER:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::TOP_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y - view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::CENTER_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y, 0));
                break;
            case UIAnchor::CENTER_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y, 0));
                break;
            case UIAnchor::BOTTOM_LEFT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x - view.getSize().x / 2.0f, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::BOTTOM_CENTER:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            case UIAnchor::BOTTOM_RIGHT:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x + view.getSize().x / 2.0f, newCenter.y + view.getSize().y / 2.0f, 0));
                break;
            default:
                newTrans = glm::translate(newTrans, glm::vec3(newCenter.x, newCenter.y, 0));
                break;
        }

        newTrans = glm::rotate(newTrans, glm::radians(transform.getRotation()), glm::vec3(0, 0, 1));
        newTrans = glm::scale(newTrans, glm::vec3(transform.getScale(), 0));

        ui.updateVertices();

        int i = 0;
        for (const auto& texture: ui.textures) {
            if (texture != nullptr) {
                std::uint32_t textureIdx = 0;
                if (auto textureHashsIt = textureHashs.find(texture->textureImage); textureHashsIt != textureHashs.end()) {
                    textureIdx = textureHashsIt->second;
                } else {
                    textureIdx = textures.size();
                    textureHashs.emplace(
                        texture->textureImage,
                        textureIdx
                    );
                    textures.emplace_back(
                        texture
                    );
                    for (auto& needRefreshPair: needRefreshTextures) {
                        needRefreshPair.first = true;
                    }
                }

                sprites[vulkanEngine.getCurFrame()].emplace_back(
                    std::array<SSBOVertex, 4>{
                        ui.vertices[i * 4 + 0],
                        ui.vertices[i * 4 + 1],
                        ui.vertices[i * 4 + 2],
                        ui.vertices[i * 4 + 3]
                    },
                    newTrans,
                    ui.color / 255.f,
                    textureIdx,
                    1
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

    void end() {
        if (sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject) > lastVertexStorageBufferSizes[engine.getCurFrame()]) {
            if (lastVertexStorageBufferSizes[engine.getCurFrame()] > 0) {
                vkUnmapMemory(engine.device, vertexStorageBuffersMemory[engine.getCurFrame()]);
                vkDestroyBuffer(engine.device, vertexStorageBuffers[engine.getCurFrame()], nullptr);
                vkFreeMemory(engine.device, vertexStorageBuffersMemory[engine.getCurFrame()], nullptr);
            }

            VkDeviceSize bufferSize = std::bit_ceil(sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject));

            createBuffer(engine.physicalDevice, engine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexStorageBuffers[engine.getCurFrame()], vertexStorageBuffersMemory[engine.getCurFrame()]);

            vkMapMemory(engine.device, vertexStorageBuffersMemory[engine.getCurFrame()], 0, bufferSize, 0, &vertexStorageBuffersMapped[engine.getCurFrame()]);
        
            lastVertexStorageBufferSizes[engine.getCurFrame()] = bufferSize;
        } 

        memcpy(vertexStorageBuffersMapped[engine.getCurFrame()], sprites[engine.getCurFrame()].data(), sprites[engine.getCurFrame()].size() * sizeof(StorageBufferObject));
    }

    void updateDescriptorSets() {
        std::vector<VkWriteDescriptorSet> descriptorWrites;

        VkDescriptorBufferInfo storageInfoVertex {
            .buffer = vertexStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(StorageBufferObject) * sprites[engine.getCurFrame()].size()
        };

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

        std::vector<VkDescriptorImageInfo> imageInfos;

        if (needRefreshTextures[engine.getCurFrame()].first) {
            imageInfos.reserve(textures.size() - needRefreshTextures[engine.getCurFrame()].second);

            for (std::size_t i = needRefreshTextures[engine.getCurFrame()].second; i < textures.size(); i++) {
                imageInfos.emplace_back(// VkDescriptorImageInfo
                    textures[i]->textureSampler,
                    textures[i]->textureImageView,
                    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
                );

                descriptorWrites.emplace_back(VkWriteDescriptorSet {
                    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                    .pNext = nullptr,
                    .dstSet = descriptorSets[0][engine.getCurFrame()],
                    .dstBinding = 1,
                    .dstArrayElement = static_cast<uint32_t>(i),
                    .descriptorCount = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                    .pImageInfo = &imageInfos[i - needRefreshTextures[engine.getCurFrame()].second],
                    .pBufferInfo = nullptr,
                    .pTexelBufferView = nullptr
                });
            }

            needRefreshTextures[engine.getCurFrame()] = std::pair(false, textures.size());
        }

        vkUpdateDescriptorSets(engine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void updatePushConstants() {
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(VertexPushConstant), &vertexPushConstant[vulkanEngine.getCurFrame()]);
    }

    void draw() {
        vkCmdBindPipeline(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
        vkCmdBindDescriptorSets(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[0][engine.getCurFrame()], 0, nullptr);
        updateDescriptorSets();
        updatePushConstants();
        vkCmdDraw(engine.commandBuffers[engine.getCurFrame()], 4, sprites[engine.getCurFrame()].size(), 0, 0);
    }

public:
    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastVertexStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexStorageBuffersMapped;

public:
    std::vector<std::shared_ptr<Texture>> textures;
    std::unordered_map<VkImage, std::size_t> textureHashs;

public:
    std::array<std::vector<StorageBufferObject>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> sprites;
    std::array<VertexPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexPushConstant;
    std::array<std::pair<bool, std::size_t>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> needRefreshTextures;
};