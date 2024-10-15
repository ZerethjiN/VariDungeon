#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateCoinParticle(World& world, const glm::vec2& position, float spreadDuration, const glm::vec2& spreadDirection, float spreadSpeed) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            CoinGroundItem(1.f),
            Sprite(textureManager, coinParticleUV),
            Animation(coinParticleAnim, CoinParticleAnimType::DEFAULT),
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
                    if (auto optCoin = world.get_components<const CoinGroundItem>(this_entity)) {
                        auto [coinGroundItem] = optCoin.value();

                        if (auto optPlayerCoin = world.get_components<PlayerCoin>(target_entity)) {
                            auto [playerCoin] = optPlayerCoin.value();

                            playerCoin += coinGroundItem.getAmount();

                            for (auto [_, coinTextUI]: world.view<TextUI>(with<PlayerCoinText>)) {
                                coinTextUI.setString("" + std::to_string(static_cast<int>(playerCoin.getCurCoin())));
                            }

                            for (auto [coinIconEnt, coinIconTransform]: world.view<Transform2D>(with<CoinIconInventoryBar>, without<ShrinkIcon>)) {
                                if (!world.has_components<ShrinkIcon>(coinIconEnt)) {
                                    coinIconTransform.scale(-0.2f, -0.2f);
                                    world.add_components(coinIconEnt, ShrinkIcon(glm::vec2(-0.2f, -0.2f), 0.1f));
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