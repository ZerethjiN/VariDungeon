#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void fireBallHitSys(World& world) {
    auto fireballs = world.view<const OnCollisionEnter, const Transform>(with<FireBall>);

    for (auto [fireballEnt, collisions, transform]: fireballs) {
        for (auto othEnt: collisions) {
            if (world.has<Wall>(othEnt)) {
                appliedCameraShake(world, 2.0f, 64.f, 2);
                instantiatePopHitParticle(world, transform.getPosition());
                world.destroy(fireballEnt);
                break;
            }
        }
    }
}

void fireBallAttackSys(World& world) {
    auto fireballs = world.view<Velocity, const FireBall, const Speed>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, fireball, speed]: fireballs) {
        velocity += fireball.getDirection() * speed.speed* time.fixedDelta();
    }
}