#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateVoidSlime(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        VoidSlime(1.5f, 1.5f, 20.f, 48.f),
        IsVoidSlimeMove(1.5f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(voidSlimeUV),
        Animation(voidSlimeAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}