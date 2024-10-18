#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void bombBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query(with<Player>, without<PlayerBomb>);

    for (auto [player_ent]: players) {
        world.add_components(player_ent, PlayerBomb(2.5f));
    }
}

void bombBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<PlayerBomb>(with<Player>);

    for (auto [_, player_bomb]: players) {
        player_bomb.cooldown -= 0.5f;
    }
}

void bombBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<PlayerBomb>(with<Player>);

    for (auto [_, player_bomb]: players) {
        player_bomb.cooldown -= 0.5f;
    }
}