#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void openDoorSys(MainFixedSystem, World& world) {
    auto enemies = world.query(with<Enemy>);

    if (enemies.empty()) {
        auto doors = world.query(with<Sprite, Collider, IsDoorLock>, without<Trigger, IsDoorWithKey>);

        for (auto [doorEnt]: doors) {
            world.remove_components<Sprite, Collider, IsDoorLock>(doorEnt);
            world.add_components(doorEnt, Trigger(-32 / 2, -8 / 2, 32, 8));
        }
    }
}

void openDoorWithKeySys(MainFixedSystem, World& world) {
    auto doors = world.query<const OnCollisionEnter>(with<IsDoorLock, IsDoorWithKey>, without<Trigger>);

    for (auto [_, door_collision]: doors) {
        for (const auto& oth_ent: door_collision) {
            if (world.has_components<IsPlayerKey>(oth_ent)) {
                for (auto [door_ent]: world.query(with<Sprite, Collider, IsDoorLock, IsDoorWithKey>, without<Trigger>)) {
                    world.remove_components<Sprite, Collider, IsDoorLock, IsDoorWithKey>(door_ent);
                    world.add_components(door_ent, Trigger(-32 / 2, -8 / 2, 32, 8));
                }
                world.remove_components<IsPlayerKey>(oth_ent);
                for (auto [_, keyUI]: world.query<UI>(with<PlayerKeyIcon>)) {
                    keyUI.setTextureRect(HUDElementsUV[6]);
                }
            }
        }
    }
}

void doorCameraMovementSys(MainFixedSystem, World& world) {
    auto cameras = world.query<Transform2D, const ChunkCameraMovement>();

    auto [time] = world.resource<const Time>();

    for (auto [cameraEnt, cameraTransform, chunkCameraMovement]: cameras) {
        if (auto opt = world.get_components<const Transform2D>(chunkCameraMovement.getNextRoomEnt())) {
            auto [nextTransform] = opt.value();

            if (glm::distance(nextTransform.getPosition() + glm::vec2(-8, 0), cameraTransform.getPosition()) < 8) {
                cameraTransform.setPosition(nextTransform.getPosition() + glm::vec2(-8, 0));
                world.remove_components<ChunkCameraMovement>(cameraEnt);
                world.setInactive(chunkCameraMovement.getOldRoomEnt());

                for (auto [playerEnt]: world.query(with<Player, Unmoveable>)) {
                    world.remove_components<Unmoveable>(playerEnt);
                }
            } else {
                cameraTransform.move(glm::normalize(nextTransform.getPosition() + glm::vec2(-8, 0) - cameraTransform.getPosition()) * chunkCameraMovement.getCameraSpeed() * time.fixedDelta());
            }
        } else {
            world.remove_components<ChunkCameraMovement>(cameraEnt);
        }
    }
}

void doorTriggerSys(MainFixedSystem, World& world) {
    auto doors = world.query<const OnCollisionEnter, const DoorTrigger>(without<IsDoorLock>);

    for (auto [_, collisions, doorTrigger]: doors) {
        for (auto othEnt: collisions) {
            if (world.has_components<Player, Transform2D>(othEnt)) {
                Ent nextRoomEnt = 0;
                for (auto [_, exploration, chunkTable]: world.query<ChunkExploration, const ChunkTable>()) {
                    nextRoomEnt = chunkTable.getChunkById(doorTrigger.getNextRoomIdx());
                    exploration.roomTypes[doorTrigger.curRoomXY.y][doorTrigger.curRoomXY.x] = ChunkExploration::ROOM_EXPLORATION_KNOW;
                    exploration.roomTypes[doorTrigger.nextRoomXY.y][doorTrigger.nextRoomXY.x] = ChunkExploration::ROOM_EXPLORATION_PLAYER;
                }

                Ent curRoomEnt = 0;
                for (auto [roomEnt]: world.query(with<ChunkInfos>)) {
                    curRoomEnt = roomEnt;
                }

                for (auto [cameraEnt]: world.query(with<CurCamera>)) {
                    if (auto optParent = world.get_parent(cameraEnt)) {
                        auto cameraParentEnt = optParent.value();
                        if (curRoomEnt != 0 && nextRoomEnt != 0) {
                            world.add_components(cameraParentEnt, ChunkCameraMovement(curRoomEnt, nextRoomEnt, 384.f));
                        }
                        // if (auto optCameraParent = world.get_components<Transform2D>(cameraParentEnt)) {
                        //     auto [cameraParentTransform] = optCameraParent.value();
                        //     if (auto opt = world.get_components<const Transform2D>(nextRoomEnt)) {
                        //         auto [nextRoomTransform] = opt.value();
                        //         cameraParentTransform.setPosition(nextRoomTransform.getPosition());
                        //     }
                        // }
                    }
                }

                if (auto opt = world.get_components<Transform2D>(othEnt)) {
                    auto [playerTransform] = opt.value();
                    switch (doorTrigger.getOrientation()) {
                        case DoorTrigger::DOOR_TRIGGER_NORTH:
                            playerTransform.moveY(-40);
                            break;
                        case DoorTrigger::DOOR_TRIGGER_SOUTH:
                            playerTransform.moveY(40);
                            break;
                        case DoorTrigger::DOOR_TRIGGER_EAST:
                            playerTransform.moveX(40);
                            break;
                        case DoorTrigger::DOOR_TRIGGER_WEST:
                            playerTransform.moveX(-40);
                            break;
                    };
                }

                world.add_components(othEnt, Unmoveable());

                if (curRoomEnt != 0 && nextRoomEnt != 0) {
                    world.setActive(nextRoomEnt);
                }
            }
        }
    }
}