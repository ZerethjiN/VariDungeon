#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void strengthBonusCallbackLvl1(World& world) {
    auto players = world.view<PlayerDamage>(with<Player>);

    for (auto [_, playerDamage]: players) {
        playerDamage *= 1.25f;
    }
}