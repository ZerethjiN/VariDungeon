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
            world.remove_components<IsMegaSlimeMove>(enemyEnt);
            unsigned int rnd;
            do {
                rnd = rand() % 3;
            } while(megaSlime.lastState == rnd);

            switch (rnd) {
                case 0:
                    animation.play(MegaSlimeAnimType::SHADOW);
                    if (world.has_components<Collider>(enemyEnt)) {
                        world.remove_components<Collider>(enemyEnt);
                    }
                    world.add_components(enemyEnt,
                        IsMegaSlimeBounceTotal(megaSlime.bounceDuration),
                        IsMegaSlimeBounce(megaSlime.bounceCooldown, megaSlime.bounceGroundDuration, megaSlime.nbBounce)
                    );
                    break;
                case 1:
                    world.add_components(enemyEnt, IsMegaSlimeFireball(megaSlime.fireballDuration, megaSlime.fireballCooldownLvl1));
                    break;
                case 2:
                    world.add_components(enemyEnt, IsMegaSlimePreSpawn(megaSlime.spawnDuration));
                    for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(40, -40), 15);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(40, 24), 15);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(-56, -40), 15);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(-56, 24), 15);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(-8, -8), 15);
                    }
                    break;
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(MegaSlimeAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(MegaSlimeAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(MegaSlimeAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(MegaSlimeAnimType::MOVE_UP);
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
            world.remove_components<IsMegaSlimeFireball>(enemyEnt);
            world.add_components(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration));
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_UP);
                }
            }
        }
    }
}

void megaSlimeBounceTotalSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMegaSlimeBounceTotal, Orientation, const MegaSlime, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMegaSlimeBounceTotal, orientation, megaSlime, transform]: enemies) {
        if (isMegaSlimeBounceTotal.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsMegaSlimeBounceTotal, IsMegaSlimeBounce>(enemyEnt);
            world.add_components(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration));
            if (!world.has_components<Collider>(enemyEnt)) {
                world.add_components(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
                appliedCameraShake(world, 0.5f, 128.f, 2);
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
    }
}

void megaSlimeBounceSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMegaSlimeBounce, Orientation, const MegaSlime, const Transform2D, const Life>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMegaSlimeBounce, orientation, megaSlime, transform, life]: enemies) {
        if (isMegaSlimeBounce.canBounce(time.fixedDelta())) {
            if (isMegaSlimeBounce.nbBounce > 0) {
                if (isMegaSlimeBounce.isJump()) {
                    animation.play(MegaSlimeAnimType::SHADOW);
                    if (world.has_components<Collider>(enemyEnt)) {
                        world.remove_components<Collider>(enemyEnt);
                    }
                } else {
                    appliedCameraShake(world, 0.5f, 128.f, 2);
                    if (!world.has_components<Collider>(enemyEnt)) {
                        world.add_components(enemyEnt, Collider(-24 / 2, -24 / 2, 24, 24));
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
                    if (world.has_components<InvincibleFrame>(enemyEnt)) {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                    }
                } else {
                    orientation = Orientation::WEST;
                    if (world.has_components<InvincibleFrame>(enemyEnt)) {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                    }
                }
            } else {
                if (orientation.y > 0) {
                    orientation = Orientation::SOUTH;
                    if (world.has_components<InvincibleFrame>(enemyEnt)) {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                    }
                } else {
                    orientation = Orientation::NORTH;
                    if (world.has_components<InvincibleFrame>(enemyEnt)) {
                        animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                    } else {
                        animation.play(MegaSlimeAnimType::ATTACK_UP);
                    }
                }
            }
        }
    }
}

void megaSlimePreSpawnSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMegaSlimePreSpawn, Orientation, const MegaSlime, const Transform2D, const Life>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMegaSlimePreSpawn, orientation, megaSlime, transform, life]: enemies) {
        if (isMegaSlimePreSpawn.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsMegaSlimePreSpawn>(enemyEnt);
            world.add_components(enemyEnt, IsMegaSlimeMove(megaSlime.moveDuration));
            for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(40, -40));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(40, 24));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-56, -40));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-56, 24));
                instantiateSlimeSlimeBoss(world, roomTransform.getPosition() + glm::vec2(-8, -8));
            }
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MegaSlimeAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(MegaSlimeAnimType::ATTACK_UP);
                }
            }
        }
    }
}