#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void anubisMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsAnubisMove, Orientation, const Speed, const Anubis, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isAnubisMove, orientation, speed, anubis, enemyTransform, zindex]: enemies) {
        if (isAnubisMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsAnubisMove>(enemyEnt);
            world.add_components(enemyEnt, IsAnubisAttack(anubis.attackDuration));

            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex)
                        });
                    }
                }
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(AnubisAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(AnubisAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(AnubisAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(AnubisAnimType::MOVE_UP);
                }
            }
        }
    }
}

void anubisAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsAnubisAttack, Orientation, const Anubis, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isAnubisAttack, orientation, anubis, enemyTransform]: enemies) {
        if (isAnubisAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsAnubisAttack>(enemyEnt);
            world.add_components(enemyEnt, IsAnubisMove(anubis.moveDuration));
            instantiateFireBallParticle(world, enemyTransform.getPosition(), orientation.orientation, 128.f);
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(AnubisAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(AnubisAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(AnubisAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(AnubisAnimType::ATTACK_UP);
                }
            }
        }
    }
}