#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rerollSys(MainFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::REROLL_BUTTON)) {
        world.loadScene(testScene);
    }
}