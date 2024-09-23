#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBatAttackParticle(World& world, const glm::vec2& position, float rotation) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, batAttackParticleUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(0.25f),
        Trigger(-48 / 2, -32 / 2, 48, 32)
    );
}