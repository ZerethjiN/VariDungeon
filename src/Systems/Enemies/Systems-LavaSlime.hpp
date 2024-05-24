#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lavaSlimeMoveSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsLavaSlimeMove, Orientation, const Speed, const LavaSlime, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isLavaSlimeMove, orientation, speed, lavaSlime, enemyTransform, zindex]: enemies) {
        if (isLavaSlimeMove.canSwitchState(time.fixedDelta())) {
            world.del<IsLavaSlimeMove>(enemyEnt);
            world.add(enemyEnt, IsLavaSlimePreAttack(lavaSlime.getPreAttackDuration()));

            world.appendChildren(enemyEnt, {
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 16), zindex),
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
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveRight");
                } else {
                    animation.play("MoveRight");
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveLeft");
                } else {
                    animation.play("MoveLeft");
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveDown");
                } else {
                    animation.play("MoveDown");
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveUp");
                } else {
                    animation.play("MoveUp");
                }
            }
        }
    }
}

void lavaSlimeAttackSys(World& world) {
    auto enemies = world.view<Animation, IsLavaSlimePreAttack, Orientation, const LavaSlime, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isLavaSlimePreAttack, orientation, lavaSlime, enemyTransform]: enemies) {
        if (isLavaSlimePreAttack.canSwitchState(time.fixedDelta())) {
            world.del<IsLavaSlimePreAttack>(enemyEnt);
            world.add(enemyEnt, IsLavaSlimeMove(lavaSlime.getMoveDuration()));

            world.appendChildren(enemyEnt, {
                instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition())
            });
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackRight");
                } else {
                    animation.play("PreAttackRight");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackLeft");
                } else {
                    animation.play("PreAttackLeft");
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackDown");
                } else {
                    animation.play("PreAttackDown");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackUp");
                } else {
                    animation.play("PreAttackUp");
                }
            }
        }
    }
}