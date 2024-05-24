#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateLaserParticle(World& world, const glm::vec2& position, const glm::vec2& direction, float rotation, float speed) {
    return world.newEnt(
        Laser(direction),
        PlayerWeapon(),
        Damage(1),
        SpriteCreator(laserParticleUV),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(1.0f),
        Velocity(),
        Speed(speed),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );
}