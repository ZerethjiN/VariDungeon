#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void laserMovementSys(MainFixedSystem, World& world) {
    auto lasers = world.view<Velocity, const Speed, const Laser>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, speed, laser]: lasers) {
        velocity.vel += laser.direction * speed.speed * time.fixedDelta();
    }
}

void laserHitSys(MainFixedSystem, World& world) {
    auto lasers = world.view<const OnCollisionEnter, const Transform2D>(with<Laser>);

    for (auto [laserEnt, collisions, transform]: lasers) {
        for (auto othEnt: collisions) {
            if (world.has<Wall>(othEnt)) {
                appliedCameraShake(world, 2.0f, 64.f, 2);
                instantiatePopHitParticle(world, transform.getPosition());
                world.delete_entity(laserEnt);
                break;
            }
        }
    }
}