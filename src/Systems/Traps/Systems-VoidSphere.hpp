#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void voidSphereOffSys(MainFixedSystem, World& world) {
    auto spheres = world.query<IsVoidSphereOff, Animation, const VoidSphere, const ZIndex, const Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOff, animation, voidSphere, zindex, transform]: spheres) {
        if (isVoidSphereOff.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<VoidSphere>(sphereEnt);
            } else {
                world.remove_components<IsVoidSphereOff>(sphereEnt);
                world.add_components(sphereEnt, IsVoidSphereOn(voidSphere.voidSphereOnDuration));
                world.append_children(sphereEnt, {
                    instantiateAttractParticle(world, transform.getPosition(), zindex + 1, voidSphere.voidSphereOnDuration)
                });
                animation.play(VoidSphereAnimType::ON);
            }
        }
    }
}

void voidSphereOnSys(MainFixedSystem, World& world) {
    auto spheres = world.query<IsVoidSphereOn, Animation, const VoidSphere, const Transform2D>();
    auto players = world.query<Velocity, const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [sphereEnt, isVoidSphereOn, animation, voidSphere, enemyTransform]: spheres) {
        if (isVoidSphereOn.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<VoidSphere>(sphereEnt);
            } else {
                world.remove_components<IsVoidSphereOn>(sphereEnt);
                world.add_components(sphereEnt, IsVoidSphereOff(voidSphere.voidSphereOffDuration));
            }
            animation.play(VoidSphereAnimType::OFF);
            continue;
        }

        for (auto [_, playerVelocity, playerTransform]: players) {
            playerVelocity.vel += glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()) * voidSphere.attractStrength * time.fixedDelta();
        }
    }
}