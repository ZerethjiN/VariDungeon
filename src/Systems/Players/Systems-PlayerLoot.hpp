#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerLootSys(MainFixedSystem, World& world) {
    auto players = world.view<const OnCollisionStay>(with<PlayerAttractor>);

    for (auto [playerEnt, collisions]: players) {
        for (auto othEnt: collisions) {
            if (world.has<Lootable>(othEnt)) {
                world.remove<Lootable>(othEnt);
                world.add(othEnt,
                    LootAttract(128.f, playerEnt)
                );
                if (auto opt = world.get<Transform>(othEnt)) {
                    auto [othTransform] = opt.value();
                    othTransform.scale(0.1f, 0.1f);
                }
            }
        }
    }
}

void playerLootAttractSys(MainFixedSystem, World& world) {
    auto loots = world.view<Velocity, const Transform, const LootAttract>();

    auto [time] = world.resource<const Time>();

    for (auto [lootEnt, velocity, lootTransform, lootAttract]: loots) {
        Ent targetEnt = lootAttract.getTargetEnt();

        if (!world.exist(targetEnt)) {
            world.destroy(lootEnt);
            continue;
        }

        if (auto opt = world.get<const Transform>(targetEnt)) {
            auto [othTransform] = opt.value();

            velocity += glm::normalize(othTransform.getPosition() - lootTransform.getPosition()) * lootAttract.getSpeed() * time.fixedDelta();

            if (glm::distance(othTransform.getPosition(), lootTransform.getPosition()) < 8) {
                // Visual Effect:
                instantiateItemFeedbackParticle(world, lootTransform.getPosition());
                world.appendChildren(targetEnt, {
                    world.newEnt(
                        TextCreator("+" + std::to_string(int(1)), "Fonts/Zepto-Regular.ttf", 8, glm::vec2(32, 16), glm::vec4(36, 34, 30, 255), glm::vec2(0.5, 0.5), TextAlignementType::ALIGN_LEFT),
                        Transform(
                            othTransform.getPosition(),
                            0,
                            glm::vec2(0.5, 0.5)
                        ),
                        DamageText(
                            /*Direction:*/ -glm::normalize(glm::vec2(0, 16)),
                            /*Duration:*/ 0.2,
                            /*MaxScale:*/ 1.0,
                            /*Speed:*/ 128
                        ),
                        Velocity()
                    )
                });

                // If XP
                if (auto optXp = world.get<const XpGroundItem>(lootEnt)) {
                    auto [xpGroundItem] = optXp.value();

                    if (auto optPlayerXp = world.get<PlayerXp>(targetEnt)) {
                        auto [playerXp] = optPlayerXp.value();

                        playerXp.addXp(xpGroundItem.getAmount());
                        if (playerXp.isLevelUp()) {
                            world.appendChildren(targetEnt, {
                                world.newEnt(
                                    PlayerWeapon(),
                                    Damage(1),
                                    LevelUpKnockback(0.25f),
                                    SpriteCreator(levelUpShockwaveUV),
                                    Transform(
                                        othTransform.getPosition(),
                                        0,
                                        glm::vec2(1, 1)
                                    ),
                                    ZIndex(99),
                                    Velocity(),
                                    Trigger(-160 / 2, -144 / 2, 160, 144)
                                )
                            });
                        }

                        for (auto [_, xpTextUI]: world.view<TextUI>(with<PlayerXpText>)) {
                            xpTextUI.setString("XP " + std::to_string(static_cast<int>(playerXp.getCurXp())) + "/" + std::to_string(static_cast<int>(playerXp.getNbXpForNextLvl())));
                        }

                        auto xpRatio = playerXp.getCurXp() / playerXp.getNbXpForNextLvl();

                        for (auto [_, xpInnerBarUI, xpInnerBar]: world.view<UI, const PlayerXpBarInner>()) {
                            xpInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(xpRatio * xpInnerBar.getMaxLength()), 8));
                        }

                        for (auto [xpIconEnt, xpIconTransform]: world.view<Transform>(with<XpIconInventoryBar>, without<ShrinkIcon>)) {
                            if (!world.has<ShrinkIcon>(xpIconEnt)) {
                                xpIconTransform.scale(-0.2f, -0.2f);
                                world.add(xpIconEnt, ShrinkIcon(glm::vec2(-0.2f, -0.2f), 0.1f));
                            }
                        }
                    }
                }

                // If Life
                if (auto optLife = world.get<const LifeGroundItem>(lootEnt)) {
                    auto [lifeGroundItem] = optLife.value();

                    if (auto optPlayerLife = world.get<Life>(targetEnt)) {
                        auto [playerLife] = optPlayerLife.value();

                        playerLife += lifeGroundItem.getAmount();

                        for (auto [_, lifeTextUI]: world.view<TextUI>(with<PlayerLifeText>)) {
                            lifeTextUI.setString("HP " + std::to_string(static_cast<int>(playerLife.getNbLife())) + "/" + std::to_string(static_cast<int>(playerLife.getCurNbLife())));
                        }

                        auto lifeRatio = playerLife.getCurNbLife() / playerLife.getNbLife();

                        for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.view<UI, const PlayerLifeBarInner>()) {
                            lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
                        }
                    }
                }

                // If Coin
                if (auto optCoin = world.get<const CoinGroundItem>(lootEnt)) {
                    auto [coinGroundItem] = optCoin.value();

                    if (auto optPlayerCoin = world.get<PlayerCoin>(targetEnt)) {
                        auto [playerCoin] = optPlayerCoin.value();

                        playerCoin += coinGroundItem.getAmount();

                        for (auto [_, coinTextUI]: world.view<TextUI>(with<PlayerCoinText>)) {
                            coinTextUI.setString("" + std::to_string(static_cast<int>(playerCoin.getCurCoin())));
                        }

                        for (auto [coinIconEnt, coinIconTransform]: world.view<Transform>(with<CoinIconInventoryBar>, without<ShrinkIcon>)) {
                            if (!world.has<ShrinkIcon>(coinIconEnt)) {
                                coinIconTransform.scale(-0.2f, -0.2f);
                                world.add(coinIconEnt, ShrinkIcon(glm::vec2(-0.2f, -0.2f), 0.1f));
                            }
                        }
                    }
                }

                // Destroy:
                world.destroy(lootEnt);
            }
        }
    }
}