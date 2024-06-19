#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rerollSys(MainFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(REROLL_BUTTON)) {
        printf("Prout\n");
        world.loadScene(testScene);
    }
}