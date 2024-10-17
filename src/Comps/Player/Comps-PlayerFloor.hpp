#pragma once

#include <Zerengine.hpp>

class PlayerFloor final: public IComponent {
public:
    PlayerFloor(const std::initializer_list<std::size_t>& new_merchant_floors, const std::initializer_list<std::size_t>& new_final_boss_floors, std::size_t new_cur_floor = 0):
        cur_floor(new_cur_floor),
        merchant_floors(new_merchant_floors),
        final_boss_floors(new_final_boss_floors),
        can_load_merchant_room(false),
        can_load_final_boss_room(false) {
    }

public:
    std::size_t cur_floor;
    std::unordered_set<std::size_t> merchant_floors;
    std::unordered_set<std::size_t> final_boss_floors;
    bool can_load_merchant_room;
    bool can_load_final_boss_room;
};