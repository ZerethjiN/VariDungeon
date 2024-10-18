#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void warp_opening_sys(MainFixedSystem, World& world) {
    auto warps = world.query<WarpOpening, Animation>(with<Warp>, without<Trigger>);

    auto [time] = world.resource<const Time>();

    for (auto [warp_ent, warp_opening, animation]: warps) {
        if (warp_opening.canSwitchState(time.fixedDelta())) {
            animation.play(WarpAnimType::DEFAULT);
            world.remove_components<WarpOpening>(warp_ent);
            world.add_components(warp_ent, Trigger(-16 / 2, -16 / 2, 16, 16));
        }
    }
}

void warp_sys(MainFixedSystem, World& world) {
    auto warps = world.query<const OnCollisionEnter>(with<Warp>);

    for (auto [_, collisions]: warps) {
        for (auto othEnt: collisions) {
            if (world.has_components<Player>(othEnt)) {
                if (!world.has_components<Unmoveable>(othEnt)) {
                    world.add_components(othEnt,
                        UnmoveableTimer(1.75f),
                        Unmoveable()
                    );
                }
                if (auto opt = world.get_components<PlayerFloor>(othEnt)) {
                    auto [playerFloor] = opt.value();
                    if (playerFloor.merchant_floors.contains(playerFloor.cur_floor)) {
                        playerFloor.can_load_merchant_room = true;
                        playerFloor.can_load_final_boss_room = false;
                        playerFloor.merchant_floors.erase(playerFloor.cur_floor);
                    } else if (playerFloor.final_boss_floors.contains(playerFloor.cur_floor)) {
                        playerFloor.can_load_merchant_room = false;
                        playerFloor.can_load_final_boss_room = true;
                        playerFloor.final_boss_floors.erase(playerFloor.cur_floor);
                    } else {
                        playerFloor.can_load_merchant_room = false;
                        playerFloor.can_load_final_boss_room = false;
                        playerFloor.cur_floor++;
                    }
                }
                world.loadScene(testScene);
            }
        }
    }
}