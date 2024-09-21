#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuChestUI(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Menu(),
        MenuChest(),
        UI(textureManager, menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform2D(
            position,// + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );
}