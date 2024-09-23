#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyPreSpawnSys(MainFixedSystem, World& world) {
    auto enemies = world.view<EnemyPreSpawn, const Transform2D, const ZIndex>();

    auto [time] = world.resource<const Time>();

    bool noHealthBar = true;

    for (auto [enemyEnt, enemyPreSpawn, transform, zindex]: enemies) {
        if (enemyPreSpawn.canRemovePreSpawn(time.fixedDelta())) {
            world.remove_component<EnemyPreSpawn>(enemyEnt);
            if (noHealthBar && world.has<Boss>(enemyEnt) && world.view(with<BossHealthBar>).empty()) {
                instantiateBossHealthBarUI(world, glm::vec2(0, 0));
                noHealthBar = false;
            }
        }

        if (enemyPreSpawn.canSpawnParticle(time.fixedDelta())) {
            if (enemyPreSpawn.getCurNbParticle() % 2 == 0) {
                world.appendChildren(enemyEnt, {
                    instantiateDustParticle(world, transform.getPosition() + glm::vec2(8, 8), zindex)
                });
            } else {
                world.appendChildren(enemyEnt, {
                    instantiateDustParticle(world, transform.getPosition() + glm::vec2(-8, -8), zindex)
                });
            }
        }
    }
}