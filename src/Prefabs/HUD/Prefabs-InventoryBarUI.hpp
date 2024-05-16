#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateInventoryBarUI(World& world, const glm::vec2& position) {
    auto inventoryBarEnt = world.newEnt(
        UICreator(inventoryBarUV, UIAnchor::BOTTOM_CENTER),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0)
    );

    world.appendChildren(inventoryBarEnt, {
        // Life Icon
        world.newEnt(
            UICreator(HUDElementsUV, 2, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(0, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Life Inner Bar
        world.newEnt(
            PlayerLifeBarInner(56),
            UICreator(HUDElementsUV, 1, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(8, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Life Outer Bar
        world.newEnt(
            UICreator(HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(8, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(2)
        ),
        // Life Text
        world.newEnt(
            PlayerLifeText(),
            TextUICreator("HP 5/5", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::BOTTOM_CENTER, glm::vec2(56, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
            Transform(
                position + glm::vec2(8, -1),
                0,
                glm::vec2(1, 1)
            )
        ),

        // Xp Icon
        world.newEnt(
            UICreator(HUDElementsUV, 4, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(0, 8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Xp Inner Bar
        world.newEnt(
            PlayerXpBarInner(56),
            UICreator(HUDElementsUV, 1, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(8, 8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Xp Outer Bar
        world.newEnt(
            UICreator(HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(8, 8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(2)
        ),
        // Xp Text
        world.newEnt(
            PlayerXpText(),
            TextUICreator("XP 0/25", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::BOTTOM_CENTER, glm::vec2(56, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
            Transform(
                position + glm::vec2(8, 7),
                0,
                glm::vec2(1, 1)
            )
        ),

        // Bottom Bar Spell A
        world.newEnt(
            UICreator(bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(80, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Bottom Bar Spell B
        world.newEnt(
            UICreator(bottomBarUV, 1, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(104, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
    });

    return inventoryBarEnt;
}