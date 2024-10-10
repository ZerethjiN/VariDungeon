#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

// Run With: [gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys]
void gasterolcanMoveSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGasterolcanMove, Orientation, const Speed, const Gasterolcan, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGasterolcanMove, orientation, speed, gasterolcan, enemyTransform, zindex]: enemies) {
        if (isGasterolcanMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGasterolcanMove>(enemyEnt);
            world.add_components(enemyEnt, IsGasterolcanPreAttack(gasterolcan.preAttackDuration));
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(GasterolcanAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(GasterolcanAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(GasterolcanAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(GasterolcanAnimType::MOVE_UP);
                }
            }
        }
    }
}

// Run With: [gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys]
void gasterolcanPreAttackSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsGasterolcanPreAttack, Orientation, const Gasterolcan, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isGasterolcanPreAttack, orientation, gasterolcan, enemyTransform]: enemies) {
        if (isGasterolcanPreAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGasterolcanPreAttack>(enemyEnt);
            world.add_components(enemyEnt, IsGasterolcanAttack(gasterolcan.attackDuration));
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(GasterolcanAnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(GasterolcanAnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(GasterolcanAnimType::PRE_ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(GasterolcanAnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}

// Run With: [gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys]
void gasterolcanAttackSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGasterolcanAttack, Orientation, const Speed, const Gasterolcan, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGasterolcanAttack, orientation, speed, gasterolcan, enemyTransform]: enemies) {
        if (isGasterolcanAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGasterolcanAttack>(enemyEnt);
            world.add_components(enemyEnt, IsGasterolcanMove(gasterolcan.moveDuration));
            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * gasterolcan.rollSpeedCoeff * time.fixedDelta();
        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(GasterolcanAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(GasterolcanAnimType::ATTACK_RIGHT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(GasterolcanAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(GasterolcanAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(GasterolcanAnimType::ATTACK_UP);
                }
            }
        }
    }
}