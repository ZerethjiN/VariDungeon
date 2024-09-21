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
        float seed;
    };

public:
    AberationPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                .offset = 0,
                .size = sizeof(FragmentPushConstant)
            }
        }) {
        createDescriptorSetLayout(
            // Bindings
            {
                // Background Image
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
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT,
            },
            // Set Index
            0
        );
        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachements {
            VkPipelineColorBlendAttachmentState {
                .blendEnable = VK_FALSE,//VK_TRUE,
                .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                .colorBlendOp = VK_BLEND_OP_ADD,
                .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                .alphaBlendOp = VK_BLEND_OP_ADD,
                .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
            }
        };
        createGraphicsPipeline(newRenderPass, "shaders/AberationShaderVert.spv", "shaders/AberationShaderFrag.spv", 1, colorBlendAttachements, 0);
        createDescriptorPool(0, {
            VkDescriptorPoolSize {
                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .descriptorCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT)
            }
        });
        createDescriptorSet(0);
    }

    ~AberationPipeline() {
        vkDeviceWaitIdle(engine.device);
    }

public:
    void updateFragmentPushConstant(const glm::ivec2& screenSize, const glm::vec2& aberationDirection, float aberationOffset, float newSeed) {
        fragmentPushConstant[engine.getCurFrame()] = {
            .screenSize = screenSize,
            .aberationDirection = aberationDirection,
            .aberationOffset = aberationOffset,
            .seed = newSeed
        };
    }

    void updateTexture(VkSampler newSampler, VkImageView newBackgroundView) {
        textures[engine.getCurFrame()] = {
            newSampler,
            newBackgroundView
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
        VkDescriptorImageInfo imageColorInfo {
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
                .pImageInfo = &imageColorInfo,
                .pBufferInfo = nullptr,
                .pTexelBufferView = nullptr
            }
        );

        vkUpdateDescriptorSets(engine.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    void updatePushConstants() {
        vkCmdPushConstants(engine.commandBuffers[engine.getCurFrame()], pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FragmentPushConstant), &fragmentPushConstant[vulkanEngine.getCurFrame()]);
    }

public:
    std::array<std::tuple<VkSampler, VkImageView>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> textures;
    std::array<FragmentPushConstant, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentPushConstant;
};