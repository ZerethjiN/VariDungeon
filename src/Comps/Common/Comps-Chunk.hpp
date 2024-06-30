#pragma once

#include <Zerengine.hpp>

class ChunkInfos {
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

class ChunkTable {
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
    const int width;
    const int height;
};

class ChunkCameraMovement {
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