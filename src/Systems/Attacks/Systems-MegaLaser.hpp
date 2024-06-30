#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void megaLaserRotationSys(MainFixedSystem, World& world) {
    auto lasers = world.view<Transform, const MegaLaser>();

    auto [time] = world.resource<const Time>();

    for (auto [_, laserTransform, laser]: lasers) {
        laserTransform.rotate(laser.rotationSpeed * time.fixedDelta());
    }
}