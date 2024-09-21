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

class MainFrameBuffer: public IFrameBuffer {
public:
    MainFrameBuffer(VulkanEngine& engine):
        IFrameBuffer(engine) {
        createOffscreenRenderPass();
        createOffscreenImageViews();
        createOffscreenFramebuffers();
        createTextureSampler();
    }

    void cleanupSwapChain() override {
        for (auto framebuffer: offscreenFrameBuffers) {
            vkDestroyFramebuffer(engine.device, framebuffer, nullptr);
        }

        // Final
        for (auto imageView: offscreenImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
    }

    ~MainFrameBuffer() override {
        cleanupSwapChain();

        vkDestroySampler(engine.device, sampler, nullptr);
        vkDestroyRenderPass(engine.device, offscreenRenderPass, nullptr);
    }

    void resizeFrame() override {
        createOffscreenImageViews();
        createOffscreenFramebuffers();
    }

private:
    void createOffscreenRenderPass() {
        std::array<VkAttachmentDescription, 1> attachementDescs {
            // Final Attachment
            VkAttachmentDescription {
                .format = engine.swapChainImageFormat,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,//VK_ATTACHMENT_LOAD_OP_CLEAR
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            }
        };

        std::array<VkAttachmentReference, 1> attachementRefsStage {
            // ColorAttachmentRef
            VkAttachmentReference {
                .attachment = 0,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            },
        };

        std::array<VkSubpassDescription, 1> subpasses {
            // Sprites and Lights Pass
            VkSubpassDescription {
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                .colorAttachmentCount = static_cast<uint32_t>(attachementRefsStage.size()),
                .pColorAttachments = attachementRefsStage.data()
            }
        };

        std::array<VkSubpassDependency, 2> dependencies {
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
            .attachmentCount = static_cast<uint32_t>(attachementDescs.size()),
            .pAttachments = attachementDescs.data(),
            .subpassCount = static_cast<uint32_t>(subpasses.size()),
            .pSubpasses = subpasses.data(),
            .dependencyCount = static_cast<std::uint32_t>(dependencies.size()),
            .pDependencies = dependencies.data()
        };

        if (vkCreateRenderPass(engine.device, &renderPassInfo, nullptr, &offscreenRenderPass) != VK_SUCCESS) {
            std::cerr << "failed to create render pass!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void createOffscreenImageViews() {
        SwapChainSupportDetails swapChainSupport = engine.querySwapChainSupport(engine.physicalDevice);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        vkGetSwapchainImagesKHR(engine.device, engine.swapChain, &imageCount, nullptr);

        // Offscreen
        offscreenImages.resize(imageCount);
        offscreenImageViews.resize(imageCount);
        vkGetSwapchainImagesKHR(engine.device, engine.swapChain, &imageCount, offscreenImages.data());

        for (int i = 0; i < imageCount; i++) {
            offscreenImageViews[i] = createImageView(engine.device, offscreenImages[i], engine.swapChainImageFormat);
        }
    }

    void createOffscreenFramebuffers() {
        offscreenFrameBuffers.resize(offscreenImageViews.size());

        for (int i = 0; i < offscreenImageViews.size(); i++) {
            std::array<VkImageView, 1> attachments {
                offscreenImageViews[i],
            };

            VkFramebufferCreateInfo framebufferInfo {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .renderPass = offscreenRenderPass,
                .attachmentCount = static_cast<uint32_t>(attachments.size()),
                .pAttachments = attachments.data(),
                .width = engine.swapChainExtent.width,
                .height = engine.swapChainExtent.height,
                .layers = 1
            };

            if (vkCreateFramebuffer(engine.device, &framebufferInfo, nullptr, &offscreenFrameBuffers[i]) != VK_SUCCESS) {
                std::cerr << "failed to create framebuffer!" << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }

    void createTextureSampler() {
        VkSamplerCreateInfo samplerInfo {
            .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            .magFilter = VK_FILTER_NEAREST,
            .minFilter = VK_FILTER_NEAREST,
            .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
            .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .anisotropyEnable = VK_FALSE,
            .compareEnable = VK_FALSE,
            .compareOp = VK_COMPARE_OP_ALWAYS,
            .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
            .unnormalizedCoordinates = VK_FALSE
        };

        if (vkCreateSampler(vulkanEngine.device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS) {
            std::cerr << "failed to create texture sampler!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

public:
    VkSampler sampler;
    VkRenderPass offscreenRenderPass;

    // FrameBuffer
    std::vector<VkFramebuffer> offscreenFrameBuffers;
    std::vector<VkFramebuffer> offscreenBackupFrameBuffers;

    // Colors
    std::vector<VkImage> offscreenImages;
    std::vector<VkDeviceMemory> offscreenImageMemories;
    std::vector<VkImageView> offscreenImageViews;
};