#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void barbarianStartDashSys(World& world) {
    auto players = world.view<const Transform, const Orientation>(with<Player, Barbarian>, without<IsBarbarianDash>);

    for (auto [playerEnt, transform, orientation]: players) {
        if (vulkanEngine.window.isKeyDown(B_BUTTON)) {
            glm::vec2 newDirection(0, 0);

            if (orientation.x > 0) {
                newDirection = glm::vec2(1, 0);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.25f),
                        Trigger(-32 / 2, -16 / 2, 32, 16)
                    )
                });
            } else if (orientation.x < 0) {
                newDirection = glm::vec2(-1, 0);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(-8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.25f),
                        Trigger(-32 / 2, -16 / 2, 32, 16)
                    )
                });
            } else if (orientation.y > 0) {
                newDirection = glm::vec2(0, 1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(0, 8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.25f),
                        Trigger(-16 / 2, -32 / 2, 16, 32)
                    )
                });
            } else if (orientation.y < 0) {
                newDirection = glm::vec2(0, -1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(0, -8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.25f),
                        Trigger(-16 / 2, -32 / 2, 16, 32)
                    )
                });
            }

            world.add(playerEnt, IsBarbarianDash(0.25f, newDirection, 2.f));
        }
    }
}

void barbarianStopDashSys(World& world) {
    auto players = world.view<IsBarbarianDash>(with<Player, Barbarian>);

    auto [time] = world.getRes<const Time>();

    for (auto [playerEnt, isBarbarianDash]: players) {
        if (isBarbarianDash.canStopDash(time.fixedDelta()) || vulkanEngine.window.isKeyUp(B_BUTTON)) {
            world.del<IsBarbarianDash>(playerEnt);
        }
    }
}

void barbarianMovementSys(World& world) {
    auto players = world.view<Velocity, Animation, Orientation, const Speed>(with<Player, Barbarian>);

    auto [time] = world.getRes<const Time>();

    for (auto [playerEnt, velocity, animation, orientation, speed]: players) {
        glm::vec2 newVelocity(0, 0);

        if (vulkanEngine.window.isKeyHold(MOVE_DOWN)) {
            newVelocity.y = speed * time.fixedDelta();
        } else if (vulkanEngine.window.isKeyHold(MOVE_UP)) {
            newVelocity.y = -speed * time.fixedDelta();
        }

        if (vulkanEngine.window.isKeyHold(MOVE_LEFT)) {
            newVelocity.x = -speed * time.fixedDelta();
        } else if (vulkanEngine.window.isKeyHold(MOVE_RIGHT)) {
            newVelocity.x = speed * time.fixedDelta();
        }

        if (auto opt = world.get<IsBarbarianDash>(playerEnt)) {
            auto [isBarbarianDash] = opt.value();
            newVelocity = isBarbarianDash.getDirection() * isBarbarianDash.getSpeedCoeff() * speed.speed * time.fixedDelta();
        }

        velocity = newVelocity;

        if (newVelocity.x > 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    animation.play("DashRight");
                } else {
                    animation.play("MoveRight");
                }
            }
            orientation = Orientation::EAST;
        } else if (newVelocity.x < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    animation.play("DashLeft");
                } else {
                    animation.play("MoveLeft");
                }
            }
            orientation = Orientation::WEST;
        } else if (newVelocity.y > 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    animation.play("DashDown");
                } else {
                    animation.play("MoveDown");
                }
            }
            orientation = Orientation::SOUTH;
        } else if (newVelocity.y < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    animation.play("DashUp");
                } else {
                    animation.play("MoveUp");
                }
            }
            orientation = Orientation::NORTH;
        } else {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (orientation.x > 0) {
                    animation.play("IdleRight");
                } else if (orientation.x < 0) {
                    animation.play("IdleLeft");
                } else if (orientation.y > 0) {
                    animation.play("IdleDown");
                } else if (orientation.y < 0) {
                    animation.play("IdleUp");
                }
            }
        }
    }
}

void barbarianStartAttackSys(World& world) {
    auto players = world.view<Animation, const Orientation, const Transform>(with<Player, Barbarian>, without<IsBarbarianAttack>);

    for (auto [playerEnt, animation, orientation, transform]: players) {
        if (vulkanEngine.window.isKeyDown(A_BUTTON)) {
            if (orientation.x > 0) {
                animation.play("AttackRight");
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -32 / 2, 32, 32)
                    )
                });
            } else if (orientation.x < 0) {
                animation.play("AttackLeft");
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(-8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -32 / 2, 32, 32)
                    )
                });
            } else if (orientation.y > 0) {
                animation.play("AttackDown");
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(0, 8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -32 / 2, 32, 32)
                    )
                });
            } else if (orientation.y < 0) {
                animation.play("AttackUp");
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Transform(
                            transform.getPosition() + glm::vec2(0, -8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -32 / 2, 32, 32)
                    )
                });
            }
            world.add(playerEnt, IsBarbarianAttack(0.2f));
        }
    }
}

void barbarianStopAttackSys(World& world) {
    auto players = world.view<IsBarbarianAttack>(with<Player, Barbarian>);

    auto [time] = world.getRes<const Time>();

    for (auto [playerEnt, isBarbarianAttack]: players) {
        if (isBarbarianAttack.canStopAttack(time.fixedDelta())) {
            world.del<IsBarbarianAttack>(playerEnt);
        }
    }
}