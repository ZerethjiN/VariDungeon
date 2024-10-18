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

static float renderTimePoint = 0;

inline void renderSys(LateSystem, World& world) {
    auto [pipelineManager, frameBufferManager] = world.resource<PipelineManager, FrameBufferManager>();
    auto [time, inGameView, uiView] = world.resource<const Time, InGameView, UIView>();
    auto [textureManager] = world.resource<TextureManager>();

    auto tileMapsNoIndexes = world.query<const TileMap, Transform2D>(without<ZIndex>);
    auto tileMapsIndexes = world.query<const TileMap, Transform2D, const ZIndex>();
    auto spriteNoIndexes = world.query<const Sprite, Transform2D>(without<ZIndex>);
    auto spriteIndexes = world.query<const Sprite, Transform2D, const ZIndex>();
    auto textNoIndexes = world.query<Text, Transform2D>(without<ZIndex>);
    auto textIndexes = world.query<Text, Transform2D, const ZIndex>();
    auto lights = world.query<const PointLight, Transform2D>();
    // auto shockwaves = world.query<const Shockwave, const Transform2D>();
    auto uiNoIndexes = world.query<const UI, Transform2D>(without<ZIndex>);
    auto uiIndexes = world.query<const UI, Transform2D, const ZIndex>();
    auto textUINoIndexes = world.query<TextUI, Transform2D>(without<ZIndex>);
    auto textUIIndexes = world.query<TextUI, Transform2D, const ZIndex>();

    auto& offscreenFrameBuffer = frameBufferManager.get<OffscreenFrameBuffer>(vulkanEngine);
    auto& mainFrameBuffer = frameBufferManager.get<MainFrameBuffer>(vulkanEngine);

    auto& spriteBatchPipeline = pipelineManager.get<SpriteBatchPipeline>(vulkanEngine, offscreenFrameBuffer.offscreenRenderPass);
    auto& lightBatchPipeline = pipelineManager.get<LightBatchPipeline>(vulkanEngine, offscreenFrameBuffer.offscreenRenderPass);
    auto& uiBatchPipeline = pipelineManager.get<UIBatchPipeline>(vulkanEngine, mainFrameBuffer.offscreenRenderPass);
    auto& backgroundPipeline = pipelineManager.get<BackgroundPipeline>(vulkanEngine, offscreenFrameBuffer.offscreenRenderPass);
    auto& aberationPipeline = pipelineManager.get<AberationPipeline>(vulkanEngine, mainFrameBuffer.offscreenRenderPass);

//// Preparation des donnees: //////////////////////////////////////////////////////////////////////////////////

    vulkanEngine.drawFrameBegin();

    // AmbientLight
    glm::vec4 ambientLight(255, 255, 255, 255);
    for (auto [_, ambient]: world.query<const AmbientLight>()) {
        ambientLight = ambient.color;
    }

    // Screen Rect
    const glm::vec4 screenRect {
        -inGameView.getSize().x * 0.5f,
        -inGameView.getSize().y * 0.5f,
        inGameView.getSize().x,
        inGameView.getSize().y,
    };
    const auto screenModel = glm::translate(glm::mat4(1.0f), glm::vec3(inGameView.getCenter(), 0));
    const auto screenRectVerticesWithTransform = applyTransformOnRect(screenRect, screenModel);

    //// Affichage des sprites/tilemaps: ////
    std::size_t nbSprites = 0;
    std::map<int, std::map<float, std::vector<SpriteBatchPipeline::StorageBufferObject>>> orderedSprites;

    // Tilemaps
    for (auto [ent, tileMap, transform]: tileMapsNoIndexes) {
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
        for (const auto& tile: tileMap.tiles) {
            const std::array<glm::vec2, 4> sprtRectVerticesWithTransform {
                glm::vec2(transform.getModel() * glm::vec4(tile.second[0].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[1].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[2].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[3].position, 0, 1))
            };

            if (computeProjection(screenRectVerticesWithTransform, sprtRectVerticesWithTransform)) {
                orderedSpritesIt1->second.emplace_back(
                    tile.second,
                    transform.getModel(),
                    tileMap.color / 255.f,
                    spriteBatchPipeline.getTextureIdx(textureManager[tile.first.getCurImage().filename]),
                    static_cast<int>(world.has_components<IsUnlit>(ent)),
                    0,
                    0,
                    tileMap.tileSize,
                    glm::vec2(0, 0)
                );
                nbSprites++;
            }
        }
    }
    for (auto [ent, tileMap, transform, index]: tileMapsIndexes) {
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
        for (const auto& tile: tileMap.tiles) {
            const std::array<glm::vec2, 4> sprtRectVerticesWithTransform {
                glm::vec2(transform.getModel() * glm::vec4(tile.second[0].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[1].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[2].position, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(tile.second[3].position, 0, 1))
            };

            if (computeProjection(screenRectVerticesWithTransform, sprtRectVerticesWithTransform)) {
                orderedSpritesIt1->second.emplace_back(
                    tile.second,
                    transform.getModel(),
                    tileMap.color / 255.f,
                    spriteBatchPipeline.getTextureIdx(textureManager[tile.first.getCurImage().filename]),
                    static_cast<int>(world.has_components<IsUnlit>(ent)),
                    0,
                    0,
                    tileMap.tileSize,
                    glm::vec2(0, 0)
                );
                nbSprites++;
            }
        }
    }

    // Sprites
    for (auto [ent, sprt, transform]: spriteNoIndexes) {
        const std::array<glm::vec2, 4> sprtRectVerticesWithTransform {
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[0].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[1].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[2].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[3].position, 0, 1))
        };

        if (computeProjection(screenRectVerticesWithTransform, sprtRectVerticesWithTransform)) {
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
            orderedSpritesIt1->second.emplace_back(
                sprt.vertices,
                transform.getModel(),
                sprt.color / 255.f,
                spriteBatchPipeline.getTextureIdx(sprt.texture),
                static_cast<int>(world.has_components<IsUnlit>(ent)),
                0,
                0,
                glm::uvec2(sprt.textureRect.z, sprt.textureRect.w),
                glm::vec2(0, 0)
            );
            nbSprites++;
        }
    }
    for (auto [ent, sprt, transform, index]: spriteIndexes) {
        const std::array<glm::vec2, 4> sprtRectVerticesWithTransform {
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[0].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[1].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[2].position, 0, 1)),
            glm::vec2(transform.getModel() * glm::vec4(sprt.vertices[3].position, 0, 1))
        };

        if (computeProjection(screenRectVerticesWithTransform, sprtRectVerticesWithTransform)) {
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
            orderedSpritesIt1->second.emplace_back(
                sprt.vertices,
                transform.getModel(),
                sprt.color / 255.f,
                spriteBatchPipeline.getTextureIdx(sprt.texture),
                static_cast<int>(world.has_components<IsUnlit>(ent)),
                0,
                0,
                glm::uvec2(sprt.textureRect.z, sprt.textureRect.w),
                glm::vec2(0, 0)
            );
            nbSprites++;
        }
    }

    //// Affichage des Textes: ////
    std::map<int, std::vector<std::pair<Text&, Transform2D&>>> orderedTexts;

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

    /////////////////////////////////
    //// Creation du SpriteBatch ////
    /////////////////////////////////

    renderTimePoint += time.unscaledDelta();

    if (renderTimePoint >= 1.0f) {
        renderTimePoint -= 1.0f;
        #ifdef DISPLAY_FPS
            std::println("Nb Entities: {}", world.getTotalEntities());
            std::println("Nb Archetypes: {}", world.getTotalArchetypes());
            std::println("Nb Sprites: {}", nbSprites);
            std::println("Nb Lights: {}", lights.size());
        #endif
    }

    spriteBatchPipeline.beginSprite(nbSprites);
        // Ajout des sprites
        for (const auto& pair: orderedSprites) {
            for (const auto& sprtHeightpair: pair.second) {
                for (const auto& sprtTransPair: sprtHeightpair.second) {
                    spriteBatchPipeline.addSprite(sprtTransPair);
                }
            }
        }

        // Ajout des textes
        for (const auto& pair: orderedTexts) {
            for (const auto& pairTextTrans: pair.second) {
                spriteBatchPipeline.addText(pairTextTrans.first, pairTextTrans.second);
            }
        }

        spriteBatchPipeline.addView(inGameView.getModel());
    spriteBatchPipeline.end();

    //// Preparation de Light Batch ////
    lightBatchPipeline.beginLight(lights.size());
        for (auto [_, light, transform]: lights) {
            const std::array<glm::vec2, 4> lightRectVerticesWithTransform {
                glm::vec2(transform.getModel() * glm::vec4(glm::vec2(-1, -1) * light.radius, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(glm::vec2(-1, +1) * light.radius, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(glm::vec2(+1, -1) * light.radius, 0, 1)),
                glm::vec2(transform.getModel() * glm::vec4(glm::vec2(+1, +1) * light.radius, 0, 1))
            };

            if (computeProjection(screenRectVerticesWithTransform, lightRectVerticesWithTransform)) {
                lightBatchPipeline.addLight(light, transform);
            }
        }

        lightBatchPipeline.addView(inGameView.getModel());
    lightBatchPipeline.end();

    //// Affichage Ui: ////

    std::map<int, std::vector<std::pair<const UI&, Transform2D&>>> orderedUISprites;

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

    //// Affichage TextUI: ////
    std::map<int, std::vector<std::pair<TextUI&, Transform2D&>>> orderedTextsUI;

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

    ///////////////////////////////
    //// Creation de l'UIBatch ////
    ///////////////////////////////

    uiBatchPipeline.beginUI();
        // Ajout des Sprites
        for (const auto& pair: orderedUISprites) {
            for (const auto& sprtTransPair: pair.second) {
                uiBatchPipeline.addUI(sprtTransPair.first, sprtTransPair.second, uiView);
            }
        }

        // Ajout des Textes
        for (const auto& pair: orderedTextsUI) {
            for (const auto& pairTextTrans: pair.second) {
                uiBatchPipeline.addTextUI(pairTextTrans.first, pairTextTrans.second, uiView);
            }
        }

        uiBatchPipeline.addView(uiView.getModel());
    uiBatchPipeline.end();

    //// background ////

    backgroundPipeline.updateFragmentPushConstant(
        ambientLight
    );
    backgroundPipeline.updateTexture(
        offscreenFrameBuffer.offscreenImageViews[vulkanEngine.imageIndex],
        offscreenFrameBuffer.unlitImageViews[vulkanEngine.imageIndex],
        offscreenFrameBuffer.lightImageViews[vulkanEngine.imageIndex]
    );

    //// preparation de l'aberation ////
    float aberationOffset = 0;
    glm::vec2 aberationDirection(1, 0);
    for (auto [_, aberation]: world.query<const CameraAberation>()) {
        aberationOffset = aberation.distance;
        aberationDirection = aberation.direction;
    }

    aberationPipeline.updateFragmentPushConstant(
        glm::ivec2(vulkanEngine.swapChainExtent.width, vulkanEngine.swapChainExtent.height),
        aberationDirection,
        aberationOffset,
        randomRangeFloat(128.0f, 256.0f)
    );
    aberationPipeline.updateTexture(
        offscreenFrameBuffer.sampler,
        offscreenFrameBuffer.finalImageViews[vulkanEngine.imageIndex]
    );

//// Debut Draw: //////////////////////////////////////////////////////////////////////////////////

    VkCommandBufferBeginInfo beginInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pInheritanceInfo = nullptr
    };

    if (vkBeginCommandBuffer(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &beginInfo) != VK_SUCCESS) {
        std::cerr << "failed to begin recording command buffer!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

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
        std::array<VkClearValue, 3> clearColors {
            VkClearValue{{{0.0f, 0.0f, 0.0f, 1.0f}}},
            VkClearValue{{{0.0f, 0.0f, 0.0f, 1.0f}}},
            VkClearValue{{{0.0f, 0.0f, 0.0f, 1.0f}}},
        };

        VkRenderPassBeginInfo renderPassInfo {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = offscreenFrameBuffer.offscreenRenderPass,
            .framebuffer = offscreenFrameBuffer.offscreenFrameBuffers[vulkanEngine.imageIndex],
            .renderArea {
                .offset = {0, 0},
                .extent = vulkanEngine.swapChainExtent
            },
            .clearValueCount = static_cast<uint32_t>(clearColors.size()),
            .pClearValues = clearColors.data()
        };

        vkCmdBeginRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdSetViewport(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &viewport);
            vkCmdSetScissor(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &scissor);

            spriteBatchPipeline.draw();

            vkCmdNextSubpass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], VK_SUBPASS_CONTENTS_INLINE);

            lightBatchPipeline.draw();

            vkCmdNextSubpass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], VK_SUBPASS_CONTENTS_INLINE);

            backgroundPipeline.draw();
        vkCmdEndRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]);
    }

    {
        std::array<VkClearValue, 1> clearColors {
            VkClearValue{{{0.0f, 0.0f, 0.0f, 1.0f}}},
        };

        VkRenderPassBeginInfo renderPassInfo {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = mainFrameBuffer.offscreenRenderPass,
            .framebuffer = mainFrameBuffer.offscreenFrameBuffers[vulkanEngine.imageIndex],
            .renderArea {
                .offset = {0, 0},
                .extent = vulkanEngine.swapChainExtent
            },
            .clearValueCount = static_cast<uint32_t>(clearColors.size()),
            .pClearValues = clearColors.data()
        };

        vkCmdBeginRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdSetViewport(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &viewport);
            vkCmdSetScissor(vulkanEngine.commandBuffers[vulkanEngine.currentFrame], 0, 1, &scissor);

            aberationPipeline.draw();
            uiBatchPipeline.draw();
        vkCmdEndRenderPass(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]);
    }

    if (vkEndCommandBuffer(vulkanEngine.commandBuffers[vulkanEngine.currentFrame]) != VK_SUCCESS) {
        std::cerr << "failed to record command buffer!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    vulkanEngine.drawFrameEnd();
}
