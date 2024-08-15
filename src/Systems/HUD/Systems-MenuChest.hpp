#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void menuChestValidateSys(MainFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::VALIDATE)) {
        for (auto [menuEnt]: world.view(with<MenuChest>)) {
            auto [time] = world.resource<Time>();
            time.setTimeScale(1);
            world.destroy(menuEnt);
        }
    }
}