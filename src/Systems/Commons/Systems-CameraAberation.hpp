#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void cameraAberationSys(MainFixedSystem, World& world) {
    auto aberations = world.view<CameraAberation>();

    auto [time] = world.resource<const Time>();

    for (auto [aberationEnt, aberation]: aberations) {
        if (aberation.canStopAberation(time.fixedDelta())) {
            world.remove<CameraAberation>(aberationEnt);
        }
    }
}