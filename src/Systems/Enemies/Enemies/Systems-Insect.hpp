#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

// Run With: [insectMoveSys, insectAttackSys]
void insectMoveSys(MainFixedSystem, World& world) {
    auto insects = world.view<Velocity, Animation, IsInsectMove, Orientation, const Speed, const Insect, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [insectEnt, velocity, animation, isInsectMove, orientation, speed, insect, transform, zindex]: insects) {
        if (isInsectMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsInsectMove, IsInsectChangeDirection>(insectEnt);
            world.add_components(insectEnt, IsInsectAttack(insect.attackDuration));
            world.append_children(insectEnt, {
                instantiateExclamationParticle(world, transform.getPosition() + glm::vec2(0, -16), zindex),
                world.create_entity(
                    Sprite(textureManager, shadowUV),
                    Animation(shadowAnim, ShadowAnimType::SMALL),
                    Transform2D(
                        transform.getPosition() + glm::vec2(0, 2),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(-2),
                    LifeTime(insect.attackDuration)
                )
            });
        }

        velocity += orientation.orientation * speed.speed * time.fixedDelta();
        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(InsectAnimType::MOVE_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(InsectAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(InsectAnimType::MOVE_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(InsectAnimType::MOVE_UP);
                }
            }
        }
    }
}

void insectChangeDirectionSys(MainFixedSystem, World& world) {
    auto insects = world.view<IsInsectChangeDirection, Orientation>(with<Insect>, without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [_, isInsectChangeDirection, orientation]: insects) {
        if (isInsectChangeDirection.canTick(time.fixedDelta())) {
            switch (rand() % 4) {
                case 0: orientation = Orientation::NORTH; break;
                case 1: orientation = Orientation::SOUTH; break;
                case 2: orientation = Orientation::EAST; break;
                case 3: orientation = Orientation::WEST; break;
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
            world.remove_components<IsInsectAttack>(insectEnt);
            world.add_components(insectEnt,
                IsInsectMove(insect.moveDuration),
                IsInsectChangeDirection(insect.directionCooldown)
            );
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - insectTransform.getPosition());
        }

        velocity += newdirection * speed.speed * insect.attackSpeedCoeff * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(InsectAnimType::ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(InsectAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(InsectAnimType::ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(insectEnt)) {
                    animation.play(InsectAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(InsectAnimType::ATTACK_UP);
                }
            }
        }
    }
}