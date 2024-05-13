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

    auto playerEnt = instantiateBarbarian(world, glm::vec2(-48, 0));

    auto cameraOrigin = world.newEnt(
        Transform(
            glm::vec2(0, 0),
            0,
            glm::vec2(1, 1)
        )
    );

    world.appendChildren(cameraOrigin, {
        // Camera
        world.newEnt(
            Transform(
                glm::vec2(0, 0),
                0,
                glm::vec2(1, 1)
            ),
            Camera(),
            CurCamera()
        )
    });

    // Background:
    world.newEnt(
        TileMapCreator("Textures/TileMapDesert.png", {
            tileMapDesertUV[ 14], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 15],
            tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  3], tileMapDesertUV[  2], tileMapDesertUV[ 11],
            tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  4], tileMapDesertUV[ 11],
            tileMapDesertUV[ 13], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[ 11],
            tileMapDesertUV[ 13], tileMapDesertUV[  3], tileMapDesertUV[  3], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[ 11],
            tileMapDesertUV[ 13], tileMapDesertUV[  2], tileMapDesertUV[  3], tileMapDesertUV[  3], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[ 11],
            tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[ 11],
            tileMapDesertUV[ 16], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 17],
        }, glm::uvec2(10, 8), glm::uvec2(16, 16)),
        ZIndex(0),
        Transform(
            glm::vec2(0, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
            0,
            glm::vec2(1, 1)
        )
    );

    // Wall Collisions:
    world.newEnt(
        Transform(
            glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 160, 32)
    );

    world.newEnt(
        Transform(
            glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 128)
    );

    world.newEnt(
        Transform(
            glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 128)
    );

    world.newEnt(
        Transform(
            glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 160, 32)
    );

    // Decors:
    instantiateMiniTorch(world, glm::vec2(-32, -64), 0);
    instantiateMiniTorch(world, glm::vec2(16, -64), 0);
    instantiateMiniTorch(world, glm::vec2(-32, 48), 180);
    instantiateMiniTorch(world, glm::vec2(16, 48), 180);
    instantiateMiniTorch(world, glm::vec2(-80, -32), 270);
    instantiateMiniTorch(world, glm::vec2(-80, 16), 270);
    instantiateMiniTorch(world, glm::vec2(64, -32), 90);
    instantiateMiniTorch(world, glm::vec2(64, 16), 90);

    // Enemies:
    instantiateSlime(world, glm::vec2(0, 0));
    instantiateSlime(world, glm::vec2(0, 0));
    instantiateSlime(world, glm::vec2(0, 0));
    instantiateSlime(world, glm::vec2(0, 0));

    // Breakables:
    instantiateRock(world, glm::vec2(-48, -48));
    instantiateJar(world, glm::vec2(-64, -48));
    instantiateRock(world, glm::vec2(-64, -32));
    instantiateJar(world, glm::vec2(48, 32));
}