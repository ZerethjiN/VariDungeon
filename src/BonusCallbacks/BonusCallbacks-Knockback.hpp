#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void knockbackBonusCallbackLvl1(World& world) {
    auto players = world.view<PlayerKnockbackStrength>(with<Player>);

    for (auto [_, playerKnockbackStrength]: players) {
        playerKnockbackStrength.increaseKnockbackStrength(16.f);
    }
}