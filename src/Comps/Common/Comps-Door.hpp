#pragma once

#include <Zerengine.hpp>

class DoorTrigger final: public IComponent {
public:
    enum DoorTriggerOrientation: uint8_t {
        DOOR_TRIGGER_NORTH,
        DOOR_TRIGGER_SOUTH,
        DOOR_TRIGGER_EAST,
        DOOR_TRIGGER_WEST
    };

public:
    DoorTrigger(const glm::ivec2 newCurRoomXY, const glm::ivec2 newNextRoomXY, std::size_t newNextRoomIdx, DoorTriggerOrientation newOrientation):
        curRoomXY(newCurRoomXY),
        nextRoomXY(newNextRoomXY),
        nextRoomIdx(newNextRoomIdx),
        orientation(newOrientation) {
    }

    std::size_t getNextRoomIdx() const {
        return nextRoomIdx;
    }

    DoorTriggerOrientation getOrientation() const {
        return orientation;
    }

public:
    const glm::ivec2 curRoomXY;
    const glm::ivec2 nextRoomXY;

private:
    const std::size_t nextRoomIdx;
    const DoorTriggerOrientation orientation;
};

class IsDoorLock final: public IComponent {};
class IsDoorWithKey final: public IComponent {};