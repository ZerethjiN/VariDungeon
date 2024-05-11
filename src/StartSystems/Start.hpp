#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Scenes.hpp>

void startSys(World& world) {
    vulkanEngine.window.buttonNameBinds = {
        {MOVE_UP, {GLFW_KEY_W, GLFW_KEY_UP}},
        {MOVE_DOWN, {GLFW_KEY_S, GLFW_KEY_DOWN}},
        {MOVE_LEFT, {GLFW_KEY_A, GLFW_KEY_LEFT}},
        {MOVE_RIGHT, {GLFW_KEY_D, GLFW_KEY_RIGHT}},
        {VALIDATE, {GLFW_KEY_ENTER}},
        {B_BUTTON, {GLFW_KEY_SPACE}},
        {A_BUTTON, {GLFW_KEY_ENTER}},
        {EXIT, {GLFW_KEY_ESCAPE}}
    };

    // vulkanEngine.window.mouseButtonNameBinds = {
    //     {MOUSE_LEFT, {GLFW_MOUSE_BUTTON_LEFT}},
    //     {MOUSE_RIGHT, {GLFW_MOUSE_BUTTON_RIGHT}},
    // };

    world.loadScene(testScene);
}