#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyHitSys(World& world) {
    auto enemies = world.view<Transform, Life, const OnCollisionEnter, const Transform, const ZIndex>(with<Enemy>, without<InvincibleFrame>);

    for (auto [enemyEnt, transform, life, collisions, enemyTransform, zindex]: enemies) {
        for (const auto& othEnt: collisions) {
            if (world.has<PlayerWeapon>(othEnt)) {
                // Damage:
                life -= 1;

                // Visual Effect:
                world.add(enemyEnt, InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f)));
                if (auto opt = world.get<const Transform>(othEnt)) {
                    auto [othTransform] = opt.value();

                    if (life.isDead()) {
                        world.add(enemyEnt,
                            Knockback(0.15f, -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()), 256.f),
                            CombatParticleGenerator(0.15f, 3, 2)
                        );
                    } else {
                        world.add(enemyEnt,
                            Knockback(0.15f, -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()), 128.f),
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
                transform.scale(-0.2f, -0.2f);

                // IsDead:
                if (life.isDead()) {
                    appliedCameraShake(world, 2.0f, 128.f, 2);

                    world.add(enemyEnt,
                        DeathParticleGenerator(0.2, 2),
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