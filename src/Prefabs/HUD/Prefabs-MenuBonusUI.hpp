#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuBonusUI(World& world, const glm::vec2& position, const std::unordered_set<std::size_t>& bonusesIdx) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Menu(),
        MenuBonus(),
        MenuBonusTranslation(position, 512.f, bonusesIdx),
        UI(textureManager, menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform2D(
            position + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );
}

Ent instantiateMenuBonusMerchantUI(World& world, const glm::vec2& position, const std::unordered_set<std::size_t>& bonusesIdx) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Menu(),
        MenuBonus(),
        MenuBonusMerchant(),
        MenuBonusTranslation(position, 512.f, bonusesIdx),
        UI(textureManager, menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform2D(
            position + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );
}