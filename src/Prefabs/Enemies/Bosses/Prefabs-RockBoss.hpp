#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSmallCrystalParticle(World&, const glm::vec2&, float, const glm::vec2&);

Ent instantiateRockBoss(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    auto bossEnt = world.create_entity(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        RockBoss(
            /*StunDuration:*/ 2.0f,
            /*SmallCrystalDuration:*/ 1.5f,
            /*GroundCrystalDuration:*/ 4.0f,
            /*GroundCrystalDurationP2:*/ 2.5f,
            /*RollSpeedCoeff:*/ 8.0f
        ),
        IsRockBossRoll(),
        Unhittable(),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, rockBossUV),
        Animation(rockBossAnim, RockBossAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 4, 6}}),
        ZIndex(0),
        Life(20),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );

    // world.appendChildren(bossEnt, {
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(-16, -16), 16.f, glm::vec2(-16, -16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(16, -16), 16.f, glm::vec2(16, -16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(-16, 16), 16.f, glm::vec2(-16, 16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(16, 16), 16.f, glm::vec2(16, 16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(0, -16), 16.f, glm::vec2(0, -16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(0, 16), 16.f, glm::vec2(0, 16)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(-16, 0), 16.f, glm::vec2(-16, 0)),
    //     instantiateSmallCrystalParticle(world, position + glm::vec2(16, 0), 16.f, glm::vec2(16, 0)),
    // });

    return bossEnt;
}