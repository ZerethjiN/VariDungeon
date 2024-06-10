#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateEnemyExplosionAttackParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(explosionParticleUV),
        Animation(explosionParticleAnim, "SmallExplosion"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-32 / 2, -32 / 2, 32, 32)
    );
}

Ent instantiatePlayerExplosionAttackParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        PlayerWeapon(),
        Damage(1),
        SpriteCreator(explosionParticleUV),
        Animation(explosionParticleAnim, "SmallExplosion"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-32 / 2, -32 / 2, 32, 32)
    );
}

Ent instantiatePlayerEnemyExplosionAttackParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        EnemyWeapon(),
        PlayerWeapon(),
        Damage(1),
        SpriteCreator(explosionParticleUV),
        Animation(explosionParticleAnim, "SmallExplosion"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-32 / 2, -32 / 2, 32, 32)
    );
}