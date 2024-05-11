#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyHitSys(World& world) {
    auto enemies = world.view<Transform, const OnCollisionEnter, const Transform>(with<Enemy>, without<InvincibleFrame>);

    for (auto [enemyEnt, transform, collisions, enemyTransform]: enemies) {
        for (const auto& othEnt: collisions) {
            if (world.has<PlayerWeapon>(othEnt)) {
                world.add(enemyEnt, InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f)));
                if (auto opt = world.get<Transform>(othEnt)) {
                    auto [othTransform] = opt.value();
                    world.add(enemyEnt,
                        Knockback(0.15f, -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()), 128.f)
                    );
                    instantiateSwordImpact(world, othTransform.getPosition());

                    world.appendChildren(enemyEnt, {
                        world.newEnt(
                            TextCreator(std::to_string(int(1)), "Fonts/Zepto-Regular.ttf", 8, glm::vec2(32, 16), glm::vec4(242, 214, 136, 255), glm::vec2(0.5, 0.5), TextAlignementType::ALIGN_LEFT),
                            Transform(
                                enemyTransform.getPosition(),
                                0,
                                glm::vec2(0.5, 0.5)
                            ),
                            DamageText(
                                /*Direction:*/ -glm::normalize(othTransform.getPosition() - enemyTransform.getPosition()),
                                /*Duration:*/ 0.15,
                                /*MaxScale:*/ 1.5,
                                /*Speed:*/ 128
                            ),
                            Velocity()
                        )
                    });
                }
                transform.scale(-0.2f, -0.2f);
            }
        }
    }
}