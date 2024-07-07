#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePauseMenuUI(World& world, const glm::vec2& position) {
    auto backgroundEnt = world.newEnt(
        PauseMenu(),
        PauseMenuTranslation(position, 512.f),
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