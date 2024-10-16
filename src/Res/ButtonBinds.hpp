#pragma once

#include <Zerengine.hpp>

enum class ButtonNameType: std::size_t {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    VALIDATE,
    EXIT,
    B_BUTTON,
    A_BUTTON,
    REROLL_BUTTON,
    DEBUG_COMMAND,
    MAP_MENU
};

enum class MouseButtonNameType: std::size_t {
    MOUSE_LEFT,
    MOUSE_RIGHT
};