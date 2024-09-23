#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void megaSlimeMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeMove, Orientation, MegaSlime, const Speed, const Transform2D, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeMove, orientation, megaSlime, speed, enemyTransform, life]: enemies) {
        if (isMegaSlimeMove.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMegaSlimeMove>(enemyEnt);
            unsigned int rnd;
            do {
                rnd = rand() % 3;
            } while(megaSlime.lastState == rnd);

            switch (rnd) {
                case 0:
                    animation.play(MegaSlimeAnimType::SHADOW);
                    if (world.has<Collider>(enemyEnt)) {
                        world.remove_component<Collider>(enemyEnt);
                    }
                    world.add_component(enemyEnt, IsMegaSlimeBounce(megaSlime.bounceDuration, megaSlime.bounceCooldownLvl1, megaSlime.bounceCooldownLvl2, megaSlime.bounceGroundDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
                    break;
                case 1:
                    world.add_component(enemyEnt, IsMegaSlimeFireball(megaSlime.fireballDuration, megaSlime.fireballCooldownLvl1, megaSlime.fireballCooldownLvl2, life.getNbLife() / 2 >= life.getCurNbLife()));
                    break;
                case 2: world.add_component(enemyEnt, IsMegaSlimeSpawn(megaSlime.spawnDuration, megaSlime.spawnCooldownLvl1, megaSlime.spawnCooldownLvl2, life.getNbLife() / 2 >= life.getCurNbLife())); break;
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
                        animation.play(MegaSlimeAnimType::P2_HIT_MOVE_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_MOVE_RIGHT);
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_MOVE_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::MOVE_RIGHT);
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_MOVE_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_MOVE_LEFT);
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_MOVE_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::MOVE_LEFT);
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_MOVE_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_MOVE_DOWN);
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_MOVE_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::MOVE_DOWN);
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_MOVE_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_MOVE_UP);
                    }
                } else {
                    if (isMegaSlimeMove.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_MOVE_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::MOVE_UP);
                    }
                }
            }
        }
    }
}

void megaSlimeFireballSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeFireball, Orientation, const MegaSlime, const Transform2D, const Life, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeFireball, orientation, megaSlime, transform, life, zindex]: enemies) {
        if (isMegaSlimeFireball.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMegaSlimeFireball>(enemyEnt);
            world.add_component(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
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
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                    }
                } else {
                    if (isMegaSlimeFireball.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_UP);
                    }
                }
            }
        }
    }
}

void megaSlimeBounceSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeBounce, Orientation, const MegaSlime, const Transform2D, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeBounce, orientation, megaSlime, transform, life]: enemies) {
        if (isMegaSlimeBounce.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMegaSlimeBounce>(enemyEnt);
            world.add_component(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
            if (!world.has<Collider>(enemyEnt)) {
                appliedCameraShake(world, 0.5f, 128.f, 2);
                world.add_component(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
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
                animation.play(MegaSlimeAnimType::SHADOW);
                if (world.has<Collider>(enemyEnt)) {
                    world.remove_component<Collider>(enemyEnt);
                }
            } else {
                appliedCameraShake(world, 0.5f, 128.f, 2);
                if (!world.has<Collider>(enemyEnt)) {
                    world.add_component(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
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
                            animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_RIGHT);
                        } else {
                            animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_ATTACK_RIGHT);
                        } else {
                            animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                        }
                    }
                } else {
                    orientation = Orientation::WEST;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_LEFT);
                        } else {
                            animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_ATTACK_LEFT);
                        } else {
                            animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                        }
                    }
                }
            } else {
                if (orientation.y > 0) {
                    orientation = Orientation::SOUTH;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_DOWN);
                        } else {
                            animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_ATTACK_DOWN);
                        } else {
                            animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                        }
                    }
                } else {
                    orientation = Orientation::NORTH;
                    if (world.has<InvincibleFrame>(enemyEnt)) {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_UP);
                        } else {
                            animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                        }
                    } else {
                        if (isMegaSlimeBounce.getIsP2()) {
                            animation.play(MegaSlimeAnimType::P2_ATTACK_UP);
                        } else {
                            animation.play(MegaSlimeAnimType::ATTACK_UP);
                        }
                    }
                }
            }
        }
    }
}

void megaSlimeSpawnSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeSpawn, Orientation, const MegaSlime, const Speed, const Transform2D, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeSpawn, orientation, megaSlime, speed, transform, life]: enemies) {
        if (isMegaSlimeSpawn.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMegaSlimeSpawn>(enemyEnt);
            world.add_component(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration, life.getNbLife() / 2 >= life.getCurNbLife()));
            // instantiateSlimeSlimeBoss(world, transform.getPosition() + glm::vec2(8, 0));
            for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(40, -40));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(40, 24));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-56, -40));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-56, 24));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-8, -8));
            }
            continue;
        }

        // if (isMegaSlimeSpawn.canSpawn(time.fixedDelta())) {
        //     instantiateSlimeSlimeBoss(world, transform.getPosition() + glm::vec2(8, 0));
        // }

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
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                    }
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                    }
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                    }
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_HIT_ATTACK_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                    }
                } else {
                    if (isMegaSlimeSpawn.getIsP2()) {
                        animation.play(MegaSlimeAnimType::P2_ATTACK_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_UP);
                    }
                }
            }
        }
    }
}