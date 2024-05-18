#pragma once

#include <Zerengine.hpp>

class Player {};
class PlayerWeapon {};
class PlayerAttractor {};

class PlayerDamage {
public:
    PlayerDamage(float newCurDamage):
        curDamage(newCurDamage) {
    }

    PlayerDamage& operator +=(float newDamage) {
        curDamage += newDamage;
        return *this;
    }

    PlayerDamage& operator -=(float newDamage) {
        curDamage -= newDamage;
        return *this;
    }

    PlayerDamage& operator *=(float newDamage) {
        curDamage *= newDamage;
        return *this;
    }

    PlayerDamage& operator /=(float newDamage) {
        curDamage /= newDamage;
        return *this;
    }

    operator float() const {
        return curDamage;
    }

    float getDamage() const {
        return curDamage;
    }

private:
    float curDamage;
};