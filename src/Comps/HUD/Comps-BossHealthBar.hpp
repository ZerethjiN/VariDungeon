#pragma once

#include <Zerengine.hpp>

class BossHealthBar {};
class BossHealthBarInner {
public:
    BossHealthBarInner(std::size_t newMaxPixelSize):
        maxPixelSize(newMaxPixelSize) {
    }

    std::size_t getMaxPixelSize() const {
        return maxPixelSize;
    }

private:
    const std::size_t maxPixelSize;
};
class BossHealthBarText {};