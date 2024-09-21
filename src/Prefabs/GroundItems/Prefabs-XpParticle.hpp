#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateXpParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.appendChildren(
        // Parent
        world.newEnt(
            XpGroundItem(1.f),
            Sprite(textureManager, xpParticleUV),
            Animation(xpParticleAnim, XpParticleAnimType::DEFAULT),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-1),
            Velocity(),
            Collider(-8 / 2, -8 / 2, 8, 8),
            LootSpread(spreadDuration, spreadDirection, spreadSpeed)
        ),
        // Children
        {
            world.newEnt(
                Sprite(textureManager, shadowUV),
                Animation(shadowAnim, ShadowAnimType::SMALL),
                Transform2D(
                    position + glm::vec2(0, 4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-2)
            )
        }
    );
}