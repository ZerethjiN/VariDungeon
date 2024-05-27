#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void inventoryBarShrinkSys(World& world) {
    auto icons = world.view<ShrinkIcon, Transform>();

    auto [time] = world.resource<const Time>();

    for (auto [iconEnt, shrinkIcon, transform]: icons) {
        if (shrinkIcon.canUnshrink(time.fixedDelta())) {
            transform.scale(-shrinkIcon.getShrink());
            world.del<ShrinkIcon>(iconEnt);
        }
    }
}