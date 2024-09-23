#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateEnemyExplosionAttackParticle(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, explosionParticleUV),
        Animation(explosionParticleAnim, ExplosionParticleAnimType::SMALL_EXPLOSION),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-32 / 2, -32 / 2, 32, 32)
    );
}

Ent instantiateEnemyBigExplosionAttackParticle(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        EnemyWeapon(),
        Damage(2),
        Sprite(textureManager, explosionParticleUV),
        Animation(explosionParticleAnim, ExplosionParticleAnimType::BIG_EXPLOSION),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-48 / 2, -48 / 2, 48, 48)
    );
}

Ent instantiatePlayerExplosionAttackParticle(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        PlayerWeapon(),
        Damage(1),
        Sprite(textureManager, explosionParticleUV),
        Animation(explosionParticleAnim, ExplosionParticleAnimType::SMALL_EXPLOSION),
        Transform2D(
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
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        EnemyWeapon(),
        PlayerWeapon(),
        Damage(1),
        Sprite(textureManager, explosionParticleUV),
        Animation(explosionParticleAnim, ExplosionParticleAnimType::SMALL_EXPLOSION),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.30f),
        Velocity(),
        Trigger(-32 / 2, -32 / 2, 32, 32)
    );
}