#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lootSpreadSys(World& world) {
    auto loots = world.view<Velocity, LootSpread, const Collider>();

    auto [time] = world.getRes<const Time>();

    for (auto [lootEnt, velocity, lootSpread, collider]: loots) {
        if (lootSpread.canStopSpreading(time.fixedDelta())) {
            world.del<LootSpread, Collider>(lootEnt);
            world.add(lootEnt,
                Lootable(),
                Trigger(collider.col),
                InnerMovement(0.5f, 4.f),
                InnerMovementUp()
            );
        }

        velocity += lootSpread.getDirection() * lootSpread.getSpeed() * time.fixedDelta();
    }
}