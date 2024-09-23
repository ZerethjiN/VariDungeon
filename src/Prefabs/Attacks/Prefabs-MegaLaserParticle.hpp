#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMegaLaserParticle(World& world, const glm::vec2& position, float rotation, float newLifeTime, float rotationSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        MegaLaser(rotationSpeed),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, megaLaserParticleUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(newLifeTime),
        ZIndex(25),
        Trigger(-16 / 2, -12 / 2, 160, 12)
    );
}