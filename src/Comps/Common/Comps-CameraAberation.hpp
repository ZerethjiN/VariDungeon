#pragma once

#include <Zerengine.hpp>

class CameraEffect final: public IComponent {
public:
    CameraEffect():
        canUseCameraShake(false),
        canUseCameraAberation(false),
        aberationDistance(0),
        aberationDuration(0),
        aberationDirection(-1, 0),
        shakeSpeed(0),
        shakeDistance(0),
        nbShake(0) {
    }

public:
    bool canUseCameraShake;
    bool canUseCameraAberation;

    float aberationDistance;
    float aberationDuration;
    glm::vec2 aberationDirection;

    float shakeSpeed;
    float shakeDistance;
    float nbShake;
};

class CameraAberation final: public IComponent {
public:
    CameraAberation(float newDistance, float newDuration, const glm::vec2& newDirection = glm::vec2(1, 0)):
        maxDistance(newDistance),
        distance(0),
        duration(newDuration),
        curTime(0),
        direction(newDirection) {
    }

    bool canStopAberation(float delta) {
        curTime += delta;
        if (curTime <= duration / 2) {
            distance = curTime * maxDistance / (duration / 2);
        } else {
            distance = (duration - curTime) * maxDistance / (duration / 2);
        }
        return curTime >= duration;
    }

public:
    float maxDistance;
    float distance;
    float duration;
    float curTime;
    glm::vec2 direction;
};

void appliedCurCameraAberation(World& world, float newDistance, float newDuration, const glm::vec2& newAberationDirection = glm::vec2(1, 0)) {
    auto aberations = world.view<CameraAberation>();

    if (!aberations.empty()) {
        for (auto [_, aberation]: aberations) {
            aberation.distance = newDistance;
            aberation.duration = newDuration;
            aberation.direction = newAberationDirection;
            aberation.curTime = 0;
        }
    } else {
        auto curCameras = world.view<CameraEffect>(with<CurCamera>);

        for (auto [_, cameraEffect]: curCameras) {
            cameraEffect.canUseCameraAberation = true;
            cameraEffect.aberationDistance = newDistance;
            cameraEffect.aberationDuration = newDuration;
            cameraEffect.aberationDirection = newAberationDirection;
            // if (!world.has_components<CameraAberation>(curCameraEnt)) {
            //     world.add_components(curCameraEnt, CameraAberation(newDistance, newDuration));
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
        // if (!world.has_components<CameraShake>(entCam)) {
        //     if (auto parentOpt = world.get_parent(entCam)) {
        //         auto parentEnt = parentOpt.value();
        //         world.add_components(
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