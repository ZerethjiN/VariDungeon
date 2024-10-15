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
#include <Comps.hpp>

class LightBatchPipeline: public IGraphicsPipeline {
private:
    struct VertexPushConstant {
        glm::mat4 proj;
    };

    struct SSBOLight {
    public:
        SSBOLight(const glm::mat4& newModel, const glm::vec2& newPos, float newRadius, float newIntensity, const glm::vec4& newColor):
            model(newModel),
            pos(newPos),
            radius(newRadius),
            intensity(newIntensity),
            color(newColor) {
        }

    public:
        glm::mat4 model;
        glm::vec2 pos;
        float radius;
        float intensity;
        glm::vec4 color;
    };

public:
    LightBatchPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                .offset = 0,
                .size = sizeof(VertexPushConstant)
            }
        }),
        lastFragmentStorageBufferSizes{0} {
        createDescriptorSetLayout(
            // Bindings
            {
                // Lights
                VkDescriptorSetLayoutBinding {
                    .binding = 0,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .descriptorCount = 1,
                    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                    .pImmutableSamplers = nullptr
                },
            },
            // Flags
            {
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
        createGraphicsPipeline(newRenderPass, "shaders/LightBatchShaderVert.spv", "shaders/LightBatchShaderFrag.spv", 1, colorBlendAttachements, 1);
        createDescriptorPool(0, {
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            }
        });
        createDescriptorSet(0);
    }

    ~LightBatchPipeline() {
        vkDeviceWaitIdle(engine.device);

        for (std::uint32_t i = 0; i < VulkanEngine::MAX_FRAMES_IN_FLIGHT; i++) {
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

    void addLight(const PointLight& light, Transform2D& transform) {
        lights[engine.getCurFrame()].emplace_back(
            transform.getModel(),
            transform.getPosition(),
            light.radius,
            light.intensity,
            light.color / 255.f
        );
    }

    void addView(const glm::mat4& view) {
        vertexPushConstant[engine.getCurFrame()] = {
            .proj = view
        };
    }

    void end() {
        if (lights[engine.getCurFrame()].size() * sizeof(SSBOLight) > lastFragmentStorageBufferSizes[engine.getCurFrame()]) {
            if (lastFragmentStorageBufferSizes[engine.getCurFrame()] > 0) {
                vkUnmapMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()]);
                vkDestroyBuffer(engine.device, fragmentStorageBuffers[engine.getCurFrame()], nullptr);
                vkFreeMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], nullptr);
            }

            VkDeviceSize bufferSize = std::bit_ceil(lights[engine.getCurFrame()].size() * sizeof(SSBOLight));

            createBuffer(engine.physicalDevice, engine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, fragmentStorageBuffers[vulkanEngine.getCurFrame()], fragmentStorageBuffersMemory[vulkanEngine.getCurFrame()]);

            vkMapMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], 0, bufferSize, 0, &fragmentStorageBuffersMapped[vulkanEngine.getCurFrame()]);
        
            lastFragmentStorageBufferSizes[engine.getCurFrame()] = bufferSize;
        }

        memcpy(fragmentStorageBuffersMapped[engine.getCurFrame()], lights[engine.getCurFrame()].data(), lights[engine.getCurFrame()].size() * sizeof(SSBOLight));
    }

    void draw() {
        if (lights[engine.getCurFrame()].size() > 0) {
            vkCmdBindPipeline(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
            vkCmdBindDescriptorSets(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[0][vulkanEngine.getCurFrame()], 0, nullptr);
            updateDescriptorSets();
            updatePushConstants();
            vkCmdDraw(engine.commandBuffers[engine.getCurFrame()], 4, lights[engine.getCurFrame()].size(), 0, 0);
        }
    }

private:
    void updateDescriptorSets() {
        VkDescriptorBufferInfo storageInfoVertex {
            .buffer = fragmentStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(SSBOLight) * lights[engine.getCurFrame()].size()
        };

        std::vector<VkWriteDescriptorSet> descriptorWrites;

        if (lights[engine.getCurFrame()].size() > 0) {
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

        vkUpdateDescriptorSets(engine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void updatePushConstants() {
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(VertexPushConstant), &vertexPushConstant[vulkanEngine.getCurFrame()]);
    }

public:
    std::array<VertexPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexPushConstant;

    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastFragmentStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMapped;

    std::array<std::vector<SSBOLight>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lights;
};