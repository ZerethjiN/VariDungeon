#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shadowBossHubMovementSys(MainFixedSystem, World& world) {
    auto bosses = world.query<Velocity, ShadowBossHubPattern, const Speed, const Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [bossEnt, velocity, shadowBoss, speed, transform]: bosses) {
        if (glm::distance(transform.getPosition(), shadowBoss.movePoints[shadowBoss.curPoint]) <= 4.f) {
            shadowBoss.curPoint++;
            if (shadowBoss.curPoint >= shadowBoss.movePoints.size()) {
                world.delete_entity(bossEnt);
                for (auto [kingEnt, kingTransform]: world.query<const Transform2D>(with<King>)) {
                    instantiateWarp(world, kingTransform.getPosition());
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(-24, 24));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(24, 40));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(-40, 72));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(56, 8));
                    world.delete_entity(kingEnt);
                }
                appliedCameraShake(world, 0.5f, 128.f, 2);
                appliedCurCameraAberation(world, 4, 0.1);
                for (auto [torchEnt, torchAnimation]: world.query<Animation>(with<TorchDecor, ParticleGenerator>)) {
                    torchAnimation.play(TorchAnimType::OFF);
                    world.remove_components<ParticleGenerator>(torchEnt);
                }
            }
        } else {
            glm::vec2 newdirection = glm::normalize(shadowBoss.movePoints[shadowBoss.curPoint] - transform.getPosition());

            velocity += newdirection * speed.speed * time.fixedDelta();
        }
    }
}

void shadow_boss_move_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsShadowBossMove, Orientation, ShadowBoss, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, velocity, animation, is_shadow_boss_move, orientation, shadow_boss, speed, enemy_transform]: enemies) {
        if (is_shadow_boss_move.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossMove>(enemy_ent);

            std::size_t rnd;
            do {
                rnd = rand() % 4;
            } while(rnd == shadow_boss.last_state);
            shadow_boss.last_state = rnd;

            switch (rnd) {
                case 0:
                    world.add_components(enemy_ent, IsShadowBossPreLaser(shadow_boss.pre_laser_duration));
                    for (auto i = 1; i < 8; i++) {
                        world.append_children(enemy_ent, {
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(16 * i, 0), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(-16 * i, 0), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(0, 16 * i), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(0, -16 * i), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(16 * i, 16 * i), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(-16 * i, 16 * i), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(16 * i, -16 * i), 15),
                            instantiateFloorCrossParticle(world, enemy_transform.getPosition() + glm::vec2(-16 * i, -16 * i), 15),
                        });
                    }
                    break;

                case 1:
                    world.add_components(enemy_ent,
                        IsShadowBossShadowMarkDuration(shadow_boss.shadow_mark_duration),
                        IsShadowBossShadowMarkInvocation(shadow_boss.shadow_mark_duration / shadow_boss.nb_shadow_mark)
                    );
                    for (auto i = 1; i < 8; i++) {
                        instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2( i * 16.f, 0));
                        instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(-i * 16.f, 0));
                        instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(0,  i * 16.f));
                        instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(0, -i * 16.f));
                        // instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2( i * 16.f, i * 16.f));
                        // instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(-i * 16.f, i * 16.f));
                        // instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(i * 16.f, -i * 16.f));
                        // instantiateGroundCrystalAttack(world, enemy_transform.getPosition() + glm::vec2(-i * 16.f, -i * 16.f));
                    }
                    break;

                case 2:
                    world.add_components(enemy_ent, IsShadowBossMinionPreSpawn(shadow_boss.minion_pre_spawn_duration));
                    for (auto [_, room_transform]: world.query<const Transform2D>(with<ChunkInfos>)) {
                        instantiateFloorCrossParticle(world, room_transform.getPosition() + glm::vec2(40, -40), 15);
                        instantiateFloorCrossParticle(world, room_transform.getPosition() + glm::vec2(40, 24), 15);
                        instantiateFloorCrossParticle(world, room_transform.getPosition() + glm::vec2(-56, -40), 15);
                        instantiateFloorCrossParticle(world, room_transform.getPosition() + glm::vec2(-56, 24), 15);
                    }
                    break;

                case 3: {
                        world.remove_components<Collider>(enemy_ent);
                        world.add_components(enemy_ent, IsShadowBossShadowExplosion(shadow_boss.shadow_explosion_duration));

                        std::size_t shadowRnd;
                        do {
                            shadowRnd = rand() % 4;
                        } while(shadowRnd == shadow_boss.last_shadow_rnd);
                        shadow_boss.last_shadow_rnd = rnd;

                        for (auto [_, room_transform]: world.query<const Transform2D>(with<ChunkInfos>)) {
                            if (shadowRnd != 0) {
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-56, -44));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-24, -44));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-56, -28));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-24, -28));
                            }
                            if (shadowRnd != 1) {
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+40, -44));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+8, -44));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+40, -28));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+8, -28));
                            }
                            if (shadowRnd != 2) {
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-56, +36));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-24, +36));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-56, +20));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(-24, +20));
                            }
                            if (shadowRnd != 3) {
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+40, +36));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+8, +36));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+40, +20));
                                instantiateShadowMarkParticle(world, room_transform.getPosition() + glm::vec2(+8, +20));
                            }
                        }

                        if (fabs(orientation.x) > fabs(orientation.y)) {
                            if (orientation.x > 0) {
                                animation.play(ShadowBossAnimType::VANISH_RIGHT);
                            } else {
                                animation.play(ShadowBossAnimType::VANISH_LEFT);
                            }
                        } else {
                            if (orientation.y > 0) {
                                animation.play(ShadowBossAnimType::VANISH_DOWN);
                            } else {
                                animation.play(ShadowBossAnimType::VANISH_UP);
                            }
                        }
                    }
                    break;
            }

            continue;
        }

        glm::vec2 new_direction;
        for (auto [_, player_transform]: players) {
            new_direction = glm::normalize(player_transform.getPosition() - enemy_transform.getPosition());
        }

        velocity += new_direction * speed.speed * time.fixedDelta();
        if (fabs(new_direction.x) > fabs(new_direction.y)) {
            if (new_direction.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_RIGHT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_LEFT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (new_direction.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_DOWN);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_UP);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_UP);
                }
            }
        }
    }
}

void shadow_boss_pre_laser_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsShadowBossPreLaser, const Orientation, const ShadowBoss, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, animation, is_shadow_boss_pre_laser, orientation, shadow_boss, enemy_transform]: enemies) {
        if (is_shadow_boss_pre_laser.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossPreLaser>(enemy_ent);
            world.add_components(enemy_ent, IsShadowBossLaser(shadow_boss.laser_duration));
            world.append_children(enemy_ent, {
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(),   0, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(),  45, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(),  90, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(), 135, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(), 180, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(), 225, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(), 270, shadow_boss.laser_duration, 20.f),
                instantiateMegaLaserParticle(world, enemy_transform.getPosition(), 315, shadow_boss.laser_duration, 20.f),
            });
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_RIGHT);
                } else {
                    animation.play(ShadowBossAnimType::CAST_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_LEFT);
                } else {
                    animation.play(ShadowBossAnimType::CAST_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_DOWN);
                } else {
                    animation.play(ShadowBossAnimType::CAST_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_UP);
                } else {
                    animation.play(ShadowBossAnimType::CAST_UP);
                }
            }
        }
    }
}

void shadow_boss_laser_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsShadowBossLaser, const Orientation, const ShadowBoss>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, animation, is_shadow_boss_laser, orientation, shadow_boss]: enemies) {
        if (is_shadow_boss_laser.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossLaser>(enemy_ent);
            world.add_components(enemy_ent, IsShadowBossMove(shadow_boss.move_duration));
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_RIGHT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_LEFT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_DOWN);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_UP);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_UP);
                }
            }
        }
    }
}

void shadow_boss_shadow_mark_duration_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsShadowBossShadowMarkDuration, Orientation, const ShadowBoss, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, velocity, animation, is_shadow_boss_shadow_mark_duration, orientation, shadow_boss, speed, enemy_transform]: enemies) {
        if (is_shadow_boss_shadow_mark_duration.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossShadowMarkDuration, IsShadowBossShadowMarkInvocation>(enemy_ent);
            world.add_components(enemy_ent, IsShadowBossMove(shadow_boss.move_duration));
        }

        glm::vec2 new_direction;
        for (auto [_, player_transform]: players) {
            new_direction = glm::normalize(player_transform.getPosition() - enemy_transform.getPosition());
        }

        velocity += new_direction * speed.speed * time.fixedDelta();
        if (fabs(new_direction.x) > fabs(new_direction.y)) {
            if (new_direction.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_RIGHT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_LEFT);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (new_direction.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_DOWN);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_UP);
                } else {
                    animation.play(ShadowBossAnimType::MOVE_UP);
                }
            }
        }
    }
}

void shadow_boss_shadow_mark_invocation_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<IsShadowBossShadowMarkInvocation>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [_, is_shadow_boss_shadow_mark_invocation]: enemies) {
        if (is_shadow_boss_shadow_mark_invocation.canTick(time.fixedDelta())) {
            for (auto [_, player_transform]: players) {
                instantiateShadowMarkParticle(world, player_transform.getPosition());
            }
        }
    }
}

void shadow_boss_minion_pre_spawn_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsShadowBossMinionPreSpawn, Orientation, const ShadowBoss, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, velocity, animation, is_shadow_boss_minion_pre_spawn, orientation, shadow_boss, speed, enemy_transform]: enemies) {
        if (is_shadow_boss_minion_pre_spawn.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossMinionPreSpawn>(enemy_ent);
            world.add_components(enemy_ent, IsShadowBossMove(shadow_boss.move_duration));
            for (auto [_, room_transform]: world.query<const Transform2D>(with<ChunkInfos>)) {
                instantiateShadowMinion(world, room_transform.getPosition() + glm::vec2(40, -40));
                instantiateShadowMinion(world, room_transform.getPosition() + glm::vec2(40, 24));
                instantiateShadowMinion(world, room_transform.getPosition() + glm::vec2(-56, -40));
                instantiateShadowMinion(world, room_transform.getPosition() + glm::vec2(-56, 24));
            }
        }

        glm::vec2 new_direction;
        for (auto [_, player_transform]: players) {
            new_direction = glm::normalize(player_transform.getPosition() - enemy_transform.getPosition());
        }

        velocity += new_direction * speed.speed * time.fixedDelta();
        if (fabs(new_direction.x) > fabs(new_direction.y)) {
            if (new_direction.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_RIGHT);
                } else {
                    animation.play(ShadowBossAnimType::CAST_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_LEFT);
                } else {
                    animation.play(ShadowBossAnimType::CAST_LEFT);
                }
            }
        } else {
            if (new_direction.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_DOWN);
                } else {
                    animation.play(ShadowBossAnimType::CAST_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowBossAnimType::HIT_UP);
                } else {
                    animation.play(ShadowBossAnimType::CAST_UP);
                }
            }
        }
    }
}

void shadow_boss_shadow_explosion_sys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsShadowBossShadowExplosion, Orientation, const ShadowBoss, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, velocity, animation, is_shadow_boss_shadow_explosion, orientation, shadow_boss, speed, enemy_transform]: enemies) {
        if (is_shadow_boss_shadow_explosion.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsShadowBossShadowExplosion>(enemy_ent);
            world.add_components(enemy_ent,
                IsShadowBossMove(shadow_boss.move_duration),
                Collider(-24 / 2, -24 / 2, 24, 24)
            );
        }

        glm::vec2 new_direction;
        for (auto [_, player_transform]: players) {
            new_direction = glm::normalize(player_transform.getPosition() - enemy_transform.getPosition());
        }

        velocity += new_direction * speed.speed * time.fixedDelta();
        if (fabs(new_direction.x) > fabs(new_direction.y)) {
            if (new_direction.x > 0) {
                orientation = Orientation::EAST;
            } else {
                orientation = Orientation::WEST;
            }
        } else {
            if (new_direction.y > 0) {
                orientation = Orientation::SOUTH;
            } else {
                orientation = Orientation::NORTH;
            }
        }
    }
}