#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGroundCrystalAttack(World& world, const glm::vec2& position) {
    return world.newEnt(
        GroundCrystalAttack(
            /*CrossDuration:*/ 0.75f,
            /*MineralDuration:*/ 1.0f
        ),
        IsGroundCrystalAttackCross(0.75f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(groundCrystalAttackUV),
        Animation(groundCrystalAttackAnim, "Cross"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        )
    );
}