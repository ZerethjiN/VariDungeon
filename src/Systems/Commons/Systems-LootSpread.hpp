#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lootSpreadSys(MainFixedSystem, World& world) {
    auto loots = world.query<Velocity, LootSpread, const Collider>();
    auto players = world.query(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [lootEnt, velocity, lootSpread, collider]: loots) {
        if (lootSpread.canStopSpreading(time.fixedDelta())) {
            Ent newPlayerEnt = 0;
            for (auto [playerEnt]: players) {
                newPlayerEnt = playerEnt;
            }
            world.remove_components<LootSpread, Collider>(lootEnt);
            world.add_components(lootEnt,
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