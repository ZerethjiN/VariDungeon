#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void fireBallAttackSys(World& world) {
    auto fireballs = world.view<Velocity, const FireBall, const Speed>();

    auto [time] = world.getRes<const Time>();

    for (auto [_, velocity, fireball, speed]: fireballs) {
        velocity += fireball.getDirection() * speed.speed* time.fixedDelta();
    }
}