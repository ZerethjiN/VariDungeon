#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerLootSys(World& world) {
    auto players = world.view<const OnCollisionStay>(with<PlayerAttractor>);

    for (auto [playerEnt, collisions]: players) {
        for (auto othEnt: collisions) {
            if (world.has<Lootable>(othEnt)) {
                world.del<Lootable>(othEnt);
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

void playerLootAttractSys(World& world) {
    auto loots = world.view<Velocity, const Transform, const LootAttract>();

    auto [time] = world.getRes<const Time>();

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

                // Destroy:
                world.destroy(lootEnt);
            }
        }
    }
}