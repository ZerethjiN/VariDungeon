#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMegaSlime(World& world, const glm::vec2& position) {
    return world.newEnt(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        MegaSlime(
            /*MoveDuration:*/ 2.0f,
            /*BounceDuration:*/ 4.5f,
            /*FireballDuration:*/ 4.f,
            /*SpawnDuration:*/ 1.0f,
            /*NbBounceLvl1:*/ 1,
            /*NbBounceLvl2:*/ 3,
            /*BounceMoveSpeed:*/ 32.f,
            /*BounceGroundDuration:*/ 0.5f,
            /*NbFireballLvl1:*/ 8,
            /*NbFireballLvl2:*/ 16,
            /*FireballMegaSlimeMoveSpeed:*/ 8.f,
            /*NbSpawnLvl1:*/ 1,
            /*NbSpawnLvl2:*/ 2
        ),
        IsMegaSlimeMove(1.0f, false),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(megaSlimeUV),
        Animation(megaSlimeAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(30),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}