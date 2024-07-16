#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

#include "Others/GenerateDungeon.hpp"

void testScene(SceneSystem, World& world) {
    // Purge
    // auto [textureManager, fontManager, pipelineManager, time] = world.resource<TextureManager, FontManager, PipelineManager, Time>();
    // textureManager.clear();
    // fontManager.clear();
    // pipelineManager.clear();

    // AppState
    auto [appstate] = world.resource<AppState>();
    appstate.state = APP_STATE_IN_GAME;

    auto [spatialHashMap] = world.resource<SpatialHashMap>();
    spatialHashMap.clear();

    // Reset Time
    auto [time] = world.resource<Time>();
    time.setTimeScale(1.0f);

    world.newEnt(
        AmbientLight(glm::vec4(255, 255, 255, 255))
    );

    generateDungeon(world, glm::vec2(0, 0));

    instantiateInventoryBarUI(world, glm::vec2(-80, -16));

    world.appendChildren(
        world.newEnt(
            UICreator(blackBackgroundUV, UIAnchor::CENTER_CENTER),
            Transform(
                glm::vec2(-80, -72),
                0,
                glm::vec2(1, 1)
            ),
            LifeTime(1.5f),
            ZIndex(999)
        ),
        {
            world.newEnt(
                TextUICreator("Floor X", "Fonts/Zepto-Regular.ttf", 16, UIAnchor::BOTTOM_CENTER, glm::vec2(160, 16), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                Transform(
                    glm::vec2(-80, -88),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(999)
            )
        }
    );
}