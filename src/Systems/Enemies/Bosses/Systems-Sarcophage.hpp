#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void sarcophageShadowMarkSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophageShadowMark, Orientation, const Sarcophage, const Speed, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophageShadowMark, orientation, sarcophage, speed, enemyTransform, zindex]: enemies) {
        if (isSarcophageShadowMark.canSpawnShadowMark(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                instantiateShadowMarkParticle(world, playerTransform.getPosition());
            }
        }

        if (isSarcophageShadowMark.canSwitchState(time.fixedDelta())) {
            world.remove<IsSarcophageShadowMark>(enemyEnt);
            world.add(enemyEnt, IsSarcophagePreLaserAttack(sarcophage.preLaserDuration));

            for (int i = 1; i < 7; i++) {
                world.appendChildren(enemyEnt, {
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex)
                });
            }
            
            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                animation.play("MoveRight");
            } else {
                orientation = Orientation::WEST;
                animation.play("MoveLeft");
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play("MoveDown");
            } else {
                orientation = Orientation::NORTH;
                animation.play("MoveUp");
            }
        }
    }
}

void sarcophagePreLaserSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophagePreLaserAttack, Orientation, const Sarcophage, const Speed, const Transform>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophagePreLaserAttack, orientation, sarcophage, speed, enemyTransform]: enemies) {
        if (isSarcophagePreLaserAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsSarcophagePreLaserAttack>(enemyEnt);
            world.add(enemyEnt, IsSarcophageLaserAttack(sarcophage.laserDuration));

            world.appendChildren(enemyEnt, {
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),   0, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),  90, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 180, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 270, sarcophage.laserDuration, 32.f),
            });
    
            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                animation.play("MoveRight");
            } else {
                orientation = Orientation::WEST;
                animation.play("MoveLeft");
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play("MoveDown");
            } else {
                orientation = Orientation::NORTH;
                animation.play("MoveUp");
            }
        }
    }
}

void sarcophageLaserSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophageLaserAttack, Orientation, const Sarcophage, const Speed, const Transform>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophageLaserAttack, orientation, sarcophage, speed, enemyTransform]: enemies) {
        if (isSarcophageLaserAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsSarcophageLaserAttack>(enemyEnt);
            world.add(enemyEnt, IsSarcophageShadowMark(sarcophage.shadowMarkDuration, sarcophage.nbShadowMark));
            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                animation.play("MoveRight");
            } else {
                orientation = Orientation::WEST;
                animation.play("MoveLeft");
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play("MoveDown");
            } else {
                orientation = Orientation::NORTH;
                animation.play("MoveUp");
            }
        }
    }
}