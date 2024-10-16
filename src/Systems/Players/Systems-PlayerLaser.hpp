#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerLaserSys(MainFixedSystem, World& world) {
    auto players = world.query<PlayerLaser>(without<IsPlayerDead>);

    auto [time] = world.resource<const Time>();

    for (auto [_, playerLaser]: players) {
        playerLaser.updateTime(time.fixedDelta());
    }
}