#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lightningBallBonusCallbackLvl1(World& world) {
    auto players = world.query(with<Player>, without<PlayerLightningBall>);

    for (auto [playerEnt]: players) {
        world.add_components(playerEnt, PlayerLightningBall(2.5f));
    }
}