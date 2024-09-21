#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBonusSphere(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.appendChildren(
        // Parent
        world.newEnt(
            BonusSphere(),
            Sprite(textureManager, bonusSphereUV),
            Animation(bonusSphereAnim, BonusSphereAnimType::DEFAULT),
            Transform2D(
                position + glm::vec2(-8, -12),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-1),
            InnerMovement(1, 2),
            InnerMovementUp(),
            Lootable(),
            Velocity(),
            Trigger(-8 / 2, -8 / 2, 8, 8)
        ),
        // Children
        {
            world.newEnt(
                Sprite(textureManager, shadowUV),
                Animation(shadowAnim, ShadowAnimType::SMALL),
                Transform2D(
                    position + glm::vec2(-8, -4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-2)
            )
        }
    );
}