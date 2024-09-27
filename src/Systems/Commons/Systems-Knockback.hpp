#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void knockbackSys(MainFixedSystem, World& world) {
    auto knockbacks = world.view<Knockback, Velocity>();

    auto [time] = world.resource<const Time>();

    for (auto [knockbackEnt, knockback, velocity]: knockbacks) {
        velocity += knockback.getDirection() * knockback.getSpeed() * time.fixedDelta();

        if (knockback.canStopKnockback(time.fixedDelta())) {
            world.remove_components<Knockback>(knockbackEnt);
        }
    }
}