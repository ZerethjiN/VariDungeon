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

class Transform {
friend void collisionSys(World&);
friend void updateVelocityRec(World&, Ent, const glm::vec2&);
friend void updateVelocitySys(World&);
friend void updatePositionSys(World&);
public:
    Transform() noexcept:
        position(0, 0),
        m_scale(1, 1),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0),
        needUpdatePosition(false) {
    }

    Transform(const glm::vec2& newPosition, float newRotation, const glm::vec2& newScale) noexcept:
        position(newPosition),
        m_scale(newScale),
        rotation(0),
        isDirty(true),
        hashMapUpdated(true),
        diffPosition(0, 0),
        needUpdatePosition(false) {
        setRotation(newRotation);
    }

public:
    void setPosition(const glm::vec2& newPosition) noexcept {
        diffPosition += newPosition - position;
        position = newPosition;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void setPosition(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y) - position;
        position = glm::vec2(x, y);
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(const glm::vec2& newOffset) noexcept {
        diffPosition += newOffset;
        position += newOffset;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveX(float x) noexcept {
        diffPosition += glm::vec2(x, 0);
        position.x += x;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void moveY(float y) noexcept {
        diffPosition += glm::vec2(0, y);
        position.y += y;
        needUpdatePosition = true;
        isDirty = true;
        hashMapUpdated = true;
    }

    void move(float x, float y) noexcept {
        diffPosition += glm::vec2(x, y);
        position += glm::vec2(x, y);
        needUpdatePosition = true;
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

    const float* getPtr() noexcept {
        return glm::value_ptr(getModel());
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
};

///////////////////////////////////////////////////////////////////////////////////

class Time {
public:
    Time(float newFixedTimeStep = 0.02) noexcept:
        t2(std::chrono::high_resolution_clock::now()),
        fixedTimeStep(newFixedTimeStep) {
    }

    void update() noexcept {
        auto t1 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::duration<float>>(t1 - t2).count();
        t2 = t1;
        timeScale = newTimeScale;
        #ifdef DISPLAY_FPS
            frameCounter();
        #endif
        timeStepBuffer += dt;
        isTimeStepFrame = false;
        if (timeStepBuffer >= fixedTimeStep) {
            isTimeStepFrame = true;
            timeStepBuffer -= fixedTimeStep;
        }
    }

    [[nodiscard]] constexpr float delta() const noexcept {
        return dt * timeScale;
    }

    [[nodiscard]] constexpr float unscaledDelta() const noexcept {
        return dt;
    }

    [[nodiscard]] constexpr float unscaledFixedDelta() const noexcept {
        return fixedTimeStep;
    }

    [[nodiscard]] constexpr float fixedDelta() const noexcept {
        return fixedTimeStep * timeScale;
    }

    [[nodiscard]] constexpr bool isTimeStep() const noexcept {
        return isTimeStepFrame;
    }

     constexpr float getTimeScale() const noexcept {
        return newTimeScale;
    }

    constexpr void setTimeScale(const float newScale) noexcept {
        newTimeScale = newScale;
    }

private:
    #ifdef DISPLAY_FPS
        void frameCounter() noexcept {
            nbFrames++;
            timer += dt;
            if (timer >= FRAME_COOLDOWN) {
                printf("FPS: %zu\n", nbFrames);
                timer -= FRAME_COOLDOWN;
                nbFrames = 0;
            }
        }
    #endif

private:
    float newTimeScale = 1.0;
    float timeScale = 1.0;

private:
    double dt = 0;
    std::chrono::high_resolution_clock::time_point t2;
    bool isTimeStepFrame = false;
    float fixedTimeStep;
    float timeStepBuffer = 0;

    #ifdef DISPLAY_FPS
        float timer = 0;
        size_t nbFrames = 0;
        constexpr static float FRAME_COOLDOWN = 1.0;
    #endif
};

///////////////////////////////////////////////////////////////////////////////////

void updateTimeSys(World& world) noexcept {
    auto [time] = world.getRes<Time>();
    time.update();
}

///////////////////////////////////////////////////////////////////////////////////

class AppState {
public:
    [[nodiscard]] constexpr AppState(const std::uint8_t newState) noexcept:
        state(newState) {
    }

    constexpr AppState& operator=(const std::uint8_t newState) noexcept {
        state = newState;
        return *this;
    }

    [[nodiscard]] constexpr operator std::uint8_t&() noexcept {
        return state;
    }

public:
    std::uint8_t state;
};

///////////////////////////////////////////////////////////////////////////////////

class LifeTime {
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

void lifeTimeSys(World& world) {
    auto [time] = world.getRes<const Time>();

    for (auto [ent, lifeTime]: world.view<LifeTime>()) {
        if (lifeTime.isEndDuration(time.fixedDelta())) {
            world.destroy(ent);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

class Speed {
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

class Velocity {
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