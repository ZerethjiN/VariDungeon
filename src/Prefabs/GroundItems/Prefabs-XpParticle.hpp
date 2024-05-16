#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateXpParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto xpEnt = world.newEnt(
        XpGroundItem(1.f),
        SpriteCreator(xpParticleUV),
        Animation(xpParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1),
        Velocity(),
        Collider(-8 / 2, -8 / 2, 8, 8),
        LootSpread(spreadDuration, spreadDirection, spreadSpeed)
    );

    world.appendChildren(xpEnt, {
        world.newEnt(
            SpriteCreator(shadowUV),
            Animation(shadowAnim, "Small"),
            Transform(
                position + glm::vec2(0, 4),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-2)
        )
    });

    return xpEnt;
}