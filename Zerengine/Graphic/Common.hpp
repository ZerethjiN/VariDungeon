#pragma once

#include <glm/glm.hpp>

class Color {
public:
    [[nodiscard]] Color() noexcept = default;

    [[nodiscard]] Color(const Color& oth):
        color(oth.color) {
    }

    [[nodiscard]] Color(float r, float g, float b, float a) noexcept:
        color(r, g, b, a) {
    }

public:
    Color& operator +=(const auto& oth) noexcept {
        color += oth;
        return *this;
    }

    Color& operator -=(const auto& oth) noexcept {
        color -= oth;
        return *this;
    }

    Color& operator *=(const auto& oth) noexcept {
        color *= oth;
        return *this;
    }

    Color& operator /=(const auto& oth) noexcept {
        color /= oth;
        return *this;
    }

    Color operator +(const auto& oth) const noexcept {
        auto res = color + oth;
        return {res.x, res.y, res.z, res.w};
    }

    Color operator -(const auto& oth) const noexcept {
        auto res = color - oth;
        return {res.x, res.y, res.z, res.w};
    }

    Color operator *(const auto& oth) const noexcept {
        auto res = color * oth;
        return {res.x, res.y, res.z, res.w};
    }

    Color operator /(const auto& oth) const noexcept {
        auto res = color / oth;
        return {res.x, res.y, res.z, res.w};
    }

    operator glm::vec4&() noexcept {
        return color;
    }

    operator const glm::vec4&() const noexcept {
        return color;
    }

public:
    union {
        struct {
            float r, g, b, a;
        };
        glm::vec4 color;
    };
};