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
            XpIconInventoryBar(),
            UICreator(HUDElementsUV, 4, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(+4, 8 + 4),
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
        // Frame
        world.newEnt(
            UICreator(bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(80, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Icon
        world.newEnt(
            ButtonAIconInventoryBar(),
            UICreator(bottomBarUV, 1, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(82 + 8, +8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Bottom Bar Spell B
        // Frame
        world.newEnt(
            UICreator(bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(104, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
        // Icon
        world.newEnt(
            ButtonBIconInventoryBar(),
            UICreator(bottomBarUV, 2, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(106 + 8, +8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),

        // Coin Text
        world.newEnt(
            PlayerCoinText(),
            TextUICreator("0", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::BOTTOM_CENTER, glm::vec2(24, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_RIGHT),
            Transform(
                position + glm::vec2(120, 2),
                0,
                glm::vec2(1, 1)
            )
        ),
        // Coin Icon
        world.newEnt(
            CoinIconInventoryBar(),
            UICreator(HUDElementsUV, 5, UIAnchor::BOTTOM_CENTER),
            Transform(
                position + glm::vec2(144 + 8, +8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        ),
    });

    return inventoryBarEnt;
}