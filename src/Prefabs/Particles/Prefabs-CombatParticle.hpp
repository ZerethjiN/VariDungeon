#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRepulseCombatParticle(World& world, const glm::vec2& position, int baseZIndex) {
    return world.newEnt(
        SpriteCreator(combatParticleUV),
        Animation(combatParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex - 1),
        LifeTime(0.2f)
    );
}

Ent instantiateSmallCombatParticle(World& world, const glm::vec2& position, int baseZIndex) {
    return world.newEnt(
        SpriteCreator(swordImpactUV, 2),
        Animation(swordImpactAnim, "Small"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex + 1),
        LifeTime(0.1f)
    );
}