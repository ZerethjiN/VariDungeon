#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateXpParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            XpGroundItem(1.f),
            Sprite(textureManager, xpParticleUV),
            Animation(xpParticleAnim, XpParticleAnimType::DEFAULT),
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
                    if (auto optXp = world.get_components<const XpGroundItem>(this_entity)) {
                        auto [xpGroundItem] = optXp.value();

                        if (auto optPlayerXp = world.get_components<PlayerXp, const Transform2D>(target_entity)) {
                            auto [playerXp, player_transform] = optPlayerXp.value();

                            auto [textureManager] = world.resource<TextureManager>();

                            playerXp.addXp(xpGroundItem.getAmount());
                            if (playerXp.isLevelUp()) {
                                world.append_children(target_entity, {
                                    world.create_entity(
                                        PlayerWeapon(),
                                        Damage(1),
                                        LevelUpKnockback(0.25f),
                                        Sprite(textureManager, levelUpShockwaveUV),
                                        Transform2D(
                                            player_transform.getPosition(),
                                            0,
                                            glm::vec2(1, 1)
                                        ),
                                        ZIndex(99),
                                        Velocity(),
                                        Trigger(-160 / 2, -144 / 2, 160, 144)
                                    )
                                });
                                appliedCurCameraAberation(world, 8, 0.2);
                            }

                            for (auto [_, xpTextUI]: world.view<TextUI>(with<PlayerXpText>)) {
                                xpTextUI.setString("XP " + std::to_string(static_cast<int>(playerXp.getCurXp())) + "/" + std::to_string(static_cast<int>(playerXp.getNbXpForNextLvl())));
                            }

                            auto xpRatio = playerXp.getCurXp() / playerXp.getNbXpForNextLvl();

                            for (auto [_, xpInnerBarUI, xpInnerBar]: world.view<UI, const PlayerXpBarInner>()) {
                                xpInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(xpRatio * xpInnerBar.getMaxLength()), 8));
                            }

                            for (auto [xpIconEnt, xpIconTransform]: world.view<Transform2D>(with<XpIconInventoryBar>, without<ShrinkIcon>)) {
                                if (!world.has_components<ShrinkIcon>(xpIconEnt)) {
                                    xpIconTransform.scale(-0.2f, -0.2f);
                                    world.add_components(xpIconEnt, ShrinkIcon(glm::vec2(-0.2f, -0.2f), 0.1f));
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