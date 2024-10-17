#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void unmoveable_timer_sys(MainFixedSystem, World& world) {
    auto timers = world.view<UnmoveableTimer>(with<Unmoveable>);

    auto [time] = world.resource<const Time>();

    for (auto [timer_ent, unmoveable_timer]: timers) {
        if (unmoveable_timer.can_stop_unmove(time.fixedDelta())) {
            world.remove_components<UnmoveableTimer, Unmoveable>(timer_ent);
        }
    }
}