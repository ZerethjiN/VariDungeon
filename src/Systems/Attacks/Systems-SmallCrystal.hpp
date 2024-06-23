#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void smallCrystalRotationSys(MainFixedSystem, World& world) {
    auto crystals = world.view<Transform, const SmallCrystalRotation>();

    auto [time] = world.resource<const Time>();

    for (auto [crystalEnt, smallCrystalTransform, smallCrystal]: crystals) {
        if (auto optParent = world.getParent(crystalEnt)) {
            auto parentEnt = optParent.value();

            if (auto opt = world.get<const Transform>(parentEnt)) {
                auto [parentTransform] = opt.value();

                auto diff = parentTransform.getPosition() - smallCrystalTransform.getPosition();

                smallCrystalTransform.rotate(smallCrystal.getRotationSpeed() * time.fixedDelta());

                smallCrystalTransform.move(
                    rotateAround(-diff, diff, smallCrystal.getRotationSpeed() * time.fixedDelta())
                );
            }
        }
    }
}

void smallCrystalThrowSys(MainFixedSystem, World& world) {
    auto crystals = world.view<Velocity, const Transform, const SmallCrystalThrow>();

    auto [time] = world.resource<const Time>();

    for (auto [crystalEnt, velocity, transform, crystal]: crystals) {
        velocity.vel += glm::normalize(crystal.lastPlayerPosition - transform.getPosition()) * crystal.speed * time.fixedDelta();
    
        if (glm::distance(crystal.lastPlayerPosition, transform.getPosition()) < 8.f) {
            world.destroy(crystalEnt);
        }
    }
}