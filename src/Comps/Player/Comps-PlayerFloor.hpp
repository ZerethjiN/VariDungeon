#pragma once

#include <Zerengine.hpp>

class PlayerFloor final: public IComponent {
public:
    PlayerFloor(const std::initializer_list<std::size_t>& newMerchantFloors, std::size_t newCurFloor = 0):
        curFloor(newCurFloor),
        merchantFloors(newMerchantFloors),
        canLoadMerchantRoom(false) {
    }

public:
    std::size_t curFloor;
    std::unordered_set<std::size_t> merchantFloors;
    bool canLoadMerchantRoom;
};