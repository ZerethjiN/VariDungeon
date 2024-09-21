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

#include "../ZerengineCommon.hpp"

#include "VulkanEngine.hpp"
#include "IFrameBuffer.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"

class IGraphicsPipeline  {
protected:
    IGraphicsPipeline(VulkanEngine& newEngine, const VkRenderPass& newRenderPass, std::size_t newNbSet, const std::initializer_list<VkPushConstantRange>& newPushConstantRanges):
        engine(newEngine),
        descriptorSetLayouts(newNbSet),
        pushConstantRanges(newPushConstantRanges),
        descriptorSets(newNbSet),
        descriptorPools(newNbSet) {
    }

public:
    virtual ~IGraphicsPipeline() {
        vkDeviceWaitIdle(engine.device);

        for (const auto& descriptorPool: descriptorPools) {
            vkDestroyDescriptorPool(engine.device, descriptorPool, nullptr);
        }

        vkDestroyPipeline(engine.device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(engine.device, pipelineLayout, nullptr);

        for (const VkDescriptorSetLayout& descriptorSetLayout: descriptorSetLayouts) {
            vkDestroyDescriptorSetLayout(engine.device, descriptorSetLayout, nullptr);
        }
    }

protected:
    void createGraphicsPipeline(const VkRenderPass& renderPass, const std::string& shaderVertName, const std::string& shaderFragName, std::size_t nbFragmentOut, const std::vector<VkPipelineColorBlendAttachmentState>& newColorBlendAttachments, uint32_t subpassId) {
        auto vertShaderCode = readFile(shaderVertName);
        auto fragShaderCode = readFile(shaderFragName);

        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vertShaderModule,
            .pName = "main"
        };

        VkPipelineShaderStageCreateInfo fragShaderStageInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = fragShaderModule,
            .pName = "main"
        };

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        VkPipelineVertexInputStateCreateInfo vertexInputInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .vertexBindingDescriptionCount = 0
        };

        VkPipelineInputAssemblyStateCreateInfo inputAssembly {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,// VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable = VK_FALSE
        };

        VkPipelineViewportStateCreateInfo viewportState {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .viewportCount = 1,
            .scissorCount = 1
        };

        VkPipelineRasterizationStateCreateInfo rasterizer {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .depthClampEnable = VK_FALSE,
            .rasterizerDiscardEnable = VK_FALSE,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .cullMode = VK_CULL_MODE_NONE, // VK_CULL_MODE_BACK_BIT,
            .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
            .depthBiasEnable = VK_FALSE,
            .lineWidth = 1.0f
        };

        VkPipelineMultisampleStateCreateInfo multisampling {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
            .sampleShadingEnable = VK_FALSE
        };

        VkPipelineColorBlendStateCreateInfo colorBlending {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .logicOpEnable = VK_FALSE,
            .logicOp = VK_LOGIC_OP_COPY,
            .attachmentCount = static_cast<uint32_t>(newColorBlendAttachments.size()),
            .pAttachments = newColorBlendAttachments.data(),
            .blendConstants {
                0.0f,
                0.0f,
                0.0f,
                0.0f   
            }
        };

        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
            .dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()),
            .pDynamicStates = dynamicStates.data()
        };

        VkPipelineLayoutCreateInfo pipelineLayoutInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size()),
            .pSetLayouts = descriptorSetLayouts.data(),
            .pushConstantRangeCount  = static_cast<uint32_t>(pushConstantRanges.size()),
            .pPushConstantRanges  = pushConstantRanges.data()
        };

        if (vkCreatePipelineLayout(engine.device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            std::cerr << "failed to create pipeline layout!" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        VkGraphicsPipelineCreateInfo pipelineInfo {
            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .stageCount = 2,
            .pStages = shaderStages,
            .pVertexInputState = &vertexInputInfo,
            .pInputAssemblyState = &inputAssembly,
            .pViewportState = &viewportState,
            .pRasterizationState = &rasterizer,
            .pMultisampleState = &multisampling,
            .pColorBlendState = &colorBlending,
            .pDynamicState = &dynamicState,
            .layout = pipelineLayout,
            .renderPass = renderPass,
            .subpass = subpassId,
            .basePipelineHandle = VK_NULL_HANDLE
        };

        if (vkCreateGraphicsPipelines(engine.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            std::cerr << "failed to create graphics pipeline!" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        vkDestroyShaderModule(engine.device, fragShaderModule, nullptr);
        vkDestroyShaderModule(engine.device, vertShaderModule, nullptr);
    }

    VkShaderModule createShaderModule(const std::vector<char>& code) {
        VkShaderModuleCreateInfo createInfo {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = code.size(),
            .pCode = reinterpret_cast<const uint32_t*>(code.data())
        };

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(engine.device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            std::cerr << "failed to create shader module!" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        return shaderModule;
    }

protected:
    void createDescriptorSetLayout(const std::vector<VkDescriptorSetLayoutBinding>& newBindings, const std::vector<VkDescriptorBindingFlags>& newFlags, std::size_t setIndex) {
        VkDescriptorSetLayoutBindingFlagsCreateInfo bindingFlags {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
            .pNext = nullptr,
            .bindingCount = static_cast<uint32_t>(newFlags.size()),
            .pBindingFlags = newFlags.data()
        };

        VkDescriptorSetLayoutCreateInfo layoutInfo {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext = &bindingFlags,
            .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
            .bindingCount = static_cast<uint32_t>(newBindings.size()),
            .pBindings = newBindings.data()
        };

        if (vkCreateDescriptorSetLayout(engine.device, &layoutInfo, nullptr, &descriptorSetLayouts[setIndex]) != VK_SUCCESS) {
            std::cerr << "failed to create descriptor set layout!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void createDescriptorPool(std::size_t setIndex, const std::vector<VkDescriptorPoolSize>& newDescriptorPoolSizes) {
        VkDescriptorPoolCreateInfo poolInfo {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
            .maxSets = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT),
            .poolSizeCount = static_cast<uint32_t>(newDescriptorPoolSizes.size()),
            .pPoolSizes = newDescriptorPoolSizes.data()
        };

        if (vkCreateDescriptorPool(engine.device, &poolInfo, nullptr, &descriptorPools[setIndex]) != VK_SUCCESS) {
            std::cerr << "failed to create descriptor pool!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void createDescriptorSet(std::size_t setIndex) {
        std::vector<VkDescriptorSetLayout> layouts(VulkanEngine::MAX_FRAMES_IN_FLIGHT, descriptorSetLayouts[setIndex]);
        VkDescriptorSetAllocateInfo allocInfo {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext = nullptr,
            .descriptorPool = descriptorPools[setIndex],
            .descriptorSetCount = static_cast<uint32_t>(VulkanEngine::MAX_FRAMES_IN_FLIGHT),
            .pSetLayouts = layouts.data()
        };

        if (vkAllocateDescriptorSets(engine.device, &allocInfo, descriptorSets[setIndex].data()) != VK_SUCCESS) {
            std::cerr << "failed to allocate descriptor sets!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

protected:
    VulkanEngine& engine;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    const std::vector<VkPushConstantRange> pushConstantRanges;
    std::vector<std::array<VkDescriptorSet, VulkanEngine::MAX_FRAMES_IN_FLIGHT>> descriptorSets;
    std::vector<VkDescriptorPool> descriptorPools;
};