#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void smallCrystalRotationSys(MainFixedSystem, World& world) {
    auto crystals = world.query<Transform2D, const SmallCrystalRotation>();

    auto [time] = world.resource<const Time>();

    for (auto [crystalEnt, smallCrystalTransform, smallCrystal]: crystals) {
        if (auto optParent = world.get_parent(crystalEnt)) {
            auto parentEnt = optParent.value();

            if (auto opt = world.get_components<const Transform2D>(parentEnt)) {
                auto [parentTransform] = opt.value();

                auto diff = parentTransform.getPosition() - smallCrystalTransform.getPosition();

                smallCrystalTransform.rotate(smallCrystal.rotationSpeed * time.fixedDelta());

                smallCrystalTransform.move(
                    rotateAround(-diff, diff, smallCrystal.rotationSpeed * time.fixedDelta())
                );
            }
        }
    }
}

void smallCrystalThrowSys(MainFixedSystem, World& world) {
    auto crystals = world.query<Velocity, const Transform2D, const SmallCrystalThrow>();

    auto [time] = world.resource<const Time>();

    for (auto [crystalEnt, velocity, transform, crystal]: crystals) {
        velocity.vel += glm::normalize(crystal.lastPlayerPosition - transform.getPosition()) * crystal.speed * time.fixedDelta();
    
        if (glm::distance(crystal.lastPlayerPosition, transform.getPosition()) < 8.f) {
            world.delete_entity(crystalEnt);
        }
    }
}