#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerBombSys(MainFixedSystem, World& world) {
    auto players = world.view<PlayerBomb, const Transform2D, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [_, playerBomb, playerTransform, zindex]: players) {
        if (playerBomb.canSpawnBomb(time.fixedDelta()) && !world.view(with<Enemy>).empty()) {
            glm::vec2 minDistance(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            float distance = std::numeric_limits<float>::max();

            for (auto [_, enemyTransform]: world.view<const Transform2D>(with<Enemy>)) {
                if (glm::distance(enemyTransform.getPosition(), glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())) < distance) {
                    minDistance = enemyTransform.getPosition();
                    distance = glm::distance(enemyTransform.getPosition(), glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()));
                }
            }

            auto newDirection = glm::normalize(minDistance);
            instantiatePlayerBombParticle(world, playerTransform.getPosition() + (newDirection * 16.f), zindex, newDirection);
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

        velocity += bombSpread.direction * bombSpread.speed * time.fixedDelta();
    }
}

void playerBombExplosionSys(MainFixedSystem, World& world) {
    auto bombs = world.view<Bomb, const Transform2D>(with<PlayerWeapon>);

    auto [time] = world.resource<const Time>();

    for (auto [bombEnt, bomb, transform]: bombs) {
        if (bomb.canExplode(time.fixedDelta())) {
            instantiatePlayerExplosionAttackParticle(world, transform.getPosition());
            world.destroy(bombEnt);
        }
    }
}