#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuBonusUI(World& world, const glm::vec2& position, const std::unordered_set<std::size_t>& bonusesIdx) {
    auto backgroundEnt = world.newEnt(
        MenuBonus(),
        MenuBonusTranslation(position, 512.f, bonusesIdx),
        UICreator(menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform(
            position + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );

    return backgroundEnt;
}

Ent instantiateMenuBonusMerchantUI(World& world, const glm::vec2& position, const std::unordered_set<std::size_t>& bonusesIdx) {
    auto backgroundEnt = world.newEnt(
        MenuBonus(),
        MenuBonusMerchant(),
        MenuBonusTranslation(position, 512.f, bonusesIdx),
        UICreator(menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform(
            position + glm::vec2(0, 144),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1)
    );

    return backgroundEnt;
}