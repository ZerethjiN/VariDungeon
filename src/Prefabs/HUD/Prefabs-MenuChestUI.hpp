#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuChestUI(World& world, const glm::vec2& position) {
    return world.newEnt(
        MenuChest(),
        UICreator(menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform(
            position,// + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );
}