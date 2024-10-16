#pragma once
#include <Zerengine.hpp>

class ShadowBossHubPattern final: public IComponent {
public:
    ShadowBossHubPattern(const std::initializer_list<glm::vec2>& newMovePoints):
        movePoints(newMovePoints),
        curPoint(0) {
    }

public:
    const std::vector<glm::vec2> movePoints;
    int curPoint;
};

class ShadowBoss final: public IComponent {
public:
    ShadowBoss(float new_move_duration, float new_pre_laser_duration, float new_laser_duration, float new_shadow_mark_duration, int new_nb_shadow_mark, float new_minion_pre_spawn_duration, float new_shadow_explosion_duration):
        move_duration(new_move_duration),
        pre_laser_duration(new_pre_laser_duration),
        laser_duration(new_laser_duration),
        shadow_mark_duration(new_shadow_mark_duration),
        nb_shadow_mark(new_nb_shadow_mark),
        minion_pre_spawn_duration(new_minion_pre_spawn_duration),
        shadow_explosion_duration(new_shadow_explosion_duration),
        last_state(10),
        last_shadow_rnd(10) {
    }

public:
    const float move_duration;
    const float pre_laser_duration;
    const float laser_duration;
    const float shadow_mark_duration;
    const int nb_shadow_mark;
    const float minion_pre_spawn_duration;
    const float shadow_explosion_duration;

    std::size_t last_state;
    std::size_t last_shadow_rnd;
};

class IsShadowBossMove final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossMove(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsShadowBossPreLaser final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossPreLaser(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsShadowBossLaser final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossLaser(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsShadowBossShadowMarkDuration final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossShadowMarkDuration(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsShadowBossShadowMarkInvocation final: public IComponent, public IIsTickDuration {
public:
    IsShadowBossShadowMarkInvocation(float new_tick_duration):
        IIsTickDuration(new_tick_duration) {
    }
};

class IsShadowBossMinionPreSpawn final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossMinionPreSpawn(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsShadowBossShadowExplosion final: public IComponent, public IIsStateDuration {
public:
    IsShadowBossShadowExplosion(float new_duration):
        IIsStateDuration(new_duration) {
    }
};