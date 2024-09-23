#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateTurret(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Turret(2.0f, 2.0f, 0.75f, 0.75f),
        IsTurretCardinal(2.0f, 0.75f),
        Sprite(textureManager, turretUV),
        Animation(turretAnim, TurretAnimType::CARDINAL),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Orientation(Orientation::SOUTH),
        ZIndex(0),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}