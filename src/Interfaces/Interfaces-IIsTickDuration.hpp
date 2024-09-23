#pragma once

class IIsTickDuration {
protected:
    [[nodiscard]] constexpr IIsTickDuration(float newDuration) noexcept:
        duration(newDuration),
        curTime(0) {
    }

public:
    [[nodiscard]] constexpr bool canTick(float delta) noexcept {
        curTime += delta;
        if (curTime >= duration) {
            curTime -= duration;
            return true;
        }
        return false;
    }

    constexpr void changeTickDuration(float newDuration) noexcept {
        curTime = 0;
        duration = newDuration;
    }

    constexpr void resetTick() noexcept {
        curTime = 0;
    }

private:
    float duration;
    float curTime;
};