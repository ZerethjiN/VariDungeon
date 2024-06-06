#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void invincibleFramesSys(MainFixedSystem, World& world) {
    auto invincibles = world.view<InvincibleFrame, Transform>();

    auto [time] = world.resource<const Time>();

    for (auto [invincibleEnt, invincible, transform]: invincibles) {
        if (invincible.canStop(time.fixedDelta())) {
            transform.scale(-invincible.getScale());
            world.del<InvincibleFrame>(invincibleEnt);
        }
    }
}