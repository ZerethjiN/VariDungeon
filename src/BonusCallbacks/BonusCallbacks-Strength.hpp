#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void strengthBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<PlayerDamage>(with<Player>);

    for (auto [_, playerDamage]: players) {
        playerDamage *= 1.25f;
    }
}

void strengthBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<PlayerDamage>(with<Player>);

    for (auto [_, playerDamage]: players) {
        playerDamage *= 1.25f;
    }
}

void strengthBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<PlayerDamage>(with<Player>);

    for (auto [_, playerDamage]: players) {
        playerDamage *= 1.25f;
    }
}