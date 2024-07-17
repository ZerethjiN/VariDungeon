#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void chestOpenSys(MainFixedSystem, World& world) {
    auto chests = world.view<const Transform, const OnCollisionEnter>(with<Chest>);

    for (auto [chestEnt, chestTransform, collisions]: chests) {
        for (auto othEnt: collisions) {
            if (world.has<Player>(othEnt)) {
                instantiateWarp(world, chestTransform.getPosition() + glm::vec2(0, 32));
                world.destroy(chestEnt);
            }
        }
    }
}
