#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void inventoryBarShrinkSys(MainFixedSystem, World& world) {
    auto icons = world.view<ShrinkIcon, Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [iconEnt, shrinkIcon, transform]: icons) {
        if (shrinkIcon.canUnshrink(time.fixedDelta())) {
            transform.scale(-shrinkIcon.getShrink());
            world.remove<ShrinkIcon>(iconEnt);
        }
    }
}