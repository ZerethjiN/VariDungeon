#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateKey(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            Key(),
            Sprite(textureManager, keyUV),
            Animation(keyAnim, KeyAnimType::DEFAULT),
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
            Trigger(-8 / 2, (-8 / 2) + 16, 8, 8),
            ParticleGenerator(
                /*Prefab:*/ instantiateParticleEffectStar,
                /*Cooldown:*/ 0.5f,
                /*Radius:*/ 12.f
            ),
            LootCallback([](World& world, const Ent& this_entity, const Ent& target_entity) {
                if (world.has_components<Player>(target_entity)) {
                    for (auto [_, keyUI]: world.view<UI>(with<PlayerKeyIcon>)) {
                        keyUI.setTextureRect(HUDElementsUV[7]);
                    }

                    world.add_components(target_entity, IsPlayerKey());
                }
            })
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