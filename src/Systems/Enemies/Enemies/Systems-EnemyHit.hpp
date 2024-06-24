#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyHitSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Transform, Life, const OnCollisionEnter, const ZIndex, const Loots>(with<Enemy>, without<Unhittable, InvincibleFrame>);

    for (auto [enemyEnt, enemyTransform, life, collisions, zindex, loots]: enemies) {
        for (auto othEnt: collisions) {
            if (world.has<PlayerWeapon, Damage>(othEnt)) {
                // Damage:
                if (auto opt = world.get<const Damage>(othEnt)) {
                    auto [damage] = opt.value();

                    life -= damage;
                }

                // Visual Effect:
                world.add(enemyEnt, InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f)));
                if (auto opt = world.get<const Transform>(othEnt)) {
                    auto [othTransform] = opt.value();

                    if (world.has<Velocity>(enemyEnt)) {
                        float knockbackStrength = 128.f;
                        for (auto [_, playerKnockbackStrength]: world.view<const PlayerKnockbackStrength>()) {
                            knockbackStrength = playerKnockbackStrength.getKnockbackStrength();
                        }

                        if (life.isDead()) {
                            world.add(enemyEnt,
                                Knockback(0.15f, -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()), knockbackStrength * 2),
                                CombatParticleGenerator(0.15f, 3, 2)
                            );
                        } else {
                            world.add(enemyEnt,
                                Knockback(0.15f, -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()), knockbackStrength),
                                CombatParticleGenerator(0.15f, 2, 2)
                            );
                        }
                    }
                    instantiateSwordImpact(world, othTransform.getPosition(), zindex);

                    world.appendChildren(enemyEnt, {
                        world.newEnt(
                            TextCreator(std::to_string(int(1)), "Fonts/Zepto-Regular.ttf", 8, glm::vec2(32, 16), glm::vec4(36, 34, 30, 255), glm::vec2(0.5, 0.5), TextAlignementType::ALIGN_LEFT),
                            Transform(
                                enemyTransform.getPosition(),
                                0,
                                glm::vec2(0.5, 0.5)
                            ),
                            DamageText(
                                /*Direction:*/ -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()),
                                /*Duration:*/ 0.3,
                                /*MaxScale:*/ 1.5,
                                /*Speed:*/ 64
                            ),
                            Velocity()
                        )
                    });
                }
                enemyTransform.scale(-0.2f, -0.2f);

                // IsDead:
                if (life.isDead()) {
                    appliedCurCameraAberation(world, 4, 0.1);

                    std::vector<std::size_t> newLoots;

                    if (!loots.empty()) {
                        auto rndLootType = rand() % loots.size();
                        const auto& loot = loots[rndLootType];
                        auto newNbLoots = (rand() % loot.minLootDrop) + (loot.maxLootDrop - loot.minLootDrop) + 1;
                        for (std::size_t i = 0; i < newNbLoots; i++) {
                            newLoots.emplace_back(loot.lootType);
                        }
                    }

                    for (auto [playerEnt, playerAttackSpeed, playerSpeed]: world.view<PlayerAttackCooldown, Speed>(with<Player>)) {
                        if (auto opt = world.get<PlayerFrenzy>(playerEnt)) {
                            auto [playerFrenzy] = opt.value();
                            playerFrenzy.reset();
                        } else {
                            playerAttackSpeed *= 1.25f;
                            playerSpeed.speed *= 1.5f;
                            world.add(playerEnt, PlayerFrenzy(0.5f, 1.25f, 1.5f));
                        }
                    }

                    if (world.has<Boss>(enemyEnt)) {
                        for (auto [bossHealthBarEnt]: world.view(with<BossHealthBar>)) {
                            world.destroy(bossHealthBarEnt);
                        }
                        for (auto [_, roomTransform]: world.view<const Transform>(with<ChunkInfos>)) {
                            instantiateWarp(world, roomTransform.getPosition() + glm::vec2(-8, -8));
                        }
                        world.add(enemyEnt,
                            DeathParticleGenerator(true, 0.4, 4),
                            EnemyDropLoots(newLoots, 0.4, 1)
                        );
                        appliedCameraShake(world, 0.5f, 128.f, 4);
                    } else {
                        world.add(enemyEnt,
                            DeathParticleGenerator(true, 0.2, 2),
                            EnemyDropLoots(newLoots, 0.2, 1)
                        );
                        appliedCameraShake(world, 0.5f, 128.f, 2);
                    }
                } else {
                    appliedCameraShake(world, 0.5f, 128.f, 2);

                    if (world.has<Boss>(enemyEnt)) {
                        for (auto [_, lifeTextUI]: world.view<TextUI>(with<BossHealthBarText>)) {
                            lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getCurNbLife())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
                        }

                        auto lifeRatio = life.getCurNbLife() / life.getNbLife();

                        for (auto [_, ui, bossHealthBarInner]: world.view<UI, const BossHealthBarInner>()) {
                            ui.setTextureRect(glm::vec4(0, 36, static_cast<unsigned int>(lifeRatio * bossHealthBarInner.getMaxPixelSize()), 8));
                        }
                    }
                }

                break;
            }
        }
    }
}