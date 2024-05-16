#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyDropLootsSys(World& world) {
    auto loots = world.view<EnemyDropLoots, const Transform>();
    auto players = world.view(with<Player>);

    auto [time] = world.getRes<const Time>();

    for (auto [_, loot, transform]: loots) {
        if (loot.canSubDrop(time.fixedDelta())) {
            for (int i = loot.getCurNbDropPerSubDrop(); i < loot.getNextMaxRange(); i++) {
                float rndSpreadDirection = std::rand() % 360;
                switch (loot[i]) {
                    case LootType::LOOT_TYPE_XP:
                        instantiateXpParticle(
                            world,
                            transform.getPosition(),
                            0.25f,
                            glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                            32.f
                        );
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