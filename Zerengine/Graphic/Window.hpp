#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "View.hpp"

class Window final {
public:
    Window(const glm::uvec2& newSize, const std::string& newTitle):
        size(newSize),
        title(newTitle) {
        create();
    }

    ~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

public:
    void setCursorHidden(bool val) noexcept {
        if (val)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool isOpen() const noexcept {
        return !glfwWindowShouldClose(window);
    }

    void close() const noexcept {
        glfwSetWindowShouldClose(window, true);
    }

    [[nodiscard]] glm::vec2 mapPixelToCoords(const ZreView& newView, const glm::vec2& point) const noexcept {
        const glm::vec3 newPoint = glm::project(
            glm::vec3(point, 0),
            glm::mat4(1.0f),
            glm::ortho(0.f, static_cast<float>(size.x), 0.f, static_cast<float>(size.y)),
            glm::vec4(-(newView.getSize().x / 2.f) + newView.getCenter().x, -(newView.getSize().y / 2.f) + newView.getCenter().y, newView.getSize().x, newView.getSize().y)
        );

        return {newPoint.x, newPoint.y};
    }

    [[nodiscard]] glm::vec2 mapCoordsToPixel(const ZreView& newView, const glm::vec2& point) const noexcept {
        const glm::vec3 newPoint = glm::unProject(
            glm::vec3(point, 0),
            glm::mat4(1.0f),
            glm::ortho(0.f, static_cast<float>(size.x), 0.f, static_cast<float>(size.y)),
            glm::vec4(-(newView.getSize().x / 2.f) + newView.getCenter().x, -(newView.getSize().y / 2.f) + newView.getCenter().y, newView.getSize().x, newView.getSize().y)
        );

        return {newPoint.x, newPoint.y};
    }

    glm::vec2 getCursorPos() const {
        double posX, posY;
        glfwGetCursorPos(window, &posX, &posY);
        return glm::vec2(posX, posY);
    }

    void pollEvents() noexcept {
        glfwPollEvents();

        // Button Input
        buttonDownOld.swap(buttonDown);
        buttonHoldOld.swap(buttonHold);

        buttonDown.clear();
        buttonHold.clear();
        buttonUp.clear();

        for (const auto& pair: buttonNameBinds) {
            for (const auto keyCode: pair.second) {
                if (glfwGetKey(window, keyCode) == GLFW_PRESS) {
                    if (!buttonDownOld.contains(keyCode) && !buttonHoldOld.contains(keyCode)) {
                        buttonDown.emplace(keyCode);
                    } else {
                        buttonHold.emplace(keyCode);
                    }
                } else if (buttonDownOld.contains(keyCode) || buttonHoldOld.contains(keyCode)) {
                    buttonUp.emplace(keyCode);
                }
            }
        }

        // Gamepad Input
        if (glfwJoystickPresent(GLFW_JOYSTICK_1) && glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
            gamepadButtonDownOld.swap(gamepadButtonDown);
            gamepadButtonHoldOld.swap(gamepadButtonHold);

            gamepadButtonDown.clear();
            gamepadButtonHold.clear();
            gamepadButtonUp.clear();

            GLFWgamepadstate state;
 
            if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
                for (const auto& pair: gamepadButtonNameBinds) {
                    for (const auto keyCode: pair.second) {
                        if (state.buttons[keyCode] == GLFW_PRESS) {
                            if (!gamepadButtonDownOld.contains(keyCode) && !gamepadButtonHoldOld.contains(keyCode)) {
                                gamepadButtonDown.emplace(keyCode);
                            } else {
                                gamepadButtonHold.emplace(keyCode);
                            }
                        } else if (gamepadButtonDownOld.contains(keyCode) || gamepadButtonHoldOld.contains(keyCode)) {
                            gamepadButtonUp.emplace(keyCode);
                        }
                    }
                }
            }
        }

        // Mouse Input
        mouseButtonDownOld.swap(mouseButtonDown);
        mouseButtonHoldOld.swap(mouseButtonHold);

        mouseButtonDown.clear();
        mouseButtonHold.clear();
        mouseButtonUp.clear();

        for (const auto& pair: mouseButtonNameBinds) {
            for (const auto keyCode: pair.second) {
                if (glfwGetMouseButton(window, keyCode) == GLFW_PRESS) {
                    if (!mouseButtonDownOld.contains(keyCode) && !mouseButtonHoldOld.contains(keyCode)) {
                        mouseButtonDown.emplace(keyCode);
                    } else {
                        mouseButtonHold.emplace(keyCode);
                    }
                } else if (mouseButtonDownOld.contains(keyCode) || mouseButtonHoldOld.contains(keyCode)) {
                    mouseButtonUp.emplace(keyCode);
                }
            }
        }
    }

    bool isKeyDown(std::size_t buttonName) const noexcept {
        for (const auto keyCode: buttonNameBinds.at(buttonName)) {
            if (buttonDown.contains(keyCode)) {
                return true;
            }
        }
        for (const auto keyCode: gamepadButtonNameBinds.at(buttonName)) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1) && glfwJoystickIsGamepad(GLFW_JOYSTICK_1) && gamepadButtonDown.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    bool isKeyHold(std::size_t buttonName) const noexcept {
        for (const auto keyCode: buttonNameBinds.at(buttonName)) {
            if (buttonHold.contains(keyCode)) {
                return true;
            }
        }
        for (const auto keyCode: gamepadButtonNameBinds.at(buttonName)) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1) && glfwJoystickIsGamepad(GLFW_JOYSTICK_1) && gamepadButtonHold.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    bool isKeyUp(std::size_t buttonName) const noexcept {
        for (const auto keyCode: buttonNameBinds.at(buttonName)) {
            if (buttonUp.contains(keyCode)) {
                return true;
            }
        }
        for (const auto keyCode: gamepadButtonNameBinds.at(buttonName)) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1) && glfwJoystickIsGamepad(GLFW_JOYSTICK_1) && gamepadButtonUp.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    bool isMouseDown(std::size_t buttonName) const noexcept {
        for (const auto keyCode: mouseButtonNameBinds.at(buttonName)) {
            if (mouseButtonDown.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    bool isMouseHold(std::size_t buttonName) const noexcept {
        for (const auto keyCode: mouseButtonNameBinds.at(buttonName)) {
            if (mouseButtonHold.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    bool isMouseUp(std::size_t buttonName) const noexcept {
        for (const auto keyCode: mouseButtonNameBinds.at(buttonName)) {
            if (mouseButtonUp.contains(keyCode)) {
                return true;
            }
        }
        return false;
    }

    float getAxisX() const noexcept {
        int count;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
        if (count >= 2) {
            return axes[0];
        }
        return 0;
    }

    float getAxisY() const noexcept {
        int count;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
        if (count >= 2) {
            return axes[1];
        }
        return 0;
    }

    void getFramebufferSize(int& width, int& height) {
        glfwGetFramebufferSize(window, &width, &height);
    }

    [[nodiscard]] constexpr const glm::ivec2& getSize() const noexcept {
        return size;
    }

    bool createWindowSurface(VkInstance& instance, VkSurfaceKHR& surface) {
        return glfwCreateWindowSurface(instance, window, nullptr, &surface);
    }

    void create() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

private:
    static void framebufferResizeCallback(GLFWwindow* window, [[maybe_unused]] int width, [[maybe_unused]] int height) {
        auto* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        windowPtr->size.x = width;
        windowPtr->size.y = height;
        windowPtr->framebufferResized = true;
    }

private:
    glm::ivec2 size;
    std::string title;
    GLFWwindow* window;

public:
    bool framebufferResized = false;

public:
    std::unordered_map<std::size_t, std::vector<int>> buttonNameBinds;

private:
    std::unordered_set<int> buttonDown;
    std::unordered_set<int> buttonHold;
    std::unordered_set<int> buttonUp;

    std::unordered_set<int> buttonDownOld;
    std::unordered_set<int> buttonHoldOld;

public:
    std::unordered_map<std::size_t, std::vector<int>> mouseButtonNameBinds;

private:
    std::unordered_set<int> mouseButtonDown;
    std::unordered_set<int> mouseButtonHold;
    std::unordered_set<int> mouseButtonUp;

    std::unordered_set<int> mouseButtonDownOld;
    std::unordered_set<int> mouseButtonHoldOld;

public:
    std::unordered_map<std::size_t, std::vector<int>> gamepadButtonNameBinds;

private:
    std::unordered_set<int> gamepadButtonDown;
    std::unordered_set<int> gamepadButtonHold;
    std::unordered_set<int> gamepadButtonUp;

    std::unordered_set<int> gamepadButtonDownOld;
    std::unordered_set<int> gamepadButtonHoldOld;
};