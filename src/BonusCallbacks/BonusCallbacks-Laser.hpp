#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void laserBonusCallbackLvl1(World& world) {
    auto players = world.view(with<Player>, without<PlayerLaser>);

    for (auto [playerEnt]: players) {
        world.add(playerEnt, PlayerLaser(0.75f));
    }
}