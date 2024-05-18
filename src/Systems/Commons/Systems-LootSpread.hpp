#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lootSpreadSys(World& world) {
    auto loots = world.view<Velocity, LootSpread, const Collider>();
    auto players = world.view(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [lootEnt, velocity, lootSpread, collider]: loots) {
        if (lootSpread.canStopSpreading(time.fixedDelta())) {
            Ent newPlayerEnt = 0;
            for (auto [playerEnt]: players) {
                newPlayerEnt = playerEnt;
            }
            world.del<LootSpread, Collider>(lootEnt);
            world.add(lootEnt,
                // Lootable(),
                Trigger(collider.col),
                // InnerMovement(0.5f, 4.f),
                // InnerMovementUp()
                LootAttract(128.f, newPlayerEnt)
            );
        }

        velocity += lootSpread.getDirection() * lootSpread.getSpeed() * time.fixedDelta();
    }
}