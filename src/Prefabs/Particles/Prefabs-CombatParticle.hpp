#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRepulseCombatParticle(World& world, const glm::vec2& position, int baseZIndex) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, combatParticleUV),
        Animation(combatParticleAnim, CombatParticleAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex - 1),
        LifeTime(combatParticleAnim[CombatParticleAnimType::DEFAULT].getTotalDuration())
    );
}

Ent instantiateSmallCombatParticle(World& world, const glm::vec2& position, int baseZIndex) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, swordImpactUV, 2),
        Animation(swordImpactAnim, SwordImpactAnimType::SMALL),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex + 1),
        LifeTime(swordImpactAnim[SwordImpactAnimType::SMALL].getTotalDuration())
    );
}