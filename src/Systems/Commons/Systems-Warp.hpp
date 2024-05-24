#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void warpSys(World& world) {
    auto warps = world.view<const OnCollisionEnter>(with<Warp>);

    for (auto [_, collisions]: warps) {
        for (auto othEnt: collisions) {
            if (world.has<Player>(othEnt)) {
                generateDungeon(world, glm::vec2(0, 0));
            }
        }
    }
}