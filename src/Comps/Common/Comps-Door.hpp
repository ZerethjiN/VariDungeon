#pragma once

#include <Zerengine.hpp>

class DoorTrigger final {
public:
    enum DoorTriggerOrientation: uint8_t {
        DOOR_TRIGGER_NORTH,
        DOOR_TRIGGER_SOUTH,
        DOOR_TRIGGER_EAST,
        DOOR_TRIGGER_WEST
    };

public:
    DoorTrigger(std::size_t newNextRoomIdx, DoorTriggerOrientation newOrientation):
        nextRoomIdx(newNextRoomIdx),
        orientation(newOrientation) {
    }

    std::size_t getNextRoomIdx() const {
        return nextRoomIdx;
    }

    DoorTriggerOrientation getOrientation() const {
        return orientation;
    }

private:
    const std::size_t nextRoomIdx;
    const DoorTriggerOrientation orientation;
};

class IsDoorLock final {};