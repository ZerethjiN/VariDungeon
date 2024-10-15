#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateHeartParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            LifeGroundItem(1.f),
            Sprite(textureManager, heartParticleUV),
            Animation(heartParticleAnim, HeartParticleAnimType::DEFAULT),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(25),
            Velocity(),
            Collider(-8 / 2, -8 / 2, 8, 8),
            LootSpread(spreadDuration, spreadDirection, spreadSpeed),
            LootCallback([](World& world, const Ent& this_entity, const Ent& target_entity) {
                if (world.has_components<Player>(target_entity)) {
                    if (auto optLife = world.get_components<const LifeGroundItem>(this_entity)) {
                        auto [lifeGroundItem] = optLife.value();

                        if (auto optPlayerLife = world.get_components<Life>(target_entity)) {
                            auto [playerLife] = optPlayerLife.value();

                            playerLife += lifeGroundItem.getAmount();

                            if (playerLife.getCurNbShield() <= 0) {
                                for (auto [_, lifeTextUI]: world.view<TextUI>(with<PlayerLifeText>)) {
                                    lifeTextUI.setString("HP " + std::to_string(static_cast<int>(playerLife.getCurNbLife())) + "/" + std::to_string(static_cast<int>(playerLife.getNbLife())));
                                }

                                auto lifeRatio = playerLife.getCurNbLife() / playerLife.getNbLife();

                                for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.view<UI, const PlayerLifeBarInner>()) {
                                    lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
                                }
                            }
                        }
                    }
                }
            })
        ),
        // Children
        {
            world.create_entity(
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