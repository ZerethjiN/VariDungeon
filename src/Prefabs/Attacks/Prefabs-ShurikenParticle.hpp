#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShurikenParticle(World& world, const glm::vec2& position, float rotationSpeed, const glm::vec2& offset) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Unerasable(),
        Shuriken(rotationSpeed, offset),
        PlayerWeapon(),
        Damage(1),
        Sprite(textureManager, shurikenParticleUV),
        // Animation(shurikenParticleAnim, ShurikenParticleAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Velocity(),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );
}