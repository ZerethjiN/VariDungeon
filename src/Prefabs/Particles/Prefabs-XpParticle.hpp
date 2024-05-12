#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateXpParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    return world.newEnt(
        SpriteCreator(xpParticleUV),
        Animation(xpParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Velocity(),
        Collider(-8 / 2, -8 / 2, 8, 8),
        LootSpread(spreadDuration, spreadDirection, spreadSpeed)
    );
}