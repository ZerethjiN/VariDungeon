#pragma once

#include "../ZerengineCore.hpp"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////////

class Transform2D final: public IComponent {
friend void collisionSys(LateFixedSystem, World&);
friend void updateVelocityRec(World&, Ent, const glm::vec2&);
friend void updateVelocitySys(LateFixedSystem, World&);
friend void updatePositionSys(LateUnscaledFixedSystem, World&);
public:
    Transform2D() noexcept:
        model(1),
        position(0, 0),
        m_scale(1, 1),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0),
        needUpdatePosition(false),
        needUpdatePositionGlobal(false) {
    }

    Transform2D(const glm::vec2& newPosition, float newRotation, const glm::vec2& newScale) noexcept:
        model(1),
        position(newPosition),
        m_scale(newScale),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0),
        needUpdatePosition(false),
        needUpdatePositionGlobal(false) {
        setRotation(newRotation);
    }

public:
    void setPosition(const glm::vec2& newPosition) noexcept {
        diffPosition += newPosition - position;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPositionGlobal(const glm::vec2& newPosition) noexcept {
        diffPosition += newPosition - position;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPosition(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y) - position;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPositionGlobal(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y) - position;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(const glm::vec2& newOffset) noexcept {
        diffPosition += newOffset;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveGlobal(const glm::vec2& newOffset) noexcept {
        diffPosition += newOffset;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveX(float x) noexcept {
        diffPosition += glm::vec2(x, 0);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveXGlobal(float x) noexcept {
        diffPosition += glm::vec2(x, 0);
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveY(float y) noexcept {
        diffPosition += glm::vec2(0, y);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveYGlobal(float y) noexcept {
        diffPosition += glm::vec2(0, y);
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveGlobal(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y);
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

private:
    void moveVelocity(const glm::vec2& newOffset) noexcept {
        position += newOffset;
        isDirty = true;
        hashMapUpdated = true;
    }

public:
    const glm::vec2& getPosition() const noexcept {
        return position;
    }

public:
    void setRotation(float angle) noexcept {
        const float val = angle - static_cast<float>(static_cast<int>(angle / 360)) * 360;
        if (val >= 0.0f)
            rotation = val;
        else
            rotation = val + 360;
        isDirty = true;
        hashMapUpdated = true;
    }

    void rotate(float offsetAngle) noexcept {
        rotation += offsetAngle;
        isDirty = true;
        hashMapUpdated = true;
        const float val = rotation - static_cast<float>(static_cast<int>(rotation / 360)) * 360;
        if (val >= 0.0f)
            rotation =  val;
        else
            rotation = val + 360;   
    }

    float getRotation() const noexcept {
        return rotation;
    }

public:
    void setScale(const glm::vec2& newScale) noexcept {
        m_scale = newScale;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScale(float x, float y) noexcept {
        m_scale = glm::vec2(x, y);
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScaleX(float x) noexcept {
        m_scale.x = x;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScaleY(float y) noexcept {
        m_scale.y = y;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scale(const glm::vec2& newOffset) noexcept {
        m_scale += newOffset;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scale(float x, float y) noexcept {
        m_scale += glm::vec2(x, y);
        isDirty = true;
        hashMapUpdated = true;
    }

    void scaleX(float x) noexcept {
        m_scale.x += x;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scaleY(float y) noexcept {
        m_scale.y += y;
        isDirty = true;
        hashMapUpdated = true;
    }

    const glm::vec2& getScale() const noexcept {
        return m_scale;
    }

public:
    const glm::mat4& getModel() noexcept {
        if (isDirty) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, 0));
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
            model = glm::scale(model, glm::vec3(m_scale, 0));
            isDirty = false;
        }
        return model;
    }

private:
    glm::mat4 model;
    glm::vec2 position;
    glm::vec2 m_scale;
    float rotation;
    bool isDirty;
    bool hashMapUpdated;

    glm::vec2 diffPosition;
    bool needUpdatePosition;
    bool needUpdatePositionGlobal;
};

///////////////////////////////////////////////////////////////////////////////////

class Transform3D final: public IComponent {
friend void collisionSys(LateFixedSystem, World&);
friend void updateVelocityRec(World&, Ent, const glm::vec2&);
friend void updateVelocitySys(LateFixedSystem, World&);
friend void updatePositionSys(LateUnscaledFixedSystem, World&);
public:
    Transform3D() noexcept:
        position(0, 0, 0),
        m_scale(1, 1, 1),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0, 0),
        needUpdatePosition(false) {
    }

    Transform3D(const glm::vec3& newPosition, float newRotation, const glm::vec3& newScale) noexcept:
        position(newPosition),
        m_scale(newScale),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0, 0),
        needUpdatePosition(false) {
        setRotation(newRotation);
    }

public:
    void setPosition(const glm::vec3& newPosition) noexcept {
        diffPosition += newPosition - position;
        // position = newPosition;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPositionGlobal(const glm::vec3& newPosition) noexcept {
        diffPosition += newPosition - position;
        // position = newPosition;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPosition(float x, float y, float z) noexcept {
        diffPosition += glm::vec3(x, y, z) - position;
        // position = glm::vec2(x, y);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPositionGlobal(float x, float y, float z) noexcept {
        diffPosition += glm::vec3(x, y, z) - position;
        // position = glm::vec2(x, y);
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(const glm::vec3& newOffset) noexcept {
        diffPosition += newOffset;
        // position += newOffset;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveGlobal(const glm::vec3& newOffset) noexcept {
        diffPosition += newOffset;
        // position += newOffset;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveX(float x) noexcept {
        diffPosition += glm::vec3(x, 0, 0);
        // position.x += x;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveXGlobal(float x) noexcept {
        diffPosition += glm::vec3(x, 0, 0);
        // position.x += x;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveY(float y) noexcept {
        diffPosition += glm::vec3(0, y, 0);
        // position.y += y;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveYGlobal(float y) noexcept {
        diffPosition += glm::vec3(0, y, 0);
        // position.y += y;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveZ(float z) noexcept {
        diffPosition += glm::vec3(0, 0, z);
        // position.y += y;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveZGlobal(float z) noexcept {
        diffPosition += glm::vec3(0, 0, z);
        // position.y += y;
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(float x, float y, float z) noexcept {
        diffPosition += glm::vec3(x, y, z);
        // position += glm::vec2(x, y);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveGlobal(float x, float y, float z) noexcept {
        diffPosition += glm::vec3(x, y, z);
        // position += glm::vec2(x, y);
        needUpdatePositionGlobal = true;
        isDirty = true;
        hashMapUpdated = true;
    }

private:
    void moveVelocity(const glm::vec3& newOffset) noexcept {
        position += newOffset;
        isDirty = true;
        hashMapUpdated = true;
    }

public:
    const glm::vec3& getPosition() const noexcept {
        return position;
    }

public:
    void setRotation(float angle) noexcept {
        const float val = angle - static_cast<float>(static_cast<int>(angle / 360)) * 360;
        if (val >= 0.0f)
            rotation = val;
        else
            rotation = val + 360;
        isDirty = true;
        hashMapUpdated = true;
    }

    void rotate(float offsetAngle) noexcept {
        rotation += offsetAngle;
        isDirty = true;
        hashMapUpdated = true;
        const float val = rotation - static_cast<float>(static_cast<int>(rotation / 360)) * 360;
        if (val >= 0.0f)
            rotation =  val;
        else
            rotation = val + 360;   
    }

    float getRotation() const noexcept {
        return rotation;
    }

public:
    void setScale(const glm::vec3& newScale) noexcept {
        m_scale = newScale;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScale(float x, float y, float z) noexcept {
        m_scale = glm::vec3(x, y, z);
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScaleX(float x) noexcept {
        m_scale.x = x;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScaleY(float y) noexcept {
        m_scale.y = y;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setScaleZ(float z) noexcept {
        m_scale.z = z;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scale(const glm::vec3& newOffset) noexcept {
        m_scale += newOffset;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scale(float x, float y, float z) noexcept {
        m_scale += glm::vec3(x, y, z);
        isDirty = true;
        hashMapUpdated = true;
    }

    void scaleX(float x) noexcept {
        m_scale.x += x;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scaleY(float y) noexcept {
        m_scale.y += y;
        isDirty = true;
        hashMapUpdated = true;
    }

    void scaleZ(float z) noexcept {
        m_scale.z += z;
        isDirty = true;
        hashMapUpdated = true;
    }

    const glm::vec3& getScale() const noexcept {
        return m_scale;
    }

public:
    const glm::mat4& getModel() noexcept {
        if (isDirty) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
            model = glm::scale(model, m_scale);
            isDirty = false;
        }
        return model;
    }

private:
    glm::mat4 model;
    glm::vec3 position;
    glm::vec3 m_scale;
    float rotation;
    bool isDirty;
    bool hashMapUpdated;

    glm::vec3 diffPosition;
    bool needUpdatePosition;
    bool needUpdatePositionGlobal;
};

///////////////////////////////////////////////////////////////////////////////////

class AppState final: public IResource {
public:
    template <typename E> requires (std::is_enum_v<E> && std::is_scoped_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t>)
    [[nodiscard]] constexpr AppState(const E& newState) noexcept:
        state(static_cast<std::size_t>(newState)) {
    }

    template <typename E> requires (std::is_enum_v<E> && std::is_scoped_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t>)
    constexpr AppState& operator=(const E& newState) noexcept {
        state = static_cast<std::size_t>(newState);
        return *this;
    }

    [[nodiscard]] constexpr operator std::size_t&() noexcept {
        return state;
    }

    template <typename E> requires (std::is_enum_v<E> && std::is_scoped_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t>)
    [[nodiscard]] constexpr bool operator==(const E& othState) const noexcept {
        return state == static_cast<std::size_t>(othState);
    }

private:
    std::size_t state;
};

///////////////////////////////////////////////////////////////////////////////////

class LifeTime final: public IComponent {
public:
    LifeTime(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool isEndDuration(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    void changeDuration(float newDuration) {
        duration = newDuration;
        curTime = 0;
    }

private:
    float duration;
    float curTime;
};

void lifeTimeSys(MainFixedSystem, World& world) {
    auto [time] = world.resource<const Time>();

    for (auto [ent, lifeTime]: world.query<LifeTime>()) {
        if (lifeTime.isEndDuration(time.fixedDelta())) {
            world.delete_entity(ent);
        }
    }
}

class UnscaledLifeTime final: public IComponent {
public:
    UnscaledLifeTime(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool isEndDuration(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    void changeDuration(float newDuration) {
        duration = newDuration;
        curTime = 0;
    }

private:
    float duration;
    float curTime;
};

void unscaledLifeTimeSys(MainUnscaledFixedSystem, World& world) {
    auto [time] = world.resource<const Time>();

    for (auto [ent, lifeTime]: world.query<UnscaledLifeTime>()) {
        if (lifeTime.isEndDuration(time.unscaledFixedDelta())) {
            world.delete_entity(ent);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

class Speed final: public IComponent {
public:
    Speed(float newSpeed):
        speed(newSpeed) {
    }

    operator float() const noexcept {
        return speed;
    }

    Speed& operator =(float newSpeed) noexcept {
        speed = newSpeed;
        return *this;
    }

public:
    float speed;
};

///////////////////////////////////////////////////////////////////////////////////

class Velocity final: public IComponent {
public:
    operator glm::vec2&() {
        return vel;
    }

    operator const glm::vec2&() const noexcept {
        return vel;
    }

    [[nodiscard]] bool operator ==(const glm::vec2& oth) const noexcept {
        return vel == oth;
    }

    [[nodiscard]] bool operator !=(const glm::vec2& oth) const noexcept {
        return vel != oth;
    }

    Velocity& operator +=(const glm::vec2& value) noexcept {
        vel += value;
        return *this;
    }

    Velocity& operator -=(const glm::vec2& value) noexcept {
        vel -= value;
        return *this;
    }

    Velocity& operator +=(float value) noexcept {
        vel += value;
        return *this;
    }

    Velocity& operator -=(float value) noexcept {
        vel -= value;
        return *this;
    }

    Velocity& operator =(const glm::vec2& value) noexcept {
        vel = value;
        return *this;
    }

public:
    union {
        glm::vec2 vel;
        struct {
            float x, y;
        };
    };
};

///////////////////////////////////////////////////////////////////////////////////