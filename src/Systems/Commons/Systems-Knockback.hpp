#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void knockbackSys(MainFixedSystem, World& world) {
    auto knockbacks = world.query<Knockback, Velocity>();

    auto [time] = world.resource<const Time>();

    for (auto [knockbackEnt, knockback, velocity]: knockbacks) {
        auto tmp = std::max(knockback.getSpeed() - ((2.f / knockback.getDuration()) * std::fabs(knockback.getCurTime() - (0.5f / knockback.getDuration()))), 0.f);

        velocity += knockback.getDirection() * tmp * time.fixedDelta();

        if (knockback.canStopKnockback(time.fixedDelta())) {
            world.remove_components<Knockback>(knockbackEnt);
        }
    }
}