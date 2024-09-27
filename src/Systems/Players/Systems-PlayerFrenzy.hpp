#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerFrenzySys(MainFixedSystem, World& world) {
    auto players = world.view<PlayerFrenzy, PlayerAttackCooldown, Speed>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, playerFrenzy, playerAttackSpeed, playerSpeed]: players) {
        if (playerFrenzy.canStop(time.fixedDelta())) {
            playerAttackSpeed /= 1.25f;
            playerSpeed.speed /= 1.5f;
            world.remove_components<PlayerFrenzy>(playerEnt);
        }
    }
}