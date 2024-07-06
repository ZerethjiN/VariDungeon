#pragma once

#include <Zerengine.hpp>

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
        auto curCameras = world.view(with<CurCamera>);

        for (auto [curCameraEnt]: curCameras) {
            if (!world.hasThisFrame<CameraAberation>(curCameraEnt)) {
                world.add(curCameraEnt, CameraAberation(newDistance, newDuration));
            }
        }
    }
}