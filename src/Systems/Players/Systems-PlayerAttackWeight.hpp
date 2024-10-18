#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerAttackWeightSys(MainFixedSystem, World& world) {
    auto players = world.query<PlayerAttackWeight, Velocity>(without<IsPlayerDead>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, playerAttackWeight, velocity]: players) {
        if (playerAttackWeight.getIsForward()) {
            playerAttackWeight.canGoBackward(time.fixedDelta());
            velocity.vel += playerAttackWeight.getDirection() * playerAttackWeight.getSpeed() * time.fixedDelta();
        } else {
            if (playerAttackWeight.canStopBackward(time.fixedDelta())) {
                world.remove_components<PlayerAttackWeight>(playerEnt);
            }
            velocity.vel -= playerAttackWeight.getDirection() * playerAttackWeight.getSpeed() * time.fixedDelta();
        }
    }
}