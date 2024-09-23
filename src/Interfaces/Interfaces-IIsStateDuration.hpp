#pragma once

class IIsStateDuration {
protected:
    [[nodiscard]] constexpr IIsStateDuration(float newDuration) noexcept:
        curTime(newDuration) {
    }

public:
    [[nodiscard]] constexpr bool canSwitchState(float delta) noexcept {
        curTime -= delta;
        return curTime <= 0;
    }

private:
    float curTime;
};