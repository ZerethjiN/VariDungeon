#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>

void testScene(World& world) {
    // Purge
    auto [textureManager, fontManager, pipelineManager, time] = world.getRes<TextureManager, FontManager, PipelineManager, Time>();
    textureManager.clear();
    fontManager.clear();
    pipelineManager.clear();

    // Reset Time
    time.setTimeScale(1.0f);

    world.newEnt(
        AmbientLight(glm::vec4(255, 255, 255, 255))
    );

    instantiateBarbarian(world, glm::vec2(0, 0));

    instantiateSlime(world, glm::vec2(48, 48));
}