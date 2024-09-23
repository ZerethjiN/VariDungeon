#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSmallCrystalParticle(World& world, const glm::vec2& position, float rotation, float rotationSpeed, const glm::vec2& offset) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        SmallCrystalRotation(rotationSpeed, offset),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, smallCrystalUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        Velocity(),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );
}