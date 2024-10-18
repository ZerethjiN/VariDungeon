#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyDropLootsSys(MainFixedSystem, World& world) {
    auto loots = world.query<EnemyDropLoots, const Transform2D>();
    auto players = world.query(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [_, loot, transform]: loots) {
        if (loot.canSubDrop(time.fixedDelta())) {
            for (std::size_t i = loot.getCurNbDropPerSubDrop(); i < loot.getNextMaxRange(); i++) {
                float rndSpreadDirection = std::rand() % 360;
                switch (loot[i]) {
                    case LootType::XP:
                        instantiateXpParticle(
                            world,
                            transform.getPosition(),
                            0.25f,
                            glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                            32.f
                        );
                        break;
                    case LootType::HEART:
                        instantiateHeartParticle(
                            world,
                            transform.getPosition(),
                            0.25f,
                            glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                            32.f
                        );
                        break;
                    case LootType::SHIELD:
                        instantiateShieldParticle(
                            world,
                            transform.getPosition(),
                            0.25f,
                            glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                            32.f
                        );
                        break;
                    case LootType::KING:
                        instantiateKingGroundItem(world, transform.getPosition());
                        break;
                    default:
                        instantiateCoinParticle(
                            world,
                            transform.getPosition(),
                            0.25f,
                            glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                            32.f
                        );
                        break;
                }
            }
            loot.nextSubLoot();
        }
    }
}