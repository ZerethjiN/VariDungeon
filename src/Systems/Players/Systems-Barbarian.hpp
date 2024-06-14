#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void barbarianStartDashSys(MainFixedSystem, World& world) {
    auto players = world.view<const Transform, const Orientation, const PlayerDamage>(with<Player, Barbarian>, without<IsBarbarianDash>);

    for (auto [playerEnt, transform, orientation, playerDamage]: players) {
        if (vulkanEngine.window.isKeyDown(B_BUTTON)) {
            glm::vec2 newDirection(0, 0);

            if (orientation.x > 0) {
                newDirection = glm::vec2(1, 0);
                world.appendChildren(playerEnt, {
                    world.newEnt(
                        PlayerWeapon(),
                        Damage(playerDamage),
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
                        Damage(playerDamage),
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
                        Damage(playerDamage),
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
                        Damage(playerDamage),
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

            if (!world.has<Unhittable>(playerEnt)) {
                world.add(playerEnt, Unhittable());
            }
        }
    }
}

void barbarianStopDashSys(MainFixedSystem, World& world) {
    auto players = world.view<IsBarbarianDash>(with<Player, Barbarian>);

    auto [time] = world.resource<const Time>();

    for (auto [playerEnt, isBarbarianDash]: players) {
        if (isBarbarianDash.canStopDash(time.fixedDelta()) || vulkanEngine.window.isKeyUp(B_BUTTON)) {
            world.remove<IsBarbarianDash>(playerEnt);
            if (world.has<Unhittable>(playerEnt)) {
                world.remove<Unhittable>(playerEnt);
            }
        }
    }
}

void barbarianMovementSys(MainFixedSystem, World& world) {
    auto players = world.view<Velocity, Animation, Orientation, const Speed>(with<Player, Barbarian>, without<Unmoveable>);

    auto [time] = world.resource<const Time>();

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
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitDashRight");
                    } else {
                        animation.play("DashRight");
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitMoveRight");
                    } else {
                        animation.play("MoveRight");
                    }
                }
            }
            orientation = Orientation::EAST;
        } else if (newVelocity.x < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitDashLeft");
                    } else {
                        animation.play("DashLeft");
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitMoveLeft");
                    } else {
                        animation.play("MoveLeft");
                    }
                }
            }
            orientation = Orientation::WEST;
        } else if (newVelocity.y > 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitDashDown");
                    } else {
                        animation.play("DashDown");
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitMoveDown");
                    } else {
                        animation.play("MoveDown");
                    }
                }
            }
            orientation = Orientation::SOUTH;
        } else if (newVelocity.y < 0) {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<IsBarbarianDash>(playerEnt)) {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitDashUp");
                    } else {
                        animation.play("DashUp");
                    }
                } else {
                    if (world.has<InvincibleFrame>(playerEnt)) {
                        animation.play("HitMoveUp");
                    } else {
                        animation.play("MoveUp");
                    }
                }
            }
            orientation = Orientation::NORTH;
        } else {
            if (!world.has<IsBarbarianAttack>(playerEnt)) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    if (orientation.x > 0) {
                        animation.play("HitIdleRight");
                    } else if (orientation.x < 0) {
                        animation.play("HitIdleLeft");
                    } else if (orientation.y > 0) {
                        animation.play("HitIdleDown");
                    } else if (orientation.y < 0) {
                        animation.play("HitIdleUp");
                    }
                } else {
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
}

void barbarianStartAttackSys(MainFixedSystem, World& world) {
    auto players = world.view<Animation, const Orientation, const Transform, const PlayerDamage, const PlayerAttackCooldown>(with<Player, Barbarian>, without<IsBarbarianAttack>);

    for (auto [playerEnt, animation, orientation, transform, playerDamage, playerAttackCooldown]: players) {
        if (vulkanEngine.window.isKeyDown(A_BUTTON)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play("HitAttackRight");
                } else {
                    animation.play("AttackRight");
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
                        Transform(
                            transform.getPosition() + glm::vec2(16, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -40 / 2, 32, 40)
                    )
                });
            } else if (orientation.x < 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play("HitAttackLeft");
                } else {
                    animation.play("AttackLeft");
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
                        Transform(
                            transform.getPosition() + glm::vec2(-16, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-32 / 2, -40 / 2, 32, 40)
                    )
                });
            } else if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play("HitAttackDown");
                } else {
                    animation.play("AttackDown");
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
                        Transform(
                            transform.getPosition() + glm::vec2(0, 16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -32 / 2, 40, 32)
                    )
                });
            } else if (orientation.y < 0) {
                if (world.has<InvincibleFrame>(playerEnt)) {
                    animation.play("HitAttackUp");
                } else {
                    animation.play("AttackUp");
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
                        Transform(
                            transform.getPosition() + glm::vec2(0, -16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Velocity(),
                        LifeTime(0.2f),
                        Trigger(-40 / 2, -32 / 2, 40, 32)
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