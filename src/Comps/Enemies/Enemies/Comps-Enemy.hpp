#pragma once

#include <Zerengine.hpp>

class Enemy final: public IComponent {};
class Boss final: public IComponent {};
class EnemyWeapon final: public IComponent {};
class EnemyWeaponForBreakables final: public IComponent {};

class OnEnemyDeath final: public IComponent {
public:
    OnEnemyDeath(std::function<void(World&, const Ent&)> new_callback):
        callback(new_callback) {
    }

public:
    std::function<void(World&, const Ent&)> callback;
};