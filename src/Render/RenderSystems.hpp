#pragma once

#include <map>

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <Scenes.hpp>
#include <Systems.hpp>
#include <Pipelines.hpp>
#include <FrameBuffers.hpp>

void renderSys(LateSystem, World& world) {
    auto [pipelineManager, frameBufferManager] = world.resource<PipelineManager, FrameBufferManager>();
    auto [inGameView, uiView] = world.resource<InGameView, UIView>();

    auto tileMapsNoIndexes = world.view<const TileMap, Transform>(without<ZIndex>);
    auto tileMapsIndexes = world.view<const TileMap, Transform, const ZIndex>();
    auto spriteNoIndexes = world.view<const Sprite, Transform>(without<ZIndex>);
    auto spriteIndexes = world.view<const Sprite, Transform, const ZIndex>();
    auto textNoIndexes = world.view<Text, Transform>(without<ZIndex>);
    auto textIndexes = world.view<Text, Transform, const ZIndex>();
    auto lights = world.view<const PointLight, const Transform>();
    auto uiNoIndexes = world.view<const UI, Transform>(without<ZIndex>);
    auto uiIndexes = world.view<const UI, Transform, const ZIndex>();
    auto textUINoIndexes = world.view<TextUI, Transform>(without<ZIndex>);
    auto textUIIndexes = world.view<TextUI, Transform, const ZIndex>();

    auto& mainFrameBuffer = frameBufferManager.get<MainFrameBuffer>(vulkanEngine);
    auto& offscreenFrameBuffer = frameBufferManager.get<OffscreenFrameBuffer>(vulkanEngine);

    auto& spriteBatchPipeline = pipelineManager.get<SpriteBatchPipeline>(vulkanEngine, offscreenFrameBuffer.offscreenRenderPass);
    auto& textBatchPipeline = pipelineManager.get<TextBatchPipeline>(vulkanEngine, offscreenFrameBuffer.offscreenRenderPass);
    auto& uiBatchPipeline = pipelineManager.get<UIBatchPipeline>(vulkanEngine, mainFrameBuffer.renderPass);
    auto& textUiBatchPipeline = pipelineManager.get<TextUIBatchPipeline>(vulkanEngine, mainFrameBuffer.renderPass);
    auto& aberationPipeline = pipelineManager.get<AberationPipeline>(vulkanEngine, mainFrameBuffer.renderPass);

//// Preparation des donnees: //////////////////////////////////////////////////////////////////////////////////

    vulkanEngine.drawFrameBegin();

    //// Affichage des sprites/tilemaps: ////

    std::map<int, std::map<float, std::vector<std::tuple<Ent, const Sprite&, Transform&>>>> orderedSprites;
    std::map<int, std::map<float, std::vector<std::tuple<Ent, const TileMap&, Transform&>>>> orderedTilemaps;

    // Tilemaps
    for (auto [ent, tileMap, transform]: tileMapsNoIndexes) {
        auto orderedSpritesIt0 = orderedTilemaps.find(0);
        if (orderedSpritesIt0 == orderedTilemaps.end()) {
            orderedSpritesIt0 = orderedTilemaps.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(0),
                std::forward_as_tuple()
            ).first;
        }
        auto orderedSpritesIt1 = orderedSpritesIt0->second.find(transform.getPosition().y);
        if (orderedSpritesIt1 == orderedSpritesIt0->second.end()) {
            orderedSpritesIt1 = orderedSpritesIt0->second.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(transform.getPosition().y),
                std::forward_as_tuple()
            ).first;
        }
        orderedSpritesIt1->second.emplace_back(ent, tileMap, transform);
    }
    for (auto [ent, tileMap, transform, index]: tileMapsIndexes) {
        auto orderedSpritesIt0 = orderedTilemaps.find(index.layer);
        if (orderedSpritesIt0 == orderedTilemaps.end()) {
            orderedSpritesIt0 = orderedTilemaps.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(index.layer),
                std::forward_as_tuple()
            ).first;
        }
        auto orderedSpritesIt1 = orderedSpritesIt0->second.find(transform.getPosition().y);
        if (orderedSpritesIt1 == orderedSpritesIt0->second.end()) {
            orderedSpritesIt1 = orderedSpritesIt0->second.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(transform.getPosition().y),
                std::forward_as_tuple()
            ).first;
        }
        orderedSpritesIt1->second.emplace_back(ent, tileMap, transform);
    }

    // Sprites
    for (auto [ent, sprt, transform]: spriteNoIndexes) {
        auto orderedSpritesIt0 = orderedSprites.find(0);
        if (orderedSpritesIt0 == orderedSprites.end()) {
            orderedSpritesIt0 = orderedSprites.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(0),
                std::forward_as_tuple()
            ).first;
        }
        auto orderedSpritesIt1 = orderedSpritesIt0->second.find(transform.getPosition().y);
        if (orderedSpritesIt1 == orderedSpritesIt0->second.end()) {
            orderedSpritesIt1 = orderedSpritesIt0->second.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(transform.getPosition().y),
                std::forward_as_tuple()
            ).first;
        }
        orderedSpritesIt1->second.emplace_back(ent, sprt, transform);
    }
    for (auto [ent, sprt, transform, index]: spriteIndexes) {
        auto orderedSpritesIt0 = orderedSprites.find(index.layer);
        if (orderedSpritesIt0 == orderedSprites.end()) {
            orderedSpritesIt0 = orderedSprites.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(index.layer),
                std::forward_as_tuple()
            ).first;
        }
        auto orderedSpritesIt1 = orderedSpritesIt0->second.find(transform.getPosition().y);
        if (orderedSpritesIt1 == orderedSpritesIt0->second.end()) {
            orderedSpritesIt1 = orderedSpritesIt0->second.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(transform.getPosition().y),
                std::forward_as_tuple()
            ).first;
        }
        orderedSpritesIt1->second.emplace_back(ent, sprt, transform);
    }

    spriteBatchPipeline.beginSprite(spriteNoIndexes.size() + spriteIndexes.size());
        for (const auto& pair: orderedTilemaps) {
            for (const auto& sprtHeightpair: pair.second) {
                for (const auto& sprtTransPair: sprtHeightpair.second) {
                    spriteBatchPipeline.addTileMap(std::get<1>(sprtTransPair), std::get<2>(sprtTransPair));
                }
            }
        }
        for (const auto& pair: orderedSprites) {
            for (const auto& sprtHeightpair: pair.second) {
                for (const auto& sprtTransPair: sprtHeightpair.second) {
                    spriteBatchPipeline.addSprite(std::get<1>(sprtTransPair), std::get<2>(sprtTransPair));
                }
            }
        }

        spriteBatchPipeline.beginLight(lights.size());
        for (auto [_, light, transform]: lights) {
            spriteBatchPipeline.addLight(light, transform);
        }

        glm::vec4 ambientLight(255, 255, 255, 255);
        for (auto [_, ambient]: world.view<const AmbientLight>()) {
            ambientLight = ambient.color;
        }
        spriteBatchPipeline.addAmbientColor(ambientLight);
        spriteBatchPipeline.addView(inGameView.getModel());    
    spriteBatchPipeline.end();

    //// Affichage des Textes: ////

    std::map<int, std::vector<std::pair<Text&, Transform&>>> orderedTexts;

    for (auto [_, text, trans]: textNoIndexes) {
        auto orderedTextsIt = orderedTexts.find(0);
        if (orderedTextsIt == orderedTexts.end()) {
            orderedTextsIt = orderedTexts.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(0),
                std::forward_as_tuple()
            ).first;
        }
        orderedTextsIt->second.emplace_back(text, trans);
    }
    for (auto [_, text, trans, index]: textIndexes) {
        auto orderedTextsIt = orderedTexts.find(index.layer);
        if (orderedTextsIt == orderedTexts.end()) {
            orderedTextsIt = orderedTexts.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(index.layer),
                std::forward_as_tuple()
            ).first;
        }
        orderedTextsIt->second.emplace_back(text, trans);
    }

    textBatchPipeline.beginText(textIndexes.size() + textNoIndexes.size());
        for (const auto& pair: orderedTexts) {
            for (const auto& pairTextTrans: pair.second) {
                textBatchPipeline.addText(pairTextTrans.first, pairTextTrans.second);
            }
        }

        textBatchPipeline.addView(inGameView.getModel());
    textBatchPipeline.endText();

    //// Affichage Ui: ////

    std::map<int, std::vector<std::pair<const UI&, Transform&>>> orderedUISprites;

    for (auto [_, ui, transform]: uiNoIndexes) {
        auto orderedUISpritesIT = orderedUISprites.find(0);
        if (orderedUISpritesIT == orderedUISprites.end()) {
            orderedUISpritesIT = orderedUISprites.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(0),
                std::forward_as_tuple()
            ).first;
        }
        orderedUISpritesIT->second.emplace_back(ui, transform);
    }
    for (auto [_, ui, transform, index]: uiIndexes) {
        auto orderedUISpritesIT = orderedUISprites.find(index.layer);
        if (orderedUISpritesIT == orderedUISprites.end()) {
            orderedUISpritesIT = orderedUISprites.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(index.layer),
                std::forward_as_tuple()
            ).first;
        }
        orderedUISpritesIT->second.emplace_back(ui, transform);
    }

    uiBatchPipeline.beginUI(uiNoIndexes.size() + uiIndexes.size());
        for (const auto& pair: orderedUISprites) {
            for (const auto& sprtTransPair: pair.second) {
                uiBatchPipeline.addUI(sprtTransPair.first, sprtTransPair.second, uiView);
            }
        }

        uiBatchPipeline.addView(uiView.getModel());
    uiBatchPipeline.end();

    //// Affichage TextUI: ////

    std::map<int, std::vector<std::pair<TextUI&, Transform&>>> orderedTextsUI;

    for (auto [_, ui, trans]: textUINoIndexes) {
        auto orderedTextsIt = orderedTextsUI.find(0);
        if (orderedTextsIt == orderedTextsUI.end()) {
            orderedTextsIt = orderedTextsUI.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(0),
                std::forward_as_tuple()
            ).first;
        }
        orderedTextsIt->second.emplace_back(ui, trans);
    }
    for (auto [_, ui, trans, index]: textUIIndexes) {
        auto orderedTextsIt = orderedTextsUI.find(index.layer);
        if (orderedTextsIt == orderedTextsUI.end()) {
            orderedTextsIt = orderedTextsUI.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(index.layer),
                std::forward_as_tuple()
            ).first;
        }
        orderedTextsIt->second.emplace_back(ui, trans);
    }

    textUiBatchPipeline.beginUI(textUIIndexes.size() + textUINoIndexes.size());
        for (const auto& pair: orderedTextsUI) {
            for (const auto& pairTextTrans: pair.second) {
                textUiBatchPipeline.addUI(pairTextTrans.first, pairTextTrans.second, uiView);
            }
        }

        textUiBatchPipeline.addView(uiView.getModel());
    textUiBatchPipeline.end();

    //// preparation de l'aberation ////
    float aberationOffset = 0;
    for (auto [_, aberation]: world.view<const CameraAberation>()) {
        aberationOffset = aberation.distance;
    }

    glm::vec2 cameraPos(0, 0);
    for (auto [_, transform]: world.view<const Transform>(with<Camera, CurCamera>)) {
        cameraPos = transform.getPosition();
    }

    aberationPipeline.addView(inGameView.getModel(), cameraPos);

    aberationPipeline.updateFragmentPushConstant(
        glm::ivec2(vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height),
        aberationOffset
    );
    aberationPipeline.updateTexture(offscreenFrameBuffer.sampler, offscreenFrameBuffer.offscreenImageViews[vulkanEngine.imageIndex]);

//// Debut Draw: //////////////////////////////////////////////////////////////////////////////////

    VkCommandBufferBeginInfo beginInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pInheritanceInfo = nullptr
    };

    if (vkBeginCommandBuffer(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    VkViewport viewport {
        .x = 0.0f,
        .y = 0.0f,
        .width = (float) vulkanEngine.swapChainExtent.width,
        .height = (float) vulkanEngine.swapChainExtent.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };
    VkRect2D scissor {
        .offset {0, 0},
        .extent = vulkanEngine.swapChainExtent
    };

    {
        VkRenderPassBeginInfo renderPassInfo {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = offscreenFrameBuffer.offscreenRenderPass,
            .framebuffer = offscreenFrameBuffer.offscreenFrameBuffers[vulkanEngine.imageIndex],
            .renderArea {
                .offset = {0, 0},
                .extent = vulkanEngine.swapChainExtent
            },
            .clearValueCount = 1,
            .pClearValues = &clearColor
        };

        vkCmdBeginRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdSetViewport(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &viewport);
            vkCmdSetScissor(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &scissor);

            spriteBatchPipeline.draw();
            textBatchPipeline.draw();
        vkCmdEndRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]);
    }

    {
        VkRenderPassBeginInfo renderPassInfo {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = mainFrameBuffer.renderPass,
            .framebuffer = mainFrameBuffer.frameBuffers[vulkanEngine.imageIndex],
            .renderArea {
                .offset = {0, 0},
                .extent = vulkanEngine.swapChainExtent
            },
            .clearValueCount = 1,
            .pClearValues = &clearColor
        };

        vkCmdBeginRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdSetViewport(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &viewport);
            vkCmdSetScissor(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &scissor);

            aberationPipeline.draw();
            uiBatchPipeline.draw();
            textUiBatchPipeline.draw();
        vkCmdEndRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]);
    }

    if (vkEndCommandBuffer(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }

    vulkanEngine.drawFrameEnd();
}