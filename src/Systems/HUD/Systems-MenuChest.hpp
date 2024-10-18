#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void menuChestValidateSys(MainUnscaledFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::VALIDATE)) {
        for (auto [menuEnt]: world.query(with<MenuChest>)) {
            auto [time] = world.resource<Time>();
            time.setTimeScale(1);
            world.delete_entity(menuEnt);
        }
    }
}