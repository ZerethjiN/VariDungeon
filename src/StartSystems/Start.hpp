#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Scenes.hpp>

void startSys(StartSystem, World& world) {
    vulkanEngine.window.buttonNameBinds = {
        {static_cast<std::size_t>(ButtonNameType::MOVE_UP), {GLFW_KEY_W, GLFW_KEY_UP}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_DOWN), {GLFW_KEY_S, GLFW_KEY_DOWN}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_LEFT), {GLFW_KEY_A, GLFW_KEY_LEFT}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_RIGHT), {GLFW_KEY_D, GLFW_KEY_RIGHT}},
        {static_cast<std::size_t>(ButtonNameType::VALIDATE), {GLFW_KEY_ENTER}},
        {static_cast<std::size_t>(ButtonNameType::B_BUTTON), {GLFW_KEY_SPACE}},
        {static_cast<std::size_t>(ButtonNameType::A_BUTTON), {GLFW_KEY_ENTER}},
        {static_cast<std::size_t>(ButtonNameType::EXIT), {GLFW_KEY_ESCAPE}},
        {static_cast<std::size_t>(ButtonNameType::REROLL_BUTTON), {GLFW_KEY_R}},
        {static_cast<std::size_t>(ButtonNameType::MAP_MENU), {GLFW_KEY_M, GLFW_KEY_SEMICOLON}}
    };

    vulkanEngine.window.gamepadButtonNameBinds = {
        {static_cast<std::size_t>(ButtonNameType::MOVE_UP), {GLFW_GAMEPAD_BUTTON_DPAD_UP}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_DOWN), {GLFW_GAMEPAD_BUTTON_DPAD_DOWN}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_LEFT), {GLFW_GAMEPAD_BUTTON_DPAD_LEFT}},
        {static_cast<std::size_t>(ButtonNameType::MOVE_RIGHT), {GLFW_GAMEPAD_BUTTON_DPAD_RIGHT}},
        {static_cast<std::size_t>(ButtonNameType::VALIDATE), {GLFW_GAMEPAD_BUTTON_A}},
        {static_cast<std::size_t>(ButtonNameType::B_BUTTON), {GLFW_GAMEPAD_BUTTON_B}},
        {static_cast<std::size_t>(ButtonNameType::A_BUTTON), {GLFW_GAMEPAD_BUTTON_A}},
        {static_cast<std::size_t>(ButtonNameType::EXIT), {GLFW_GAMEPAD_BUTTON_Y}},
        {static_cast<std::size_t>(ButtonNameType::REROLL_BUTTON), {GLFW_GAMEPAD_BUTTON_X}},
        {static_cast<std::size_t>(ButtonNameType::MAP_MENU), {GLFW_GAMEPAD_BUTTON_START}}
    };

    // vulkanEngine.window.mouseButtonNameBinds = {
    //     {MOUSE_LEFT, {GLFW_MOUSE_BUTTON_LEFT}},
    //     {MOUSE_RIGHT, {GLFW_MOUSE_BUTTON_RIGHT}},
    // };

    world.loadScene(testScene2);
}