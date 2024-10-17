#pragma once

#include <Zerengine.hpp>

class Unmoveable final: public IComponent {};

class UnmoveableTimer final: public IComponent {
public:
    UnmoveableTimer(float new_duration):
        cur_time(new_duration) {
    }

    bool can_stop_unmove(float delta) {
        cur_time -= delta;
        return cur_time < 0;
    }

private:
    float cur_time;
};