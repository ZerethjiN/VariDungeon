#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerBombSys(MainFixedSystem, World& world) {
    auto players = world.view<PlayerBomb, const Transform, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [_, playerBomb, playerTransform, zindex]: players) {
        if (playerBomb.canSpawnBomb(time.fixedDelta())) {
            float rndSpreadDirection = std::rand() % 360;
            auto newDirection = glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection));
            instantiatePlayerBombParticle(world, playerTransform.getPosition() + (newDirection * glm::vec2(8, 8)), zindex, newDirection);
        }
    }
}

void bombSpreadSys(MainFixedSystem, World& world) {
    auto bombs = world.view<Velocity, BombSpread, const Collider>();

    auto [time] = world.resource<const Time>();

    for (auto [bombEnt, velocity, bombSpread, collider]: bombs) {
        if (bombSpread.canStopSpreading(time.fixedDelta())) {
            world.remove<BombSpread, Collider>(bombEnt);
        }

        velocity += bombSpread.getDirection() * bombSpread.getSpeed() * time.fixedDelta();
    }
}

void playerBombExplosionSys(MainFixedSystem, World& world) {
    auto bombs = world.view<Bomb, const Transform>(with<PlayerWeapon>);

    auto [time] = world.resource<const Time>();

    for (auto [bombEnt, bomb, transform]: bombs) {
        if (bomb.canExplode(time.fixedDelta())) {
            instantiatePlayerExplosionAttackParticle(world, transform.getPosition());
            world.destroy(bombEnt);
        }
    }
}