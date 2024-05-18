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

void cameraShakeRightSys(World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform>(with<CurCamera, CameraShakeRight>);

    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        transform.moveX(camShake.speed * time.fixedDelta());
        if (auto opt = world.get<const Transform>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x >= originTransform.getPosition().x + camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.del<CameraShake, CameraShakeRight>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.del<CameraShakeRight>(entCam);
                    world.add(entCam, CameraShakeLeft());
                }
            }
        }
    }
}

void cameraShakeLeftSys(World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform>(with<CurCamera, CameraShakeLeft>);
    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        transform.moveX(-camShake.speed * time.fixedDelta());
        if (auto opt = world.get<const Transform>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x <= originTransform.getPosition().x - camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.del<CameraShake, CameraShakeLeft>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.del<CameraShakeLeft>(entCam);
                    world.add(entCam, CameraShakeRight());
                }
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