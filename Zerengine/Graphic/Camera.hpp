#pragma once

class Camera {};
class CurCamera {};

class CameraShake {
public:
    CameraShake(Ent newOriginEnt, float newDistance, float newSpeed, int newNbShake):
        originEnt(newOriginEnt),
        distance(newDistance),
        speed(newSpeed),
        nbShake(newNbShake),
        curShake(0) {
    }

public:
    const Ent originEnt;
    const float distance;
    const float speed;
    const int nbShake;
    int curShake;
};

class CameraShakeLeft {};
class CameraShakeRight {};

void cameraShakeRightSys(MainFixedSystem, World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform>(with<CurCamera, CameraShakeRight>);

    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        if (auto opt = world.get<const Transform>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x >= originTransform.getPosition().x + camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.remove<CameraShake, CameraShakeRight>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.remove<CameraShakeRight>(entCam);
                    world.add(entCam, CameraShakeLeft());
                }
            } else {
                transform.moveX(camShake.speed * time.fixedDelta());
            }
        }
    }
}

void cameraShakeLeftSys(MainFixedSystem, World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform>(with<CurCamera, CameraShakeLeft>);
    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        if (auto opt = world.get<const Transform>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x <= originTransform.getPosition().x - camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.remove<CameraShake, CameraShakeLeft>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.remove<CameraShakeLeft>(entCam);
                    world.add(entCam, CameraShakeRight());
                }
            } else {
                transform.moveX(-camShake.speed * time.fixedDelta());
            }
        }
    }
}

void appliedCameraShake(World& world, float distance, float speed, unsigned int nbShake) {
    auto cameras = world.view(with<CurCamera>, without<CameraShake>);

    for (auto [entCam]: cameras) {
        if (!world.has<CameraShake>(entCam)) {
            if (auto parentOpt = world.getParent(entCam)) {
                auto parentEnt = parentOpt.value();
                world.add(
                    entCam,
                    CameraShake(
                        /*OriginEnt:*/ parentEnt,
                        /*Distance:*/ distance,
                        /*Speed:*/ speed,
                        /*NbShake:*/ nbShake
                    ),
                    CameraShakeLeft()
                );
            }
        }
    }
}