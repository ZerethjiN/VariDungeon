#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void megaLaserRotationSys(MainFixedSystem, World& world) {
    auto lasers = world.view<Transform, const MegaLaser>();

    auto [time] = world.resource<const Time>();

    for (auto [laserEnt, laserTransform, laser]: lasers) {
        if (auto optParent = world.getParent(laserEnt)) {
            auto parentEnt = optParent.value();

            if (auto opt = world.get<const Transform>(parentEnt)) {
                auto [parentTransform] = opt.value();

                auto diff = parentTransform.getPosition() - laserTransform.getPosition();

                laserTransform.rotate(laser.rotationSpeed * time.fixedDelta());

                // laserTransform.move(
                //     rotateAround(-diff, diff, laser.rotationSpeed * time.fixedDelta())
                // );
            }
        }
    }
}