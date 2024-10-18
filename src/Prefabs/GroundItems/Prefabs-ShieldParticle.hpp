#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShieldParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            ShieldGroundItem(1.f),
            Sprite(textureManager, shieldParticleUV),
            Animation(shieldParticleAnim, ShieldParticleAnimType::DEFAULT),
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
                    if (auto optShield = world.get_components<const ShieldGroundItem>(this_entity)) {
                        auto [shieldGroundItem] = optShield.value();

                        if (auto optPlayerLife = world.get_components<Life>(target_entity)) {
                            auto [playerLife] = optPlayerLife.value();

                            playerLife.addShield(shieldGroundItem.getAmount());

                            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                                lifeIcon.setTextureRect(HUDElementsUV[3]);
                            }

                            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                                lifeTextUI.setString("Shield " + std::to_string(static_cast<int>(playerLife.getCurNbShield())) + "/" + std::to_string(static_cast<int>(playerLife.getNbLife())));
                            }

                            auto lifeRatio = playerLife.getCurNbShield() / playerLife.getNbLife();

                            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
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