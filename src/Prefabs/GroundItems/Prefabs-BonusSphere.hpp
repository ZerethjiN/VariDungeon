#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBonusSphere(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            BonusSphere(),
            Sprite(textureManager, bonusSphereUV),
            Animation(bonusSphereAnim, BonusSphereAnimType::DEFAULT),
            Transform2D(
                position + glm::vec2(-8, -12),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-1),
            InnerMovement(/*Duration:*/ 1, /*Speed:*/ 2),
            InnerMovementUp(),
            Lootable(),
            Velocity(),
            Trigger(-8 / 2, -8 / 2, 8, 8),
            ParticleGenerator(
                /*Prefab:*/ instantiateParticleEffectStar,
                /*Cooldown:*/ 0.5f,
                /*Radius:*/ 12.f
            )
        ),
        // Children
        {
            world.create_entity(
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