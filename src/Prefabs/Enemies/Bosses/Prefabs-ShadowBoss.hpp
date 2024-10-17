#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowBossHub(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        ShadowBossHubPattern({
            position + glm::vec2(-32, -16),
            position + glm::vec2(48, 32),
            position + glm::vec2(32, -48),
            position + glm::vec2(-8, -40)
        }),
        Sprite(textureManager, shadowBossUV),
        Animation(shadowBossAnim, ShadowBossAnimType::MOVE_DOWN),
        Transform2D(
            position + glm::vec2(-128, 64),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(15),
        Velocity(),
        Speed(128)
    );
}

Ent instantiateShadowBoss(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Boss(),
        FinalBoss(),
        Enemy(),
        EnemyPreSpawn(2.0f, 2),
        ShadowBoss(
            /*Move Duration:*/ 1.0f,
            /*Pre Laser Duration:*/ 0.75f,
            /*Laser Duration:*/ 3.0f,
            /*Shadow Mark Duration:*/ 2.0f,
            /*Nb Shadow Mark:*/ 8,
            /*Minion Pre Spawn Duration:*/ 0.75f,
            /*Shadow Explosion Duration:*/ 1.5f
        ),
        IsShadowBossMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, shadowBossUV),
        Animation(shadowBossAnim, ShadowBossAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({
            {LootType::KING, 1, 1}
        }),
        ZIndex(0),
        Life(40),
        Velocity(),
        Speed(20),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}

Ent instantiateShadowMinion(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        ShadowMinion(),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, shadowMinionUV),
        Animation(shadowMinionAnim, ShadowMinionAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots(),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(20),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}