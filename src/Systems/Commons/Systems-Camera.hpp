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
        inGameView.setCenter(trans.getPosition());
    }
}