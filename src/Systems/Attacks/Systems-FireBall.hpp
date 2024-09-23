#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void fireBallHitSys(MainFixedSystem, World& world) {
    auto fireballs = world.view<const OnCollisionEnter, const Transform2D>(with<FireBall>);

    for (auto [fireballEnt, collisions, transform]: fireballs) {
        for (auto othEnt: collisions) {
            if (world.has<Wall>(othEnt)) {
                appliedCameraShake(world, 2.0f, 64.f, 2);
                instantiatePopHitParticle(world, transform.getPosition());
                world.delete_entity(fireballEnt);
                break;
            }
        }
    }
}

void fireBallAttackSys(MainFixedSystem, World& world) {
    auto fireballs = world.view<Velocity, const FireBall, const Speed>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, fireball, speed]: fireballs) {
        velocity += fireball.direction * speed.speed* time.fixedDelta();
    }
}