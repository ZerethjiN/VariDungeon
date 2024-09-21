#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void barbarianStartDashSys(MainFixedSystem, World& world) {
    auto players = world.view<const Transform2D, const Orientation, const PlayerDamage, const ZIndex>(with<Player, Barbarian>, without<IsBarbarianDash>);

    for (auto [playerEnt, transform, orientation, playerDamage, zindex]: players) {
        if (vulkanEngine.window.isKeyDown(ButtonNameType::B_BUTTON)) {
            for (auto [buttonBIconEnt, buttonBIconTransform]: world.view<Transform2D>(with<ButtonBIconInventoryBar>, without<ShrinkIcon>)) {
                if (!world.has<ShrinkIcon>(buttonBIconEnt)) {
                    buttonBIconTransform.scale(-0.1f, -0.1f);
                    world.add(buttonBIconEnt, ShrinkIcon(glm::vec2(-0.1f, -0.1f), 0.2f));
                }
            }

            glm::vec2 newDirection(0, 0);

            if (orientation.x > 0) {
                newDirection = glm::vec2(1, 0);
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_RIGHT, zindex.layer - 1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
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
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_LEFT, zindex.layer - 1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
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
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_DOWN, zindex.layer - 1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
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
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_UP, zindex.layer - 1);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
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

            world.add(playerEnt, IsBarbarianDash(0.25f, newDirection, 2.f, 0.1f));
            // appliedCurCameraAberation(world, 8, 10, newDirection);

            if (!world.has<Unhittable>(playerEnt)) {
                world.add(playerEnt, Unhittable());
            }
        }
    }
}

void barbarianStopDashSys(MainFixedSystem, World& world) {
    auto players = world.view<IsBarbarianDash, const Orientation, const Transform2D, const ZIndex>(with<Player, Barbarian>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, isBarbarianDash, orientation, transform, zindex]: players) {
        if (isBarbarianDash.canStopDash(time.fixedDelta()) || vulkanEngine.window.isKeyUp(ButtonNameType::B_BUTTON)) {
            world.remove<IsBarbarianDash>(playerEnt);
            if (world.has<Unhittable>(playerEnt)) {
                world.remove<Unhittable>(playerEnt);
            }
            continue;
        }

        if (isBarbarianDash.canSpawnPersistentImage(time.fixedDelta())) {
            if (orientation.x > 0) {
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_RIGHT, zindex.layer - 1);
            } else if (orientation.x < 0) {
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_LEFT, zindex.layer - 1);
            } else if (orientation.y > 0) {
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_DOWN, zindex.layer - 1);
            } else if (orientation.y < 0) {
                instantiateBarbarianPersistence(world, transform.getPosition(), BarbareAnimType::PERSISTENCE_UP, zindex.layer - 1);
            }
        }
    }
}

void barbarianMovementSys(MainFixedSystem, World& world) {
    auto players = world.view<Velocity, Animation, Orientation, const Speed>(with<Player, Barbarian>, without<Unmoveable>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, velocity, animation, orientation, speed]: players) {
        glm::vec2 newVelocity(0, 0);

        if (vulkanEngine.window.isKeyHold(ButtonNameType::MOVE_DOWN)) {
            newVelocity.y = speed * time.fixedDelta();
        } else if (vulkanEngine.window.isKeyHold(ButtonNameType::MOVE_UP)) {
            newVelocity.y = -speed * time.fixedDelta();
        }

        if (vulkanEngine.window.isKeyHold(ButtonNameType::MOVE_LEFT)) {
            newVelocity.x = -speed * time.fixedDelta();
        } else if (vulkanEngine.window.isKeyHold(ButtonNameType::MOVE_RIGHT)) {
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
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_DASH_RIGHT);
                    } else {
                        animation.play(BarbareAnimType::DASH_RIGHT);
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_MOVE_RIGHT);
                    } else {
                        animation.play(BarbareAnimType::MOVE_RIGHT);
                    }
                }
            }
            orientation = Orientation::EAST;
        } else if (newVelocity.x < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_DASH_LEFT);
                    } else {
                        animation.play(BarbareAnimType::DASH_LEFT);
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_MOVE_LEFT);
                    } else {
                        animation.play(BarbareAnimType::MOVE_LEFT);
                    }
                }
            }
            orientation = Orientation::WEST;
        } else if (newVelocity.y > 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_DASH_DOWN);
                    } else {
                        animation.play(BarbareAnimType::DASH_DOWN);
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_MOVE_DOWN);
                    } else {
                        animation.play(BarbareAnimType::MOVE_DOWN);
                    }
                }
            }
            orientation = Orientation::SOUTH;
        } else if (newVelocity.y < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_DASH_UP);
                    } else {
                        animation.play(BarbareAnimType::DASH_UP);
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play(BarbareAnimType::HIT_MOVE_UP);
                    } else {
                        animation.play(BarbareAnimType::MOVE_UP);
                    }
                }
            }
            orientation = Orientation::NORTH;
        } else {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    if (orientation.x > 0) {
                        animation.play(BarbareAnimType::HIT_IDLE_RIGHT);
                    } else if (orientation.x < 0) {
                        animation.play(BarbareAnimType::HIT_IDLE_LEFT);
                    } else if (orientation.y > 0) {
                        animation.play(BarbareAnimType::HIT_IDLE_DOWN);
                    } else if (orientation.y < 0) {
                        animation.play(BarbareAnimType::HIT_IDLE_UP);
                    }
                } else {
                    if (orientation.x > 0) {
                        animation.play(BarbareAnimType::IDLE_RIGHT);
                    } else if (orientation.x < 0) {
                        animation.play(BarbareAnimType::IDLE_LEFT);
                    } else if (orientation.y > 0) {
                        animation.play(BarbareAnimType::IDLE_DOWN);
                    } else if (orientation.y < 0) {
                        animation.play(BarbareAnimType::IDLE_UP);
                    }
                }
            }
        }
    }
}

void barbarianStartAttackSys(MainFixedSystem, World& world) {
    auto players = world.view<Animation, const Orientation, const Transform2D, const PlayerDamage, const PlayerAttackCooldown>(with<Player, Barbarian>, without<IsBarbarianAttack>);

    for (auto [playerEnt, animation, orientation, transform, playerDamage, playerAttackCooldown]: players) {
        if (vulkanEngine.window.isKeyDown(ButtonNameType::A_BUTTON)) {
            for (auto [buttonAIconEnt, buttonAIconTransform]: world.view<Transform2D>(with<ButtonAIconInventoryBar>, without<ShrinkIcon>)) {
                if (!world.has<ShrinkIcon>(buttonAIconEnt)) {
                    buttonAIconTransform.scale(-0.1f, -0.1f);
                    world.add(buttonAIconEnt, ShrinkIcon(glm::vec2(-0.1f, -0.1f), 0.05f));
                }
            }

            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play(BarbareAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(BarbareAnimType::ATTACK_RIGHT);
                }
                if (auto optLaser = world.get<PlayerLaser>(playerEnt)) {
                    auto [playerLaser] = optLaser.value();
                    if (playerLaser.canShot()) {
                        playerLaser.resetCurTime();
                        instantiateLaserParticle(world, transform.getPosition(), glm::vec2(1, 0), 90, 256.f);
                    }
                }
                if (!world.has<PlayerAttackWeight>(playerEnt)) {
                    world.add(playerEnt, PlayerAttackWeight(glm::vec2(2, 0), 16.f, 0.075f));
                }
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
                            transform.getPosition() + glm::vec2(8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -40 / 2, 40, 40)
                    )
                });
            } else if (orientation.x < 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play(BarbareAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(BarbareAnimType::ATTACK_LEFT);
                }
                if (auto optLaser = world.get<PlayerLaser>(playerEnt)) {
                    auto [playerLaser] = optLaser.value();
                    if (playerLaser.canShot()) {
                        playerLaser.resetCurTime();
                        instantiateLaserParticle(world, transform.getPosition(), glm::vec2(-1, 0), 270, 256.f);
                    }
                }
                if (!world.has<PlayerAttackWeight>(playerEnt)) {
                    world.add(playerEnt, PlayerAttackWeight(glm::vec2(-2, 0), 16.f, 0.075f));
                }
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
                            transform.getPosition() + glm::vec2(-8, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -40 / 2, 40, 40)
                    )
                });
            } else if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play(BarbareAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(BarbareAnimType::ATTACK_DOWN);
                }
                if (auto optLaser = world.get<PlayerLaser>(playerEnt)) {
                    auto [playerLaser] = optLaser.value();
                    if (playerLaser.canShot()) {
                        playerLaser.resetCurTime();
                        instantiateLaserParticle(world, transform.getPosition(), glm::vec2(0, 1), 180, 256.f);
                    }
                }
                if (!world.has<PlayerAttackWeight>(playerEnt)) {
                    world.add(playerEnt, PlayerAttackWeight(glm::vec2(0, 2), 16.f, 0.075f));
                }
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
                            transform.getPosition() + glm::vec2(0, 8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -40 / 2, 40, 40)
                    )
                });
            } else if (orientation.y < 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play(BarbareAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(BarbareAnimType::ATTACK_UP);
                }
                if (auto optLaser = world.get<PlayerLaser>(playerEnt)) {
                    auto [playerLaser] = optLaser.value();
                    if (playerLaser.canShot()) {
                        playerLaser.resetCurTime();
                        instantiateLaserParticle(world, transform.getPosition(), glm::vec2(0, -1), 0, 256.f);
                    }
                }
                if (!world.has<PlayerAttackWeight>(playerEnt)) {
                    world.add(playerEnt, PlayerAttackWeight(glm::vec2(0, -2), 16.f, 0.075f));
                }
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
                        Transform2D(
                            transform.getPosition() + glm::vec2(0, -8),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -40 / 2, 40, 40)
                    )
                });
            }
            world.add(playerEnt, IsBarbarianAttack(playerAttackCooldown.getAttackCooldown()));
        }
    }
}

void barbarianStopAttackSys(MainFixedSystem, World& world) {
    auto players = world.view<IsBarbarianAttack>(with<Player, Barbarian>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, isBarbarianAttack]: players) {
        if (isBarbarianAttack.canStopAttack(time.fixedDelta())) {
            world.remove<IsBarbarianAttack>(playerEnt);
        }
    }
}