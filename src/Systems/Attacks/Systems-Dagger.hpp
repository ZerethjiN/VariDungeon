#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerDaggerSys(MainFixedSystem, World& world) {
    auto players = world.query<PlayerDagger, const Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [_, playerDagger, playerTransform]: players) {
        if (playerDagger.canSpawnDagger(time.fixedDelta()) && !world.query(with<Enemy>).empty()) {
            instantiateDaggerParticle(world, playerTransform.getPosition(), glm::vec2(1, -1), 0 * 90.f + 45.f, 128.f);
            instantiateDaggerParticle(world, playerTransform.getPosition(), glm::vec2(1, 1), 1 * 90.f + 45.f, 128.f);
            instantiateDaggerParticle(world, playerTransform.getPosition(), glm::vec2(-1, 1), 2 * 90.f + 45.f, 128.f);
            instantiateDaggerParticle(world, playerTransform.getPosition(), glm::vec2(-1, -1), 3 * 90.f + 45.f, 128.f);
        }
    }
}

void daggerMovementSys(MainFixedSystem, World& world) {
    auto daggers = world.query<Velocity, const Speed, const Dagger>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, speed, dagger]: daggers) {
        velocity.vel += dagger.direction * speed.speed * time.fixedDelta();
    }
}