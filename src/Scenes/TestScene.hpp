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
}