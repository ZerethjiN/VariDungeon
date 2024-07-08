#pragma once

#include <Zerengine.hpp>

class CameraEffect final {
public:
    CameraEffect():
        canUseCameraShake(false),
        canUseCameraAberation(false),
        aberationDistance(0),
        aberationDuration(0),
        shakeSpeed(0),
        shakeDistance(0),
        nbShake(0) {
    }

public:
    bool canUseCameraShake;
    bool canUseCameraAberation;

    float aberationDistance;
    float aberationDuration;

    float shakeSpeed;
    float shakeDistance;
    float nbShake;
};

class CameraAberation final {
public:
    CameraAberation(float newDistance, float newDuration):
        distance(newDistance),
        duration(newDuration),
        curTime(0) {
    }

    bool canStopAberation(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

public:
    float distance;
    float duration;
    float curTime;
};

void appliedCurCameraAberation(World& world, float newDistance, float newDuration) {
    auto aberations = world.view<CameraAberation>();

    if (!aberations.empty()) {
        for (auto [_, aberation]: aberations) {
            aberation.distance = newDistance;
            aberation.duration = newDuration;
            aberation.curTime = 0;
        }
    } else {
        auto curCameras = world.view<CameraEffect>(with<CurCamera>);

        for (auto [_, cameraEffect]: curCameras) {
            cameraEffect.canUseCameraAberation = true;
            cameraEffect.aberationDistance = newDistance;
            cameraEffect.aberationDuration = newDuration;
            // if (!world.has<CameraAberation>(curCameraEnt)) {
            //     world.add(curCameraEnt, CameraAberation(newDistance, newDuration));
            // }
        }
    }
}

void appliedCameraShake(World& world, float distance, float speed, unsigned int nbShake) {
    auto cameras = world.view<CameraEffect>(with<CurCamera>, without<CameraShake>);

    for (auto [_, cameraEffect]: cameras) {
        cameraEffect.canUseCameraShake = true;
        cameraEffect.shakeSpeed = speed;
        cameraEffect.shakeDistance = distance;
        cameraEffect.nbShake = nbShake;
        // if (!world.has<CameraShake>(entCam)) {
        //     if (auto parentOpt = world.getParent(entCam)) {
        //         auto parentEnt = parentOpt.value();
        //         world.add(
        //             entCam,
        //             CameraShake(
        //                 /*OriginEnt:*/ parentEnt,
        //                 /*Distance:*/ distance,
        //                 /*Speed:*/ speed,
        //                 /*NbShake:*/ nbShake
        //             ),
        //             CameraShakeLeft()
        //         );
        //     }
        // }
    }
}