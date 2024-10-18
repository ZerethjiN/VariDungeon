#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void spikeDownSys(MainFixedSystem, World& world) {
    auto spikes = world.query<IsSpikeDown, Animation, const Spike>();

    auto [time] = world.resource<const Time>();

    for (auto [spikeEnt, isSpikeDown, animation, spike]: spikes) {
        if (isSpikeDown.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<Spike>(spikeEnt);
            } else {
                world.remove_components<IsSpikeDown>(spikeEnt);
                world.add_components(spikeEnt, IsSpikeUp(spike.spikeUpDuration));
                animation.play(SpikeAnimType::UP);
                if (!world.has_components<Trigger>(spikeEnt)) {
                    world.add_components(spikeEnt, Trigger(-8 / 2, -8 / 2, 8, 8));
                }
            }
        }
    }
}

void spikeUpSys(MainFixedSystem, World& world) {
    auto spikes = world.query<IsSpikeUp, Animation, const Spike>();

    auto [time] = world.resource<const Time>();

    for (auto [spikeEnt, isSpikeUp, animation, spike]: spikes) {
        if (isSpikeUp.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<Spike, IsSpikeUp>(spikeEnt);
            } else {
                world.remove_components<IsSpikeUp>(spikeEnt);
                world.add_components(spikeEnt, IsSpikeDown(spike.spikeDownDuration));
            }
            animation.play(SpikeAnimType::DOWN);
            if (world.has_components<Trigger>(spikeEnt)) {
                world.remove_components<Trigger>(spikeEnt);
            }
        }
    }
}