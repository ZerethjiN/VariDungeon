#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void voidSphereOffSys(MainFixedSystem, World& world) {
    auto spheres = world.view<IsVoidSphereOff, Animation, const VoidSphere, const ZIndex, const Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOff, animation, voidSphere, zindex, transform]: spheres) {
        if (isVoidSphereOff.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<VoidSphere>(sphereEnt);
            } else {
                world.remove<IsVoidSphereOff>(sphereEnt);
                world.add(sphereEnt, IsVoidSphereOn(voidSphere.voidSphereOnDuration));
                world.appendChildren(sphereEnt, {
                    instantiateAttractParticle(world, transform.getPosition(), zindex + 1, voidSphere.voidSphereOnDuration)
                });
                animation.play(VoidSphereAnimType::ON);
            }
        }
    }
}

void voidSphereOnSys(MainFixedSystem, World& world) {
    auto spheres = world.view<IsVoidSphereOn, Animation, const VoidSphere, const Transform2D>();
    auto players = world.view<Velocity, const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOn, animation, voidSphere, enemyTransform]: spheres) {
        if (isVoidSphereOn.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<VoidSphere>(sphereEnt);
            } else {
                world.remove<IsVoidSphereOn>(sphereEnt);
                world.add(sphereEnt, IsVoidSphereOff(voidSphere.voidSphereOffDuration));
            }
            animation.play(VoidSphereAnimType::OFF);
            continue;
        }

        for (auto [_, playerVelocity, playerTransform]: players) {
            playerVelocity.vel += glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()) * voidSphere.attractStrength * time.fixedDelta();
        }
    }
}