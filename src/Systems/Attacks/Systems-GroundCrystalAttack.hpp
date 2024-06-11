#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void groundCrystalAttackCrossSys(MainFixedSystem, World& world) {
    auto crystals = world.view<IsGroundCrystalAttackCross, Animation, const GroundCrystalAttack>();

    auto [time] = world.resource<const Time>();

    for (auto [crystalEnt, isGroundCrystalAttackCross, animation, groundCrystalAttack]: crystals) {
        if (isGroundCrystalAttackCross.canSwitchState(time.fixedDelta())) {
            world.remove<IsGroundCrystalAttackCross, Animation>(crystalEnt);
            world.add(crystalEnt,
                Trigger(-12 / 2, -12 / 2, 12, 12),
                LifeTime(groundCrystalAttack.mineralDuration)
            );
            animation.play("Crystal");
        }
    }
}