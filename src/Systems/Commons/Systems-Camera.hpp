#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void cameraEffectApplicationSys(MainFixedSystem, World& world) {
    auto cameras = world.query<CameraEffect>(with<CurCamera>);

    for (auto [curCameraEnt, cameraEffect]: cameras) {
        if (cameraEffect.canUseCameraAberation) {
            cameraEffect.canUseCameraAberation = false;
            if (!world.has_components<CameraAberation>(curCameraEnt)) {
                world.add_components(curCameraEnt, CameraAberation(cameraEffect.aberationDistance, cameraEffect.aberationDuration, cameraEffect.aberationDirection));
            }
        }

        if (cameraEffect.canUseCameraShake) {
            cameraEffect.canUseCameraShake = false;
            if (!world.has_components<CameraShake>(curCameraEnt)) {
                if (auto parentOpt = world.get_parent(curCameraEnt)) {
                    auto parentEnt = parentOpt.value();
                    world.add_components(
                        curCameraEnt,
                        CameraShake(
                            /*OriginEnt:*/ parentEnt,
                            /*Distance:*/ cameraEffect.shakeDistance,
                            /*Speed:*/ cameraEffect.shakeSpeed,
                            /*NbShake:*/ cameraEffect.nbShake
                        ),
                        CameraShakeLeft()
                    );
                }
            }
        }
    }
}

void cameraSys(MainFixedSystem, World& world) {
    auto cameras = world.query<const Transform2D>(with<CurCamera>);

    auto [inGameView, uiView] = world.resource<InGameView, UIView>();

    for (auto [_, trans]: cameras) {
        const auto& windowSize = vulkanEngine.window.getSize();

        if (160.f / static_cast<float>(windowSize.y) * (static_cast<float>(windowSize.x)) > 160.f) {
            inGameView.setSize(160.f / static_cast<float>(windowSize.y) * static_cast<float>(windowSize.x), 144.f);
        } else {
            inGameView.setSize(160.f, 144.f / static_cast<float>(windowSize.x) * static_cast<float>(windowSize.y));
        }
        inGameView.setCenter(trans.getPosition());

        if (160.f / static_cast<float>(windowSize.y) * (static_cast<float>(windowSize.x)) > 160.f) {
            uiView.setSize(160.f / static_cast<float>(windowSize.y) * static_cast<float>(windowSize.x), 144.f);
        } else {
            uiView.setSize(160.f, 144.f / static_cast<float>(windowSize.x) * static_cast<float>(windowSize.y));
        }
    }
}