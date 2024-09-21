#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGolem(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Golem(
            /*PreLaserDuration:*/ 0.75f,
            /*LaserDuration:*/ 1.0f,
            /*NbLasers:*/ 4,
            /*RockDuration:*/ 3.0f,
            /*NbRocks:*/ 9,
            /*FootDuration:*/ 0.75f
        ),
        IsGolemRockAttack(3.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, golemUV),
        Animation(golemAnim, GolemAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 4, 6}}),
        ZIndex(0),
        Life(30),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}

Ent instantiateGolemRock(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        GolemRock(0.75f),
        Breakable(),
        Life(2),
        Sprite(textureManager, rockUV),
        Animation(rockAnim, RockAnimType::NO_HIT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        OnBreakableHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(RockAnimType::HIT);
            }
        }),
        OnBreakableNoHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(RockAnimType::NO_HIT);
            }
        }),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(RockAnimType::DESTROYED);
            }
        }),
        Loots(),
        ZIndex(0),
        LifeTime(6.0)
        // Collider(-12 / 2, -12 / 2, 12, 12)
    );
}