#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerLightningBallSys(MainFixedSystem, World& world) {
    auto players = world.view<PlayerLightningBall, const Transform>();

    auto [time] = world.resource<const Time>();

    for (auto [_, playerDagger, playerTransform]: players) {
        if (playerDagger.canSpawnLightningBall(time.fixedDelta()) && !world.view(with<Enemy>).empty()) {
            glm::vec2 minDirection;
            float minDistance = std::numeric_limits<float>::max();
            for (auto [_, enemyTransform]: world.view<const Transform>(with<Enemy>)) {
                auto newDistance = glm::distance(enemyTransform.getPosition(), playerTransform.getPosition());
                if (newDistance < minDistance) {
                    minDistance = newDistance;
                    minDirection = glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition());
                }
            }

            instantiateLightningBallParticle(world, playerTransform.getPosition(), minDirection, 64.f);
        }
    }
}

void lightballMovementSys(MainFixedSystem, World& world) {
    auto balls = world.view<Velocity, const Speed, const LightningBall>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, speed, lightball]: balls) {
        velocity.vel += lightball.direction * speed.speed * time.fixedDelta();
    }
}

void lightningBallHitSys(MainFixedSystem, World& world) {
    auto balls = world.view<const OnCollisionEnter, const Transform>(with<LightningBall>);

    for (auto [ballEnt, collisions, transform]: balls) {
        for (auto othEnt: collisions) {
            if (world.has<Wall>(othEnt) || world.has<Enemy>(othEnt)) {
                world.destroy(ballEnt);
                break;
            }
        }
    }
}