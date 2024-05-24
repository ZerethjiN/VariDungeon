#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void enemyPreSpawnSys(World& world) {
    auto enemies = world.view<EnemyPreSpawn, const Transform, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, enemyPreSpawn, transform, zindex]: enemies) {
        if (enemyPreSpawn.canRemovePreSpawn(time.fixedDelta())) {
            world.del<EnemyPreSpawn>(enemyEnt);
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