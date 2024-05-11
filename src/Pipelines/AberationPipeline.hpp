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
        float aberationOffset;
        int nbShockwaves;
    };

    struct VertexPushConstant {
        glm::mat4 proj;
        glm::vec2 cameraPos;
    };

    struct SSBOShockwave {
    public:
        SSBOShockwave(const glm::vec2& newPos, float newRadius, float newAmplitude, float newRefraction):
            pos(newPos),
            radius(newRadius),
            amplitude(newAmplitude),
            refraction(newRefraction) {
        }

    public:
        glm::vec2 pos;
        float radius;
        float amplitude;
        float refraction;
        float padding1;
        float padding2;
        float padding3;
    };

public:
    AberationPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass):
        IGraphicsPipeline(newEngine, newRenderPass, 1, {
            {
                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                .offset = 0,
                .size = sizeof(vertexPushConstant)
            },
            {
                .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                .offset = sizeof(vertexPushConstant),
                .size = sizeof(FragmentPushConstant)
            }
        }),
        lastFragmentStorageBufferSizes{0} {
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
                // Shockwaves
                VkDescriptorSetLayoutBinding {
                    .binding = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .descriptorCount = 1,
                    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .pImmutableSamplers = nullptr
                },
            },
            // Flags
            {
                VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT,
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

    ~AberationPipeline() {
        vkDeviceWaitIdle(engine.device);

        for (std::uint32_t i = 0; i < VulkanEngine::MAX_FRAMES_IN_FLIGHT; i++) {
            if (lastFragmentStorageBufferSizes[i] > 0) {
                vkDestroyBuffer(engine.device, fragmentStorageBuffers[i], nullptr);
                vkFreeMemory(engine.device, fragmentStorageBuffersMemory[i], nullptr);
            }
        }
    }

public:
    void beginShockwave(std::size_t newNbShockwaves) {
        shockwaves[engine.getCurFrame()].clear();
        shockwaves[engine.getCurFrame()].reserve(newNbShockwaves);
    }

    void addShockwave(const Shockwave& shockwave, const Transform& transform) {
        shockwaves[engine.getCurFrame()].emplace_back(
            transform.getPosition(),
            shockwave.radius,
            shockwave.amplitude,
            shockwave.refraction
        );
    }

    void addView(const glm::mat4& view, const glm::vec2& cameraPos) {
        vertexPushConstant[engine.getCurFrame()] = {
            .proj = view,
            .cameraPos = cameraPos
        };
    }

    void updateFragmentPushConstant(const glm::ivec2& screenSize, float aberationOffset) {
        fragmentPushConstant[engine.getCurFrame()] = {
            .screenSize = screenSize,
            .aberationOffset = aberationOffset,
            .nbShockwaves = static_cast<int>(shockwaves[engine.getCurFrame()].size())
        };
    }

    void updateTexture(VkSampler newSampler, VkImageView newImageView) {
        textures[engine.getCurFrame()] = {
            newSampler,
            newImageView
        };
    }

    void end() {
        if (shockwaves[engine.getCurFrame()].size() > lastFragmentStorageBufferSizes[engine.getCurFrame()]) {
            if (lastFragmentStorageBufferSizes[engine.getCurFrame()] > 0) {
                vkDestroyBuffer(engine.device, fragmentStorageBuffers[engine.getCurFrame()], nullptr);
                vkFreeMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], nullptr);
            }

            VkDeviceSize bufferSize = shockwaves[engine.getCurFrame()].size() * sizeof(SSBOShockwave);

            createBuffer(engine.physicalDevice, engine.device, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, fragmentStorageBuffers[vulkanEngine.getCurFrame()], fragmentStorageBuffersMemory[vulkanEngine.getCurFrame()]);

            vkMapMemory(engine.device, fragmentStorageBuffersMemory[engine.getCurFrame()], 0, bufferSize, 0, &fragmentStorageBuffersMapped[vulkanEngine.getCurFrame()]);
        
            lastFragmentStorageBufferSizes[engine.getCurFrame()] = shockwaves[engine.getCurFrame()].size();
        }

        memcpy(fragmentStorageBuffersMapped[engine.getCurFrame()], shockwaves[engine.getCurFrame()].data(), shockwaves[engine.getCurFrame()].size() * sizeof(SSBOShockwave));
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
        VkDescriptorBufferInfo storageInfoFragment {
            .buffer = fragmentStorageBuffers[engine.getCurFrame()],
            .offset = 0,
            .range = sizeof(SSBOShockwave) * shockwaves[engine.getCurFrame()].size()
        };

        VkDescriptorImageInfo imageInfo {
            .sampler = std::get<0>(textures[engine.getCurFrame()]),
            .imageView = std::get<1>(textures[engine.getCurFrame()]),
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        };

        std::vector<VkWriteDescriptorSet> descriptorWrites;
        
        if (shockwaves[engine.getCurFrame()].size() > 0) {
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

    std::array<std::size_t, VulkanEngine::MAX_FRAMES_IN_FLIGHT> lastFragmentStorageBufferSizes;
    std::array<VkBuffer, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffers;
    std::array<VkDeviceMemory, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMemory;
    std::array<void*, VulkanEngine::MAX_FRAMES_IN_FLIGHT> fragmentStorageBuffersMapped;

    std::array<std::vector<SSBOShockwave>, VulkanEngine::MAX_FRAMES_IN_FLIGHT> shockwaves;
};