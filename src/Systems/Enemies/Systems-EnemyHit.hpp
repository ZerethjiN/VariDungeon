#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyHitSys(World& world) {
    auto enemies = world.view<Transform, Life, const OnCollisionEnter, const ZIndex>(with<Enemy>, without<Unhittable, InvincibleFrame>);

    for (auto [enemyEnt, enemyTransform, life, collisions, zindex]: enemies) {
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
                    appliedCameraShake(world, 2.0f, 128.f, 2);

                    world.add(enemyEnt,
                        DeathParticleGenerator(true, 0.2, 2),
                        EnemyDropLoots(
                            {LootType::LOOT_TYPE_XP, LootType::LOOT_TYPE_XP, LootType::LOOT_TYPE_XP},
                            0.2,
                            2
                        )
                    );
                } else {
                    appliedCameraShake(world, 2.0f, 64.f, 2);
                }

                break;
            }
        }
    }
}