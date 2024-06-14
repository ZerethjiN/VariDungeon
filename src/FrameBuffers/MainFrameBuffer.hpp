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
        createRenderPass();
        createImageViews();
        createFramebuffers();
    }

    void cleanupSwapChain() override {
        for (auto framebuffer: frameBuffers) {
            vkDestroyFramebuffer(engine.device, framebuffer, nullptr);
        }

        for (auto imageView: imageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
    }

    ~MainFrameBuffer() override {
        cleanupSwapChain();

        vkDestroyRenderPass(engine.device, renderPass, nullptr);
    }

    void resizeFrame() override {
        createImageViews();
        createFramebuffers();
    }

private:
    void createRenderPass() {
        VkAttachmentDescription colorAttachment {
            .format = engine.swapChainImageFormat,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,//VK_ATTACHMENT_LOAD_OP_CLEAR
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
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

        // std::array<VkSubpassDependency, 1> dependencies {
        //     VkSubpassDependency {
        //         .srcSubpass = VK_SUBPASS_EXTERNAL,
        //         .dstSubpass = 0,
        //         .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        //         .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        //         .srcAccessMask = 0,
        //         .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        //         .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
        //     }
        // };

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

        if (vkCreateRenderPass(engine.device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void createImageViews() {
        SwapChainSupportDetails swapChainSupport = engine.querySwapChainSupport(engine.physicalDevice);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        vkGetSwapchainImagesKHR(engine.device, engine.swapChain, &imageCount, nullptr);
        images.resize(imageCount);
        imageViews.resize(imageCount);
        vkGetSwapchainImagesKHR(engine.device, engine.swapChain, &imageCount, images.data());

        for (int i = 0; i < imageCount; i++) {
            imageViews[i] = createImageView(engine.device, images[i], engine.swapChainImageFormat);

            // printf("Reset ImageView[%d]: %d, %d\n", i, vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height);
        }
    }

    void createFramebuffers() {
        frameBuffers.resize(imageViews.size());

        for (int i = 0; i < imageViews.size(); i++) {
            VkImageView attachments[] = {
                imageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .renderPass = renderPass,
                .attachmentCount = 1,
                .pAttachments = attachments,
                .width = engine.swapChainExtent.width,
                .height = engine.swapChainExtent.height,
                .layers = 1
            };

            // printf("Reset FrameBuffer[%d]: %d, %d\n", i, engine.swapChainExtent.width, engine.swapChainExtent.height);

            if (vkCreateFramebuffer(engine.device, &framebufferInfo, nullptr, &frameBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

public:
    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;
    std::vector<VkFramebuffer> frameBuffers;
    VkRenderPass renderPass;
};