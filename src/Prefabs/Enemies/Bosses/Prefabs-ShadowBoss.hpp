#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowBossHub(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        ShadowBossHubPattern({
            position + glm::vec2(-32, -16),
            position + glm::vec2(48, 32),
            position + glm::vec2(32, -48),
            position + glm::vec2(-8, -40)
        }),
        Sprite(textureManager, shadowBossUV),
        Animation(shadowBossAnim, ShadowBossAnimType::MOVE_DOWN),
        Transform2D(
            position + glm::vec2(-128, 64),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(15),
        Velocity(),
        Speed(128)
    );
}