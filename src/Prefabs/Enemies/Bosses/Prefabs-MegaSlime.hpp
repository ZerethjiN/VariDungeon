#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMegaSlime(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        MegaSlime(
            /*MoveDuration:*/ 1.5f,
            /*BounceDuration:*/ 4.5f,
            /*FireballDuration:*/ 4.f,
            /*SpawnDuration:*/ 1.0f,
            /*NbBounceLvl1:*/ 3,
            /*BounceMoveSpeed:*/ 32.f,
            /*BounceGroundDuration:*/ 0.25f,
            /*NbFireballLvl1:*/ 8,
            /*FireballMegaSlimeMoveSpeed:*/ 8.f
        ),
        IsMegaSlimeMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, megaSlimeUV),
        Animation(megaSlimeAnim, MegaSlimeAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 4, 6}}),
        ZIndex(0),
        Life(20),
        Velocity(),
        Speed(12),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}

Ent instantiateSlimeSlimeBoss(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Slime(0.5f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, slimeUV),
        Animation(slimeAnim, SlimeAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots(),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}