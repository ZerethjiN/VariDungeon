#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void menuBonusSelectorSys(World& world) {
    auto selectors = world.view<MenuBonusSelector, Transform>();

    for (auto [_, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(MOVE_DOWN)) {
            if (selector.nextElement()) {
                selectorTransform.moveY(32.f);
            }
        } else if (vulkanEngine.window.isKeyDown(MOVE_UP)) {
            if (selector.previousElement()) {
                selectorTransform.moveY(-32.f);
            }
        } else if (vulkanEngine.window.isKeyDown(VALIDATE)) {
            for (auto [menuBonusEnt]: world.view(with<MenuBonus>)) {
                world.destroy(menuBonusEnt);
            }
            auto [time] = world.resource<Time>();
            time.setTimeScale(1.0f);
        }
    }
}