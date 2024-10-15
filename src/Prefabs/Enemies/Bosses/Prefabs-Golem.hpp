#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGolem(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Golem(
            /*PreLaserDuration:*/ 1.0f,
            /*LaserDuration:*/ 0.75f,
            /*NbLasers:*/ 4,
            /*RockDuration:*/ 3.0f,
            /*NbRocks:*/ 5,
            /*FootDuration:*/ 1.0f
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
        Loots({{LootType::XP, 4, 6}}),
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
    return world.create_entity(
        GolemRock(0.75f),
        Breakable(),
        Life(1),
        // Sprite(textureManager, rockUV),
        // Animation(rockAnim, RockAnimType::NO_HIT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        OnBreakableHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get_components<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(RockAnimType::HIT);
            }
        }),
        OnBreakableNoHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get_components<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(RockAnimType::NO_HIT);
            }
        }),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (auto opt = world.get_components<Animation>(thisEnt)) {
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