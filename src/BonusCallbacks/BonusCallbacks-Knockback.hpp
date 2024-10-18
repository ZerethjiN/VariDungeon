#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void knockbackBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<PlayerKnockbackStrength>(with<Player>);

    for (auto [_, player_knockback_strength]: players) {
        player_knockback_strength.increaseKnockbackStrength(16.f);
    }
}

void knockbackBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<PlayerKnockbackStrength>(with<Player>);

    for (auto [_, player_knockback_strength]: players) {
        player_knockback_strength.increaseKnockbackStrength(16.f);
    }
}

void knockbackBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<PlayerKnockbackStrength>(with<Player>);

    for (auto [_, player_knockback_strength]: players) {
        player_knockback_strength.increaseKnockbackStrength(16.f);
    }
}