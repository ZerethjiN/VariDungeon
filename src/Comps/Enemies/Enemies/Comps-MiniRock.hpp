#pragma once

#include <Zerengine.hpp>

class MiniRockSpawner final {
public:
    MiniRockSpawner(float newCooldown, int newNbMiniRock):
        nbMiniRock(newNbMiniRock),
        cooldown(newCooldown),
        curTime(0) {
    }

    bool canSpawn(float delta) {
        curTime += delta;
        if (curTime >= cooldown) {
            curTime -= cooldown;
            return true;
        }
        return false;
    }

public:
    const int nbMiniRock;

private:
    const float cooldown;
    float curTime;
};

class MiniRock final {};