#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerLootSys(MainFixedSystem, World& world) {
    auto players = world.view<const OnCollisionStay>(with<PlayerAttractor>);

    for (auto [_, collisions]: players) {
        for (auto othEnt: collisions) {
            if (world.has_components<Lootable>(othEnt)) {
                world.remove_components<Lootable>(othEnt);
                for (auto [player_ent]: world.view(with<Player>)) {
                    world.add_components(othEnt,
                        LootAttract(128.f, player_ent)
                    );
                }
                if (auto opt = world.get_components<Transform2D>(othEnt)) {
                    auto [othTransform] = opt.value();
                    othTransform.scale(0.1f, 0.1f);
                }
            }
        }
    }
}

void playerLootAttractSys(MainFixedSystem, World& world) {
    auto loots = world.view<Velocity, const Transform2D, const LootAttract>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [lootEnt, velocity, lootTransform, lootAttract]: loots) {
        Ent targetEnt = lootAttract.getTargetEnt();

        if (!world.entity_exists(targetEnt)) {
            world.delete_entity(lootEnt);
            continue;
        }

        if (auto opt = world.get_components<const Transform2D>(targetEnt)) {
            auto [othTransform] = opt.value();

            auto distancePlayerItem = std::min(glm::distance(lootTransform.getPosition(), othTransform.getPosition()), 24.f) * 0.0375f;

            velocity += glm::normalize(othTransform.getPosition() - lootTransform.getPosition()) * (lootAttract.getSpeed() / distancePlayerItem) * time.fixedDelta();

            if (glm::distance(othTransform.getPosition(), lootTransform.getPosition()) < 8) {
                // Visual Effect:
                instantiateItemFeedbackParticle(world, lootTransform.getPosition());
                world.append_children(targetEnt, {
                    world.create_entity(
                        TextCreator("+" + std::to_string(int(1)), "Fonts/Zepto-Regular.ttf", 8, glm::vec2(32, 16), glm::vec4(85, 80, 67, 255), glm::vec2(0.5, 0.5), TextAlignementType::ALIGN_LEFT),
                        Transform2D(
                            othTransform.getPosition() - glm::vec2(8, 0),
                            0,
                            glm::vec2(0.5, 0.5)
                        ),
                        DamageText(
                            /*Direction:*/ -glm::normalize(glm::vec2(0, 16)),
                            /*Duration:*/ 0.5,
                            /*MaxScale:*/ 1.5,
                            /*Speed:*/ 64
                        ),
                        Velocity()
                    )
                });

                if (auto opt_loot_callback = world.get_components<LootCallback>(lootEnt)) {
                    auto [loot_callback] = opt_loot_callback.value();

                    loot_callback.callback(world, lootEnt, targetEnt);
                }

                // Destroy:
                world.delete_entity(lootEnt);
            }
        }
    }
}