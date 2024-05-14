#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void cameraSys(World& world) {
    auto cameras = world.view<const Transform>(with<CurCamera>);

    auto [inGameView] = world.getRes<InGameView>();

    for (auto [_, trans]: cameras) {
        const auto& windowSize = vulkanEngine.window.getSize();

        if (160.f * (static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y)) > 160.f) {
            inGameView.setSize(static_cast<int>(160.f * (static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y))), 144);
        } else {
            inGameView.setSize(160.f, static_cast<int>(144.f * (static_cast<float>(windowSize.y) / static_cast<float>(windowSize.x))));
        }
        inGameView.setCenter(trans.getPosition());
    }
}