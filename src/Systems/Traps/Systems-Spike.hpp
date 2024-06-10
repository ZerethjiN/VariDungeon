#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void spikeDownSys(MainFixedSystem, World& world) {
    auto spikes = world.view<IsSpikeDown, Sprite, const Spike>();

    auto [time] = world.resource<const Time>();

    for (auto [spikeEnt, isSpikeDown, sprite, spike]: spikes) {
        if (isSpikeDown.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<Spike>(spikeEnt);
            } else {
                world.remove<IsSpikeDown>(spikeEnt);
                world.add(spikeEnt, IsSpikeUp(spike.spikeUpDuration));
                sprite.setTextureRect(spikeUV[1]);
                if (!world.has<Trigger>(spikeEnt)) {
                    world.add(spikeEnt, Trigger(-8 / 2, -8 / 2, 8, 8));
                }
            }
        }
    }
}

void spikeUpSys(MainFixedSystem, World& world) {
    auto spikes = world.view<IsSpikeUp, Sprite, const Spike>();

    auto [time] = world.resource<const Time>();

    for (auto [spikeEnt, isSpikeUp, sprite, spike]: spikes) {
        if (isSpikeUp.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<Spike>(spikeEnt);
                sprite.setTextureRect(spikeUV[0]);
            } else {
                world.remove<IsSpikeUp>(spikeEnt);
                sprite.setTextureRect(spikeUV[0]);
                world.add(spikeEnt, IsSpikeDown(spike.spikeDownDuration));
                if (world.has<Trigger>(spikeEnt)) {
                    world.remove<Trigger>(spikeEnt);
                }
            }
        }
    }
}