#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGroundCrystalAttack(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        GroundCrystalAttack(
            /*CrossDuration:*/ 0.75f,
            /*MineralDuration:*/ 1.0f
        ),
        IsGroundCrystalAttackCross(0.75f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, groundCrystalAttackUV),
        Animation(groundCrystalAttackAnim, GroundCrystalAttackAnimType::CROSS),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        )
    );
}