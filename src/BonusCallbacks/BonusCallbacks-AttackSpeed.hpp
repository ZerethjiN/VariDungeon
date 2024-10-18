#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void attackSpeedBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<PlayerAttackCooldown>(with<Player>);

    for (auto [_, player_attack_cooldown]: players) {
        player_attack_cooldown.reduceCooldown(0.05f);
    }
}

void attackSpeedBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<PlayerAttackCooldown>(with<Player>);

    for (auto [_, player_attack_cooldown]: players) {
        player_attack_cooldown.reduceCooldown(0.05f);
    }
}

void attackSpeedBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<PlayerAttackCooldown>(with<Player>);

    for (auto [_, player_attack_cooldown]: players) {
        player_attack_cooldown.reduceCooldown(0.05f);
    }
}