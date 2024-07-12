#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Scenes.hpp>

void startSys(StartSystem, World& world) {
    vulkanEngine.window.buttonNameBinds = {
        {MOVE_UP, {GLFW_KEY_W, GLFW_KEY_UP}},
        {MOVE_DOWN, {GLFW_KEY_S, GLFW_KEY_DOWN}},
        {MOVE_LEFT, {GLFW_KEY_A, GLFW_KEY_LEFT}},
        {MOVE_RIGHT, {GLFW_KEY_D, GLFW_KEY_RIGHT}},
        {VALIDATE, {GLFW_KEY_ENTER}},
        {B_BUTTON, {GLFW_KEY_SPACE}},
        {A_BUTTON, {GLFW_KEY_ENTER}},
        {EXIT, {GLFW_KEY_ESCAPE}},
        {REROLL_BUTTON, {GLFW_KEY_R}},
        {MAP_MENU, {GLFW_KEY_M, GLFW_KEY_SEMICOLON}}
    };

    vulkanEngine.window.gamepadButtonNameBinds = {
        {MOVE_UP, {GLFW_GAMEPAD_BUTTON_DPAD_UP}},
        {MOVE_DOWN, {GLFW_GAMEPAD_BUTTON_DPAD_DOWN}},
        {MOVE_LEFT, {GLFW_GAMEPAD_BUTTON_DPAD_LEFT}},
        {MOVE_RIGHT, {GLFW_GAMEPAD_BUTTON_DPAD_RIGHT}},
        {VALIDATE, {GLFW_GAMEPAD_BUTTON_A}},
        {B_BUTTON, {GLFW_GAMEPAD_BUTTON_B}},
        {A_BUTTON, {GLFW_GAMEPAD_BUTTON_A}},
        {EXIT, {GLFW_GAMEPAD_BUTTON_Y}},
        {REROLL_BUTTON, {GLFW_GAMEPAD_BUTTON_X}},
        {MAP_MENU, {GLFW_GAMEPAD_BUTTON_START}}
    };

    // vulkanEngine.window.mouseButtonNameBinds = {
    //     {MOUSE_LEFT, {GLFW_MOUSE_BUTTON_LEFT}},
    //     {MOUSE_RIGHT, {GLFW_MOUSE_BUTTON_RIGHT}},
    // };

    world.loadScene(testScene2);
}