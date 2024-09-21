#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

// Run With: [insectMoveSys, insectAttackSys]
void insectMoveSys(MainFixedSystem, World& world) {
    auto insects = world.view<Velocity, Animation, IsInsectMove, Orientation, const Speed, const Insect, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [insectEnt, velocity, animation, isInsectMove, orientation, speed, insect, transform, zindex]: insects) {
        if (isInsectMove.canSwitchState(time.fixedDelta())) {
            world.remove<IsInsectMove>(insectEnt);
            world.add(insectEnt, IsInsectAttack(insect.getAttackDuration()));
            world.appendChildren(insectEnt, {
                instantiateExclamationParticle(world, transform.getPosition() + glm::vec2(0, -16), zindex)
            });
        }

        if (isInsectMove.canChangeDirection(time.fixedDelta())) {
            switch (rand() % 4) {
                case 0: orientation = Orientation::NORTH; break;
                case 1: orientation = Orientation::SOUTH; break;
                case 2: orientation = Orientation::EAST; break;
                case 3: orientation = Orientation::WEST; break;
            }
        }

        velocity += orientation.orientation * speed.speed * time.fixedDelta();
        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(InsectAnimType::MOVE_RIGHT);
                }
            } else {
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(InsectAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(InsectAnimType::MOVE_DOWN);
                }
            } else {
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(InsectAnimType::MOVE_UP);
                }
            }
        }
    }
}

// Run With: [insectMoveSys, insectAttackSys]
void insectAttackSys(MainFixedSystem, World& world) {
    auto insects = world.view<Velocity, Animation, IsInsectAttack, Orientation, const Speed, const Transform2D, const Insect>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [insectEnt, velocity, animation, isInsectAttack, orientation, speed, insectTransform, insect]: insects) {
        if (isInsectAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsInsectAttack>(insectEnt);
            world.add(insectEnt, IsInsectMove(insect.getMoveDuration(), insect.getDirectionCooldown()));
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - insectTransform.getPosition());
        }

        velocity += newdirection * speed.speed * insect.getAttackSpeedCoeff() * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(InsectAnimType::ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(InsectAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(InsectAnimType::ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(InsectAnimType::ATTACK_UP);
                }
            }
        }
    }
}