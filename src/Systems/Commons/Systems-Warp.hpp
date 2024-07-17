#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void warpSys(MainFixedSystem, World& world) {
    auto warps = world.view<const OnCollisionEnter>(with<Warp>);

    for (auto [_, collisions]: warps) {
        for (auto othEnt: collisions) {
            if (world.has<Player>(othEnt)) {
                if (auto opt = world.get<PlayerFloor>(othEnt)) {
                    auto [playerFloor] = opt.value();
                    if (playerFloor.merchantFloors.contains(playerFloor.curFloor)) {
                        playerFloor.canLoadMerchantRoom = true;
                        playerFloor.merchantFloors.erase(playerFloor.curFloor);
                    } else {
                        playerFloor.canLoadMerchantRoom = false;
                        playerFloor.curFloor++;
                    }
                }
                world.loadScene(testScene);
            }
        }
    }
}