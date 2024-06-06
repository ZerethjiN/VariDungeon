#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void voidSphereOffSys(MainFixedSystem, World& world) {
    auto spheres = world.view<IsVoidSphereOff, Animation, const VoidSphere, const ZIndex, const Transform>();

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOff, animation, voidSphere, zindex, transform]: spheres) {
        if (isVoidSphereOff.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.del<VoidSphere>(sphereEnt);
            } else {
                world.del<IsVoidSphereOff>(sphereEnt);
                world.add(sphereEnt, IsVoidSphereOn(voidSphere.voidSphereOnDuration));
                world.appendChildren(sphereEnt, {
                    instantiateAttractParticle(world, transform.getPosition(), zindex + 1, voidSphere.voidSphereOnDuration)
                });
                animation.play("On");
            }
        }
    }
}

void voidSphereOnSys(MainFixedSystem, World& world) {
    auto spheres = world.view<IsVoidSphereOn, Animation, const VoidSphere, const Transform>();
    auto players = world.view<Velocity, const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOn, animation, voidSphere, enemyTransform]: spheres) {
        if (isVoidSphereOn.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.del<VoidSphere>(sphereEnt);
            } else {
                world.del<IsVoidSphereOn>(sphereEnt);
                world.add(sphereEnt, IsVoidSphereOff(voidSphere.voidSphereOffDuration));
            }
            animation.play("Off");
            continue;
        }

        for (auto [_, playerVelocity, playerTransform]: players) {
            playerVelocity.vel += glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()) * voidSphere.attractStrength * time.fixedDelta();
        }
    }
}