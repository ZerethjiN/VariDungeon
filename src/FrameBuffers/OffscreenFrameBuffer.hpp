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

class OffscreenFrameBuffer: public IFrameBuffer {
public:
    OffscreenFrameBuffer(VulkanEngine& engine):
        IFrameBuffer(engine) {
        createOffscreenRenderPass();
        createOffscreenImageViews();
        createOffscreenFramebuffers();
        createTextureSampler();
    }

    void cleanupSwapChain() override {
        for (auto framebuffer: offscreenBackupFrameBuffers) {
            vkDestroyFramebuffer(engine.device, framebuffer, nullptr);
        }
        offscreenBackupFrameBuffers = offscreenFrameBuffers;

        for (auto imageView: offscreenBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        offscreenBackupImageViews = offscreenImageViews;

        for (auto image: offscreenBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        offscreenBackupImages = offscreenImages;

        for (auto memory: offscreenBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }
        offscreenBackupImageMemories = offscreenImageMemories;
    }

    ~OffscreenFrameBuffer() override {
        cleanupSwapChain();

        for (auto framebuffer: offscreenBackupFrameBuffers) {
            vkDestroyFramebuffer(engine.device, framebuffer, nullptr);
        }
        for (auto imageView: offscreenBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        for (auto image: offscreenBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        for (auto memory: offscreenBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }

        vkDestroySampler(engine.device, sampler, nullptr);
        vkDestroyRenderPass(engine.device, offscreenRenderPass, nullptr);
    }

    void resizeFrame() override {
        createOffscreenImageViews();
        createOffscreenFramebuffers();
    }

private:
    void createOffscreenRenderPass() {
        VkAttachmentDescription colorAttachment {
            .format = engine.swapChainImageFormat,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,//VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
        };

        VkAttachmentReference colorAttachmentRef {
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };

        VkSubpassDescription subpass {
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = 1,
            .pColorAttachments = &colorAttachmentRef
        };

        // dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		// dependencies[0].dstSubpass = 0;
		// dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		// dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		// dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		// dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		// dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		// dependencies[1].srcSubpass = 0;
		// dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		// dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		// dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		// dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		// dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		// dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

        std::vector<VkSubpassDependency> dependencies {
            VkSubpassDependency {
                .srcSubpass = VK_SUBPASS_EXTERNAL,
                .dstSubpass = 0,
                .srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .srcAccessMask = VK_ACCESS_SHADER_READ_BIT,
                .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            },
            VkSubpassDependency {
                .srcSubpass = 0,
                .dstSubpass = VK_SUBPASS_EXTERNAL,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
                .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            }
        };

        VkRenderPassCreateInfo renderPassInfo {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .attachmentCount = 1,
            .pAttachments = &colorAttachment,
            .subpassCount = 1,
            .pSubpasses = &subpass,
            .dependencyCount = static_cast<std::uint32_t>(dependencies.size()),
            .pDependencies = dependencies.data()
        };

        if (vkCreateRenderPass(engine.device, &renderPassInfo, nullptr, &offscreenRenderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void createOffscreenImageViews() {
        SwapChainSupportDetails swapChainSupport = engine.querySwapChainSupport(engine.physicalDevice);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        vkGetSwapchainImagesKHR(engine.device, engine.swapChain, &imageCount, nullptr);
        offscreenImages.resize(imageCount);
        offscreenImageMemories.resize(imageCount);
        offscreenImageViews.resize(imageCount);

        for (uint32_t i = 0; i < imageCount; i++) {
            VkImageCreateInfo imageInfo {
                .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                .imageType = VK_IMAGE_TYPE_2D,
                .format = engine.swapChainImageFormat,
                .extent {
                    .width = engine.swapChainExtent.width,
                    .height = engine.swapChainExtent.height,
                    .depth = 1
                },
                .mipLevels = 1,
                .arrayLayers = 1,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .tiling = VK_IMAGE_TILING_OPTIMAL,
                .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
            };

            if (vkCreateImage(engine.device, &imageInfo, nullptr, &offscreenImages[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image!");
            }

            // printf("Reset offscreen ImageView[%d]: %d, %d\n", i, vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height);

            VkMemoryRequirements memRequirements;
            vkGetImageMemoryRequirements(engine.device, offscreenImages[i], &memRequirements);

            VkMemoryAllocateInfo allocInfo {
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize = memRequirements.size,
                .memoryTypeIndex = findMemoryType(engine.physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            };

            if (vkAllocateMemory(engine.device, &allocInfo, nullptr, &offscreenImageMemories[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate image memory!");
            }

            vkBindImageMemory(engine.device, offscreenImages[i], offscreenImageMemories[i], 0);

            offscreenImageViews[i] = createImageView(engine.device, offscreenImages[i], engine.swapChainImageFormat);
        }
    }

    void createOffscreenFramebuffers() {
        offscreenFrameBuffers.resize(offscreenImageViews.size());

        for (std::size_t i = 0; i < offscreenImageViews.size(); i++) {
            VkImageView attachments[] = {
                offscreenImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .pNext = nullptr,
                .flags = {},
                .renderPass = offscreenRenderPass,
                .attachmentCount = 1,
                .pAttachments = attachments,
                .width = engine.swapChainExtent.width,
                .height = engine.swapChainExtent.height,
                .layers = 1
            };

            // printf("Reset Offscreen FrameBuffer[%d]: %d, %d\n", i, engine.swapChainExtent.width, engine.swapChainExtent.height);

            if (vkCreateFramebuffer(engine.device, &framebufferInfo, nullptr, &offscreenFrameBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void createTextureSampler() {
        VkSamplerCreateInfo samplerInfo {
            .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            .pNext = nullptr,
            .flags = {},
            .magFilter = VK_FILTER_NEAREST,
            .minFilter = VK_FILTER_NEAREST,
            .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
            .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .mipLodBias = 0.f,
            .anisotropyEnable = VK_FALSE,
            .maxAnisotropy = 0.f,
            .compareEnable = VK_FALSE,
            .compareOp = VK_COMPARE_OP_ALWAYS,
            .minLod = 0.f,
            .maxLod = 0.f,
            .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
            .unnormalizedCoordinates = VK_FALSE
        };

        if (vkCreateSampler(vulkanEngine.device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture sampler!");
        }
    }

public:
    std::vector<VkImage> offscreenImages;
    std::vector<VkDeviceMemory> offscreenImageMemories;
    std::vector<VkImageView> offscreenImageViews;
    std::vector<VkFramebuffer> offscreenFrameBuffers;
    VkSampler sampler;
    VkRenderPass offscreenRenderPass;

    std::vector<VkImage> offscreenBackupImages;
    std::vector<VkDeviceMemory> offscreenBackupImageMemories;
    std::vector<VkImageView> offscreenBackupImageViews;
    std::vector<VkFramebuffer> offscreenBackupFrameBuffers;
};