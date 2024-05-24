#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void attackSpeedBonusCallbackLvl1(World& world) {
    auto players = world.view<PlayerAttackCooldown>(with<Player>);

    for (auto [_, playerAttackCooldown]: players) {
        playerAttackCooldown.reduceCooldown(0.05f);
    }
}