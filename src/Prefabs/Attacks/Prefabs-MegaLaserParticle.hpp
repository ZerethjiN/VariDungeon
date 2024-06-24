#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMegaLaserParticle(World& world, const glm::vec2& position, float rotation, float newLifeTime, float rotationSpeed) {
    return world.newEnt(
        MegaLaser(rotationSpeed),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(megaLaserParticleUV),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(newLifeTime),
        Trigger(-16 / 2, -12 / 2, 160, 12)
    );
}