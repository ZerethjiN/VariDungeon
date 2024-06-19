#pragma once

class IIsStateDuration {
protected:
    [[nodiscard]] constexpr IIsStateDuration(float newDuration) noexcept:
        duration(newDuration),
        curTime(0) {
    }

public:
    [[nodiscard]] constexpr bool canSwitchState(float delta) noexcept {
        curTime += delta;
        return curTime >= duration;
    }

    constexpr void resetStateTimer() noexcept {
        curTime = 0;
    }

private:
    const float duration;
    float curTime;
};