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
#include <Comps.hpp>

class AberationPipeline: public IGraphicsPipeline {
private:
    struct FragmentPushConstant {
        glm::ivec2 screenSize;
        glm::vec2 aberationDirection;
        float aberationOffset;
        float _padding1;
    };

    struct VertexPushConstant {
        glm::mat4 proj;
        glm::vec2 cameraPos;
    };

public:
    AberationPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
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
        }) {
        createDescriptorSetLayout(
            // Bindings
            {
                // Images
                VkDescriptorSetLayoutBinding {
                    .binding = 0,
                    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                    .descriptorCount = 1,
                    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
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
        createGraphicsPipeline(newRenderPass, "shaders/AberationShaderVert.spv", "shaders/AberationShaderFrag.spv");
        createDescriptorPool(0, {
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            },
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            }
        });
        createDescriptorSet(0);
    }

public:
    void addView(const glm::mat4& view, const glm::vec2& cameraPos) {
        vertexPushConstant[engine.getCurFrame()] = {
            .proj = view,
            .cameraPos = cameraPos
        };
    }

    void updateFragmentPushConstant(const glm::ivec2& screenSize, float aberationOffset, const glm::vec2& aberationDirection) {
        fragmentPushConstant[engine.getCurFrame()] = {
            .screenSize = screenSize,
            .aberationDirection = aberationDirection,
            .aberationOffset = aberationOffset
        };
    }

    void updateTexture(VkSampler newSampler, VkImageView newImageView) {
        textures[engine.getCurFrame()] = {
            newSampler,
            newImageView
        };
    }

    void draw() {
        vkCmdBindPipeline(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
        vkCmdBindDescriptorSets(engine.commandBuffers[engine.getCurFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[0][vulkanEngine.getCurFrame()], 0, nullptr);
        updateDescriptorSets();
        updatePushConstants();
        vkCmdDraw(engine.commandBuffers[engine.getCurFrame()], 4, 1, 0, 0);
    }

private:
    void updateDescriptorSets() {
        VkDescriptorImageInfo imageInfo {
            .sampler = std::get<0>(textures[engine.getCurFrame()]),
            .imageView = std::get<1>(textures[engine.getCurFrame()]),
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        };

        std::vector<VkWriteDescriptorSet> descriptorWrites;

        descriptorWrites.emplace_back(
            VkWriteDescriptorSet {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext = nullptr,
                .dstSet = descriptorSets[0][engine.getCurFrame()],
                .dstBinding = 0,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .pImageInfo = &imageInfo,
                .pBufferInfo = nullptr,
                .pTexelBufferView = nullptr
            }
        );

        vkUpdateDescriptorSets(engine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void updatePushConstants() {
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(VertexPushConstant), &vertexPushConstant[vulkanEngine.getCurFrame()]);
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(VertexPushConstant), sizeof(FragmentPushConstant), &fragmentPushConstant[vulkanEngine.getCurFrame()]);
    }

public:
    std::array<std::tuple<VkSampler, VkImageView>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textures;
    std::array<FragmentPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentPushConstant;
    std::array<VertexPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> vertexPushConstant;
};