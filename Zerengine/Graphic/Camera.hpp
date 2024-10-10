#pragma once

class Camera final: public IComponent {};
class CurCamera final: public IComponent {};

class CameraShake final: public IComponent {
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

class CameraShakeLeft final: public IComponent {};
class CameraShakeRight final: public IComponent {};

void cameraShakeRightSys(ThreadedFixedSystem, World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform2D>(with<CurCamera, CameraShakeRight>, without<CameraShakeLeft>);

    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        if (auto opt = world.get_components<const Transform2D>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x >= originTransform.getPosition().x + camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.remove_components<CameraShake, CameraShakeRight>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.remove_components<CameraShakeRight>(entCam);
                    world.add_components(entCam, CameraShakeLeft());
                }
            } else {
                transform.moveX(camShake.speed * time.fixedDelta());
            }
        }
    }
}

void cameraShakeLeftSys(ThreadedFixedSystem, World& world) noexcept {
    auto cameras = world.view<CameraShake, Transform2D>(with<CurCamera, CameraShakeLeft>, without<CameraShakeRight>);
    auto [time] = world.resource<const Time>();

    for (auto [entCam, camShake, transform]: cameras) {
        if (auto opt = world.get_components<const Transform2D>(camShake.originEnt)) {
            auto [originTransform] = opt.value();
            if (transform.getPosition().x <= originTransform.getPosition().x - camShake.distance) {
                camShake.curShake++;
                if (camShake.curShake >= camShake.nbShake) {
                    world.remove_components<CameraShake, CameraShakeLeft>(entCam);
                    transform.setPosition(originTransform.getPosition());
                } else {
                    world.remove_components<CameraShakeLeft>(entCam);
                    world.add_components(entCam, CameraShakeRight());
                }
            } else {
                transform.moveX(-camShake.speed * time.fixedDelta());
            }
        }
    }
}