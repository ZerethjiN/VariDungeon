#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateLavaSlime(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        LavaSlime(1.0f, 0.75f),
        IsLavaSlimeMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(lavaSlimeUV),
        Animation(lavaSlimeAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(4),
        Velocity(),
        Speed(32),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}