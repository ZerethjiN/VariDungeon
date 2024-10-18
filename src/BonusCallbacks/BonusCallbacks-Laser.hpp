#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void laserBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query(with<Player>, without<PlayerLaser>);

    for (auto [playerEnt]: players) {
        world.add_components(playerEnt, PlayerLaser(0.75f));
    }
}

void laserBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<PlayerLaser>(with<Player>);

    for (auto [_, player_laser]: players) {
        player_laser.cooldown = 0.65f;
    }
}

void laserBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<PlayerLaser>(with<Player>);

    for (auto [_, player_laser]: players) {
        player_laser.cooldown = 0.50f;
    }
}