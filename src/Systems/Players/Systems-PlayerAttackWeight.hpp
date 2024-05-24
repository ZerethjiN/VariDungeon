#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerAttackWeightSys(World& world) {
    auto players = world.view<PlayerAttackWeight, Velocity>();

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, playerAttackWeight, velocity]: players) {
        if (playerAttackWeight.getIsForward()) {
            playerAttackWeight.canGoBackward(time.fixedDelta());
            velocity.vel += playerAttackWeight.getDirection() * playerAttackWeight.getSpeed() * time.fixedDelta();
        } else {
            if (playerAttackWeight.canStopBackward(time.fixedDelta())) {
                world.del<PlayerAttackWeight>(playerEnt);
            }
            velocity.vel -= playerAttackWeight.getDirection() * playerAttackWeight.getSpeed() * time.fixedDelta();
        }
    }
}