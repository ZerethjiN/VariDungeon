#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void daggerBonusCallbackLvl1(World& world) {
    auto players = world.view(with<Player>, without<PlayerDagger>);

    for (auto [playerEnt]: players) {
        world.add_component(playerEnt, PlayerDagger(2.5f));
    }
}