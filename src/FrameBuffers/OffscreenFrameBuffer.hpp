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

        // Colors
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

        // Colors
        for (auto imageView: unlitBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        unlitBackupImageViews = unlitImageViews;

        for (auto image: unlitBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        unlitBackupImages = unlitImages;

        for (auto memory: unlitBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }
        unlitBackupImageMemories = unlitImageMemories;

        // Lights
        for (auto imageView: lightBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        lightBackupImageViews = lightImageViews;

        for (auto image: lightBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        lightBackupImages = lightImages;

        for (auto memory: lightBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }
        lightBackupImageMemories = lightImageMemories;

        // Final
        for (auto imageView: finalBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        finalBackupImageViews = finalImageViews;

        for (auto image: finalBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        finalBackupImages = finalImages;

        for (auto memory: finalBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }
        finalBackupImageMemories = finalImageMemories;
    }

    ~OffscreenFrameBuffer() override {
        cleanupSwapChain();

        for (auto framebuffer: offscreenBackupFrameBuffers) {
            vkDestroyFramebuffer(engine.device, framebuffer, nullptr);
        }

        // Colors
        for (auto imageView: offscreenBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        for (auto image: offscreenBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        for (auto memory: offscreenBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }

        // Unlits
        for (auto imageView: unlitBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        for (auto image: unlitBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        for (auto memory: unlitBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }

        // Lights
        for (auto imageView: lightBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        for (auto image: lightBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        for (auto memory: lightBackupImageMemories) {
            vkFreeMemory(engine.device, memory, nullptr);
        }

        // Finals
        for (auto imageView: finalBackupImageViews) {
            vkDestroyImageView(engine.device, imageView, nullptr);
        }
        for (auto image: finalBackupImages) {
            vkDestroyImage(engine.device, image, nullptr);
        }
        for (auto memory: finalBackupImageMemories) {
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
        std::array<VkAttachmentDescription, 4> attachementDescs {
            // Color Attachement
            VkAttachmentDescription {
                .format = engine.swapChainImageFormat,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,//VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            },
            // Unlit Attachement
            VkAttachmentDescription {
                .format = engine.swapChainImageFormat,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,//VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            },
            // Light Attachement
            VkAttachmentDescription {
                .format = engine.swapChainImageFormat,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,//VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            },
            // Final Attachment
            VkAttachmentDescription {
                .format = engine.swapChainImageFormat,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,//VK_ATTACHMENT_LOAD_OP_CLEAR
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            }
        };

        std::array<VkAttachmentReference, 2> attachementRefsStage1 {
            // ColorAttachmentRef
            VkAttachmentReference {
                .attachment = 0,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            },
            // UnlitAttachmentRef
            VkAttachmentReference {
                .attachment = 1,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            },
        };

        std::array<VkAttachmentReference, 1> attachementRefsStage2 {
            // LightAttachmentRef
            VkAttachmentReference {
                .attachment = 2,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            }
        };

        std::array<VkAttachmentReference, 1> attachementRefsStage3out {
            // FinalAttachmentRef
            VkAttachmentReference {
                .attachment = 3,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            },
        };

        std::array<VkAttachmentReference, 3> attachementRefsStage3in {
            // ColorAttachmentRef
            VkAttachmentReference {
                .attachment = 0,
                .layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            },
            // UnlitAttachmentRef
            VkAttachmentReference {
                .attachment = 1,
                .layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            },
            // LightAttachmentRef
            VkAttachmentReference {
                .attachment = 2,
                .layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            }
        };

        std::array<VkSubpassDescription, 3> subpasses {
            // Sprites Pass
            VkSubpassDescription {
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                .colorAttachmentCount = static_cast<uint32_t>(attachementRefsStage1.size()),
                .pColorAttachments = attachementRefsStage1.data()
            },
            // Lights Pass
            VkSubpassDescription {
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                .colorAttachmentCount = static_cast<uint32_t>(attachementRefsStage2.size()),
                .pColorAttachments = attachementRefsStage2.data()
            },
            // Final Pass
            VkSubpassDescription {
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                .inputAttachmentCount = static_cast<uint32_t>(attachementRefsStage3in.size()),
                .pInputAttachments = attachementRefsStage3in.data(),
                .colorAttachmentCount = static_cast<uint32_t>(attachementRefsStage3out.size()),
                .pColorAttachments = attachementRefsStage3out.data()
            }
        };

        std::array<VkSubpassDependency, 4> dependencies {
            VkSubpassDependency {
                .srcSubpass = VK_SUBPASS_EXTERNAL,
                .dstSubpass = 0,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .srcAccessMask = 0,
                .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dependencyFlags = 0
            },
            VkSubpassDependency {
                .srcSubpass = 0,
                .dstSubpass = 1,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
                .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            },
            VkSubpassDependency {
                .srcSubpass = 1,
                .dstSubpass = 2,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
                .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            },
            VkSubpassDependency {
                .srcSubpass = 2,
                .dstSubpass = VK_SUBPASS_EXTERNAL,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT,
                .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            },
            // VkSubpassDependency {
            //     .srcSubpass = VK_SUBPASS_EXTERNAL,
            //     .dstSubpass = 0,
            //     .srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            //     .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            //     .srcAccessMask = VK_ACCESS_SHADER_READ_BIT,
            //     .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            //     .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            // },
            // VkSubpassDependency {
            //     .srcSubpass = 0,
            //     .dstSubpass = VK_SUBPASS_EXTERNAL,
            //     .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            //     .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            //     .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            //     .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
            //     .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
            // }
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
        offscreenImageMemories.resize(imageCount);
        offscreenImageViews.resize(imageCount);

        for (int i = 0; i < imageCount; i++) {
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
                .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, // VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
            };

            if (vkCreateImage(engine.device, &imageInfo, nullptr, &offscreenImages[i]) != VK_SUCCESS) {
                std::cerr << "failed to create image!" << std::endl;
                std::exit(EXIT_FAILURE);
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
                std::cerr << "failed to allocate image memory!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            vkBindImageMemory(engine.device, offscreenImages[i], offscreenImageMemories[i], 0);

            offscreenImageViews[i] = createImageView(engine.device, offscreenImages[i], engine.swapChainImageFormat);
        }

        // Unlit
        unlitImages.resize(imageCount);
        unlitImageMemories.resize(imageCount);
        unlitImageViews.resize(imageCount);

        for (int i = 0; i < imageCount; i++) {
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
                .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, // VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
            };

            if (vkCreateImage(engine.device, &imageInfo, nullptr, &unlitImages[i]) != VK_SUCCESS) {
                std::cerr << "failed to create image!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // printf("Reset offscreen ImageView[%d]: %d, %d\n", i, vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height);

            VkMemoryRequirements memRequirements;
            vkGetImageMemoryRequirements(engine.device, unlitImages[i], &memRequirements);

            VkMemoryAllocateInfo allocInfo {
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize = memRequirements.size,
                .memoryTypeIndex = findMemoryType(engine.physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            };

            if (vkAllocateMemory(engine.device, &allocInfo, nullptr, &unlitImageMemories[i]) != VK_SUCCESS) {
                std::cerr << "failed to allocate image memory!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            vkBindImageMemory(engine.device, unlitImages[i], unlitImageMemories[i], 0);

            unlitImageViews[i] = createImageView(engine.device, unlitImages[i], engine.swapChainImageFormat);
        }

        // Lights
        lightImages.resize(imageCount);
        lightImageMemories.resize(imageCount);
        lightImageViews.resize(imageCount);

        for (int i = 0; i < imageCount; i++) {
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
                .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, // VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
            };

            if (vkCreateImage(engine.device, &imageInfo, nullptr, &lightImages[i]) != VK_SUCCESS) {
                std::cerr << "failed to create image!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // printf("Reset offscreen ImageView[%d]: %d, %d\n", i, vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height);

            VkMemoryRequirements memRequirements;
            vkGetImageMemoryRequirements(engine.device, lightImages[i], &memRequirements);

            VkMemoryAllocateInfo allocInfo {
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize = memRequirements.size,
                .memoryTypeIndex = findMemoryType(engine.physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            };

            if (vkAllocateMemory(engine.device, &allocInfo, nullptr, &lightImageMemories[i]) != VK_SUCCESS) {
                std::cerr << "failed to allocate image memory!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            vkBindImageMemory(engine.device, lightImages[i], lightImageMemories[i], 0);

            lightImageViews[i] = createImageView(engine.device, lightImages[i], engine.swapChainImageFormat);
        }

        // Finals
        finalImages.resize(imageCount);
        finalImageMemories.resize(imageCount);
        finalImageViews.resize(imageCount);

        for (int i = 0; i < imageCount; i++) {
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

            if (vkCreateImage(engine.device, &imageInfo, nullptr, &finalImages[i]) != VK_SUCCESS) {
                std::cerr << "failed to create image!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // printf("Reset offscreen ImageView[%d]: %d, %d\n", i, vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height);

            VkMemoryRequirements memRequirements;
            vkGetImageMemoryRequirements(engine.device, finalImages[i], &memRequirements);

            VkMemoryAllocateInfo allocInfo {
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize = memRequirements.size,
                .memoryTypeIndex = findMemoryType(engine.physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            };

            if (vkAllocateMemory(engine.device, &allocInfo, nullptr, &finalImageMemories[i]) != VK_SUCCESS) {
                std::cerr << "failed to allocate image memory!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            vkBindImageMemory(engine.device, finalImages[i], finalImageMemories[i], 0);

            finalImageViews[i] = createImageView(engine.device, finalImages[i], engine.swapChainImageFormat);
        }
    }

    void createOffscreenFramebuffers() {
        offscreenFrameBuffers.resize(offscreenImageViews.size());

        for (int i = 0; i < offscreenImageViews.size(); i++) {
            std::array<VkImageView, 4> attachments {
                offscreenImageViews[i],
                unlitImageViews[i],
                lightImageViews[i],
                finalImageViews[i]
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

    std::vector<VkImage> offscreenBackupImages;
    std::vector<VkDeviceMemory> offscreenBackupImageMemories;
    std::vector<VkImageView> offscreenBackupImageViews;

    // Unlits
    std::vector<VkImage> unlitImages;
    std::vector<VkDeviceMemory> unlitImageMemories;
    std::vector<VkImageView> unlitImageViews;

    std::vector<VkImage> unlitBackupImages;
    std::vector<VkDeviceMemory> unlitBackupImageMemories;
    std::vector<VkImageView> unlitBackupImageViews;

    // Lights
    std::vector<VkImage> lightImages;
    std::vector<VkDeviceMemory> lightImageMemories;
    std::vector<VkImageView> lightImageViews;

    std::vector<VkImage> lightBackupImages;
    std::vector<VkDeviceMemory> lightBackupImageMemories;
    std::vector<VkImageView> lightBackupImageViews;

    // Final
    std::vector<VkImage> finalImages;
    std::vector<VkDeviceMemory> finalImageMemories;
    std::vector<VkImageView> finalImageViews;

    std::vector<VkImage> finalBackupImages;
    std::vector<VkDeviceMemory> finalBackupImageMemories;
    std::vector<VkImageView> finalBackupImageViews;
};