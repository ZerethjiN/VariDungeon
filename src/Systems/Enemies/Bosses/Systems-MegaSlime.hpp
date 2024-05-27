#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void megaSlimeMoveSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeMove, Orientation, MegaSlime, const Speed, const Transform, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeMove, orientation, megaSlime, speed, enemyTransform, life]: enemies) {
        if (isMegaSlimeMove.canSwitchState(time.fixedDelta())) {
            world.del<IsMegaSlimeMove>(enemyEnt);
            unsigned int rnd;
            do {
                rnd = rand() % 3;
            } while(megaSlime.lastState == rnd);

            switch (rnd) {
                case 0:
                    animation.play("Shadow");
                    if (world.has<Collider>(enemyEnt)) {
                        world.del<Collider>(enemyEnt);
                    }
                    world.add(enemyEnt, IsMegaSlimeBounce(megaSlime.bounceDuration, megaSlime.bounceCooldownLvl1, megaSlime.bounceCooldownLvl2, megaSlime.bounceGroundDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
                    break;
                case 1:
                    world.add(enemyEnt, IsMegaSlimeFireball(megaSlime.fireballDuration, megaSlime.fireballCooldownLvl1, megaSlime.fireballCooldownLvl2, life.getNbLife() / 2 >= life.getCurNbLife()));
                    break;
                case 2: world.add(enemyEnt, IsMegaSlimeSpawn(megaSlime.spawnDuration, megaSlime.spawnCooldownLvl1, megaSlime.spawnCooldownLvl2, life.getNbLife() / 2 >= life.getCurNbLife())); break;
            }
            megaSlime.lastState = rnd;
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
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2HitMoveRight");
                    } else {
                        animation.play("HitMoveRight");
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2MoveRight");
                    } else {
                        animation.play("MoveRight");
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2HitMoveLeft");
                    } else {
                        animation.play("HitMoveLeft");
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2MoveLeft");
                    } else {
                        animation.play("MoveLeft");
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2HitMoveDown");
                    } else {
                        animation.play("HitMoveDown");
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2MoveDown");
                    } else {
                        animation.play("MoveDown");
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2HitMoveUp");
                    } else {
                        animation.play("HitMoveUp");
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play("P2MoveUp");
                    } else {
                        animation.play("MoveUp");
                    }
                }
            }
        }
    }
}

void megaSlimeFireballSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeFireball, Orientation, const MegaSlime, const Transform, const Life, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeFireball, orientation, megaSlime, transform, life, zindex]: enemies) {
        if (isMegaSlimeFireball.canSwitchState(time.fixedDelta())) {
            world.del<IsMegaSlimeFireball>(enemyEnt);
            world.add(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
            continue;
        }

        if (isMegaSlimeFireball.canCastFireball(time.fixedDelta())) {
            auto curFireball = isMegaSlimeFireball.getCurFireball();
            switch (curFireball) {
                case 0: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, -1), 64.f); break;
                case 1: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, -1), 64.f); break;
                case 2: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 0), 64.f); break;
                case 3: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 1), 64.f); break;
                case 4: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, 1), 64.f); break;
                case 5: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 1), 64.f); break;
                case 6: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 0), 64.f); break;
                case 7: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, -1), 64.f); break;
            }

            switch ((curFireball + 4) % 8) {
                case 0: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, -1), 64.f); break;
                case 1: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, -1), 64.f); break;
                case 2: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 0), 64.f); break;
                case 3: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 1), 64.f); break;
                case 4: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, 1), 64.f); break;
                case 5: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 1), 64.f); break;
                case 6: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 0), 64.f); break;
                case 7: instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, -1), 64.f); break;
            }
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - transform.getPosition());
        }

        velocity += newdirection * megaSlime.fireballMegaSlimeMoveSpeed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2HitAttackRight");
                    } else {
                        animation.play("HitAttackRight");
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2AttackRight");
                    } else {
                        animation.play("AttackRight");
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2HitAttackLeft");
                    } else {
                        animation.play("HitAttackLeft");
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2AttackLeft");
                    } else {
                        animation.play("AttackLeft");
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2HitAttackDown");
                    } else {
                        animation.play("HitAttackDown");
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2AttackDown");
                    } else {
                        animation.play("AttackDown");
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2HitAttackUp");
                    } else {
                        animation.play("HitAttackUp");
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play("P2AttackUp");
                    } else {
                        animation.play("AttackUp");
                    }
                }
            }
        }
    }
}

void megaSlimeBounceSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeBounce, Orientation, const MegaSlime, const Transform, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeBounce, orientation, megaSlime, transform, life]: enemies) {
        if (isMegaSlimeBounce.canSwitchState(time.fixedDelta())) {
            world.del<IsMegaSlimeBounce>(enemyEnt);
            world.add(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
            if (!world.has<Collider>(enemyEnt)) {
                appliedCameraShake(world, 0.5f, 128.f, 2);
                world.add(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
                instantiateEnemyExplosionAttackParticle(world, transform.getPosition());
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, -1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, -1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 0), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 0), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, -1), 48.f);
            }
            continue;
        }
        
        if (isMegaSlimeBounce.canBounce(time.fixedDelta())) {
            if (isMegaSlimeBounce.isJump()) {
                animation.play("Shadow");
                if (world.has<Collider>(enemyEnt)) {
                    world.del<Collider>(enemyEnt);
                }
            } else {
                appliedCameraShake(world, 0.5f, 128.f, 2);
                if (!world.has<Collider>(enemyEnt)) {
                    world.add(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
                }
                instantiateEnemyExplosionAttackParticle(world, transform.getPosition());
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, -1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, -1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 0), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 1), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 0), 48.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, -1), 48.f);
            }
        }

        if (isMegaSlimeBounce.isJump()) {
            glm::vec2 newdirection;
            for (auto [_, playerTransform]: players) {
                newdirection = glm::normalize(playerTransform.getPosition() - transform.getPosition());
            }

            velocity += newdirection * megaSlime.bounceMoveSpeed * time.fixedDelta();
        } else {
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    orientation = Orientation::EAST;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2HitAttackRight");
                        } else {
                            animation.play("HitAttackRight");
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2AttackRight");
                        } else {
                            animation.play("AttackRight");
                        }
                    }
                } else {
                    orientation = Orientation::WEST;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2HitAttackLeft");
                        } else {
                            animation.play("HitAttackLeft");
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2AttackLeft");
                        } else {
                            animation.play("AttackLeft");
                        }
                    }
                }
            } else {
                if (orientation.y > 0) {
                    orientation = Orientation::SOUTH;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2HitAttackDown");
                        } else {
                            animation.play("HitAttackDown");
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2AttackDown");
                        } else {
                            animation.play("AttackDown");
                        }
                    }
                } else {
                    orientation = Orientation::NORTH;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2HitAttackUp");
                        } else {
                            animation.play("HitAttackUp");
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play("P2AttackUp");
                        } else {
                            animation.play("AttackUp");
                        }
                    }
                }
            }
        }
    }
}

void megaSlimeSpawnSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeSpawn, Orientation, const MegaSlime, const Speed, const Transform, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeSpawn, orientation, megaSlime, speed, transform, life]: enemies) {
        if (isMegaSlimeSpawn.canSwitchState(time.fixedDelta())) {
            world.del<IsMegaSlimeSpawn>(enemyEnt);
            world.add(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
            instantiateSlime(world, transform.getPosition() + glm::vec2(8, 0));
            continue;
        }

        if (isMegaSlimeSpawn.canSpawn(time.fixedDelta())) {
            instantiateSlime(world, transform.getPosition() + glm::vec2(8, 0));
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - transform.getPosition());
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2HitAttackRight");
                    } else {
                        animation.play("HitAttackRight");
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2AttackRight");
                    } else {
                        animation.play("AttackRight");
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2HitAttackLeft");
                    } else {
                        animation.play("HitAttackLeft");
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2AttackLeft");
                    } else {
                        animation.play("AttackLeft");
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2HitAttackDown");
                    } else {
                        animation.play("HitAttackDown");
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2AttackDown");
                    } else {
                        animation.play("AttackDown");
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2HitAttackUp");
                    } else {
                        animation.play("HitAttackUp");
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play("P2AttackUp");
                    } else {
                        animation.play("AttackUp");
                    }
                }
            }
        }
    }
}