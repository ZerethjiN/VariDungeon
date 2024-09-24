#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void sarcophageShadowMarkSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophageShadowMark, Orientation, const Sarcophage, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophageShadowMark, orientation, sarcophage, speed, enemyTransform, zindex]: enemies) {
        if (isSarcophageShadowMark.canSpawnShadowMark(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                instantiateShadowMarkParticle(world, playerTransform.getPosition());
            }
        }

        if (isSarcophageShadowMark.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsSarcophageShadowMark>(enemyEnt);
            world.add_component(enemyEnt, IsSarcophagePreLaserAttack(sarcophage.preLaserDuration));

            for (int i = 1; i < 7; i++) {
                world.append_children(enemyEnt, {
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex),
                    instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex)
                });
            }
            
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
                animation.play(SarcophageAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(SarcophageAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(SarcophageAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(SarcophageAnimType::MOVE_UP);
            }
        }
    }
}

void sarcophagePreLaserSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophagePreLaserAttack, Orientation, const Sarcophage, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophagePreLaserAttack, orientation, sarcophage, speed, enemyTransform]: enemies) {
        if (isSarcophagePreLaserAttack.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsSarcophagePreLaserAttack>(enemyEnt);
            world.add_component(enemyEnt, IsSarcophageLaserAttack(sarcophage.laserDuration));

            world.append_children(enemyEnt, {
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),   0, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),  90, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 180, sarcophage.laserDuration, 32.f),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 270, sarcophage.laserDuration, 32.f),
            });
    
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
                animation.play(SarcophageAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(SarcophageAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(SarcophageAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(SarcophageAnimType::MOVE_UP);
            }
        }
    }
}

void sarcophageLaserSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSarcophageLaserAttack, Orientation, const Sarcophage, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSarcophageLaserAttack, orientation, sarcophage, speed, enemyTransform]: enemies) {
        if (isSarcophageLaserAttack.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsSarcophageLaserAttack>(enemyEnt);
            world.add_component(enemyEnt, IsSarcophageObelisk(sarcophage.obeliskDuration));
            for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                for (int i = 0; i < 2; i++) {
                    auto rndX = rand() % 6;
                    auto rndY = rand() % 3;
                    instantiateSarcophageObelisk(world, roomTransform.getPosition() + glm::vec2((rndX * 16) - 48, (rndY * 32) - 40));
                }
            }
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
                animation.play(SarcophageAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(SarcophageAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(SarcophageAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(SarcophageAnimType::MOVE_UP);
            }
        }
    }
}


void sarcophageObeliskSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsSarcophageObelisk, const Orientation, const Sarcophage, const Speed, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [enemyEnt, animation, isSarcophageObelisk, orientation, sarcophage, speed, enemyTransform]: enemies) {
        if (isSarcophageObelisk.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsSarcophageObelisk>(enemyEnt);
            world.add_component(enemyEnt, IsSarcophageShadowMark(sarcophage.shadowMarkDuration, sarcophage.nbShadowMark));
            for (auto [obeliskEnt]: world.view(with<SarcophageObelisk>)) {
                world.delete_entity(obeliskEnt);
            }
            world.append_children(enemyEnt, {
                world.create_entity(
                    SarcophageShockwave(),
                    Sprite(textureManager, levelUpShockwaveUV),
                    Transform2D(
                        enemyTransform.getPosition(),
                        0,
                        glm::vec2(1, 1)
                    ),
                    LifeTime(0.25f),
                    ZIndex(99)
                )
            });
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                animation.play(SarcophageAnimType::ATTACK_RIGHT);
            } else {
                animation.play(SarcophageAnimType::ATTACK_LEFT);
            }
        } else {
            if (orientation.y > 0) {
                animation.play(SarcophageAnimType::ATTACK_DOWN);
            } else {
                animation.play(SarcophageAnimType::ATTACK_UP);
            }
        }
    }
}

void sarcophageShockwaveSys(MainFixedSystem, World& world) {
    auto preMenus = world.view<Transform2D>(with<SarcophageShockwave>);

    auto [time] = world.resource<Time>();

    for (auto [preMenuEnt, transform]: preMenus) {
        transform.scale(glm::vec2(32, 32) * time.fixedDelta());
    }
}