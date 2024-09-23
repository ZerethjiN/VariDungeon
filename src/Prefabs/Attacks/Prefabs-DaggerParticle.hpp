#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateDaggerParticle(World& world, const glm::vec2& position, const glm::vec2& direction, float rotation, float speed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Dagger(direction),
        PlayerWeapon(),
        Damage(1),
        Sprite(textureManager, daggerParticleUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(1.5f),
        Velocity(),
        Speed(speed),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );
}