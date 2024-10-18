#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void batLvl2MoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsBatLvl2Move, Orientation, const Speed, const BatLvl2, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isBatMove, orientation, speed, bat, enemyTransform, zindex]: enemies) {
        if (isBatMove.canSwitchState(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= bat.attackRadius) {
                    world.remove_components<IsBatLvl2Move>(enemyEnt);
                    world.add_components(enemyEnt, IsBatLvl2Attack(bat.attackDuration));

                    world.append_children(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, -16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, -16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16), zindex)
                    });
                    continue;
                }
            }
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
                    animation.play(BatLvl2AnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(BatLvl2AnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(BatLvl2AnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(BatLvl2AnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_MOVE_UP);
                } else {
                    animation.play(BatLvl2AnimType::MOVE_UP);
                }
            }
        }
    }
}

void batLvl2AttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsBatLvl2Attack, Orientation, const BatLvl2, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isBatAttack, orientation, bat, enemyTransform]: enemies) {
        if (isBatAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsBatLvl2Attack>(enemyEnt);
            world.add_components(enemyEnt, IsBatLvl2Move(bat.moveDuration));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 90),
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 270)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 90),
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 270)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 180),
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 0)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 180),
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 0)
                    });
                }
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(BatLvl2AnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(BatLvl2AnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(BatLvl2AnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatLvl2AnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(BatLvl2AnimType::ATTACK_UP);
                }
            }
        }
    }
}