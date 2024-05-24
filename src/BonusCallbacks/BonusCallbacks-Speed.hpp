#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void speedBonusCallbackLvl1(World& world) {
    auto players = world.view<Speed>(with<Player>);

    for (auto [_, speed]: players) {
        speed.speed *= 1.10f;
    }
}