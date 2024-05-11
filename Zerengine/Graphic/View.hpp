#pragma once

#include <glm/glm.hpp>

class ZreView {
public:
    ZreView(const glm::vec4& rect) {
        reset(rect);
    }

public:
    void reset(const glm::vec4& rect) {
        center = glm::vec2(rect.x, rect.y);
        size = glm::vec2(rect.z, rect.w);
        needRefreshTransform = true;
    }

    void setSize(float x, float y) {
        size = glm::vec2(x, y);
        needRefreshTransform = true;
    }

    void setCenter(const glm::vec2& newCenter) {
        center = newCenter;
        needRefreshTransform = true;
    }

    const glm::vec2& getSize() const noexcept {
        return size;
    }

    const glm::vec2& getCenter() const noexcept {
        return center;
    }

    const glm::mat4& getModel() {
        if (needRefreshTransform) {
            model = glm::ortho(center.x - size.x / 2, center.x + size.x / 2, center.y - size.y / 2, center.y + size.y / 2);

            needRefreshTransform = false;
        }
        return model;
    }

private:
    glm::vec2 center;
    glm::vec2 size;
    glm::mat4 model;
    bool needRefreshTransform;
};