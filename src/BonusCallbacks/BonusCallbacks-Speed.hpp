#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void speedBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<Speed>(with<Player>);

    for (auto [_, speed]: players) {
        speed.speed *= 1.08f;
    }
}

void speedBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<Speed>(with<Player>);

    for (auto [_, speed]: players) {
        speed.speed *= 1.08f;
    }
}

void speedBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<Speed>(with<Player>);

    for (auto [_, speed]: players) {
        speed.speed *= 1.08f;
    }
}