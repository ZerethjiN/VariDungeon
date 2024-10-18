#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void bombBonusCallbackLvl1(World& world) {
    auto players = world.query(with<Player>, without<PlayerBomb>);

    for (auto [playerEnt]: players) {
        world.add_components(playerEnt, PlayerBomb(2.5f));
    }
}