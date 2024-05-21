#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuBonusUI(World& world, const glm::vec2& position, int nbElements) {
    auto backgroundEnt = world.newEnt(
        MenuBonus(),
        UICreator(menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0)
    );

    world.appendChildren(backgroundEnt, {
        world.newEnt(
            MenuBonusSelector(nbElements),
            UICreator(menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
            Animation(menuBonusHUDAnim, "MediumSelector", AnimType::UNSCALED),
            Transform(
                position + glm::vec2(8, 8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        )
    });

    return backgroundEnt;
}