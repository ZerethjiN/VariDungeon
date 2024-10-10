#pragma once

#include <Zerengine.hpp>

class BossHealthBar final: public IComponent  {};
class BossHealthBarInner final: public IComponent {
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
class BossHealthBarText final: public IComponent {};