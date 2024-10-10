#pragma once

#include <Zerengine.hpp>

class ChunkInfos final: public IComponent {
public:
    ChunkInfos(std::size_t newIdx):
        idx(newIdx) {
    }

    std::size_t getIdx() const {
        return idx;
    }

private:
    const std::size_t idx;
};

class ChunkTable final: public IComponent {
public:
    ChunkTable(int newWidth, int newHeight, const std::initializer_list<std::pair<const std::size_t, Ent>>& newList):
        chunks(newList),
        width(newWidth),
        height(newHeight) {
    }

    ChunkTable(int newWidth, int newHeight, const std::vector<std::pair<const std::size_t, Ent>>& newList):
        chunks(newList.begin(), newList.end()),
        width(newWidth),
        height(newHeight) {
    }

    [[nodiscard]] Ent getChunkById(std::size_t id) const noexcept {
        if (auto chunkIt = chunks.find(id); chunkIt != chunks.end()) {
            return chunkIt->second;
        }
        return 0;
    }

    [[nodiscard]] std::unordered_map<std::size_t, Ent>::const_iterator begin() const noexcept {
        return chunks.begin();
    }

    [[nodiscard]] std::unordered_map<std::size_t, Ent>::const_iterator end() const noexcept {
        return chunks.end();
    }

private:
    std::unordered_map<std::size_t, Ent> chunks;

public:
    const int width;
    const int height;
};

class ChunkExploration final: public IComponent {
public:
    enum RoomExplorationType: uint8_t {
        ROOM_EXPLORATION_EMPTY,
        ROOM_EXPLORATION_PLAYER,
        ROOM_EXPLORATION_UNKNOW,
        ROOM_EXPLORATION_KNOW
    };

public:
    ChunkExploration(int newWidth, int newHeight, const std::vector<std::vector<RoomExplorationType>>& newRoomTypes):
        roomTypes(newRoomTypes),
        width(newWidth),
        height(newHeight) {
    }

public:
    std::vector<std::vector<RoomExplorationType>> roomTypes;
    const int width;
    const int height;
};

class ChunkCameraMovement final: public IComponent {
public:
    ChunkCameraMovement(Ent newOldRoomEnt, Ent newNextRoomEnt, float newCameraSpeed):
        oldRoomEnt(newOldRoomEnt),
        nextRoomEnt(newNextRoomEnt),
        cameraSpeed(newCameraSpeed) {
    }

    Ent getOldRoomEnt() const {
        return oldRoomEnt;
    }

    Ent getNextRoomEnt() const {
        return nextRoomEnt;
    }

    float getCameraSpeed() const {
        return cameraSpeed;
    }

private:
    const Ent oldRoomEnt;
    const Ent nextRoomEnt;
    const float cameraSpeed;
};