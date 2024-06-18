#pragma once

class IIsStateDuration {
protected:
    [[nodiscard]] constexpr IIsStateDuration(float newDuration) noexcept:
        duration(newDuration) {
    }

public:
    [[nodiscard]] constexpr bool canSwitchState(float delta) noexcept {
        duration -= delta;
        return duration <= 0;
    }

private:
    float duration;
};