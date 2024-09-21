#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateInventoryBarUI(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.appendChildren(
        // Parent
        world.newEnt(
            UI(textureManager, inventoryBarUV, UIAnchor::BOTTOM_CENTER),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(0)
        ),
        // Children
        {
            // Life Icon
            world.newEnt(
                UI(textureManager, HUDElementsUV, 2, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(0, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Life Inner Bar
            world.newEnt(
                PlayerLifeBarInner(56),
                UI(textureManager, HUDElementsUV, 1, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(8, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Life Outer Bar
            world.newEnt(
                UI(textureManager, HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
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
                Transform2D(
                    position + glm::vec2(8, -1),
                    0,
                    glm::vec2(1, 1)
                )
            ),
            // Xp Icon
            world.newEnt(
                XpIconInventoryBar(),
                UI(textureManager, HUDElementsUV, 4, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(+4, 8 + 4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Xp Inner Bar
            world.newEnt(
                PlayerXpBarInner(56),
                UI(textureManager, HUDElementsUV, 1, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(8, 8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Xp Outer Bar
            world.newEnt(
                UI(textureManager, HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
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
                Transform2D(
                    position + glm::vec2(8, 7),
                    0,
                    glm::vec2(1, 1)
                )
            ),

            // Bottom Bar Spell A
            // Frame
            world.newEnt(
                UI(textureManager, bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(80, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Icon
            world.newEnt(
                ButtonAIconInventoryBar(),
                UI(textureManager, bottomBarUV, 1, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(82 + 8, +8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Bottom Bar Spell B
            // Frame
            world.newEnt(
                UI(textureManager, bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(104, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Icon
            world.newEnt(
                ButtonBIconInventoryBar(),
                UI(textureManager, bottomBarUV, 2, UIAnchor::BOTTOM_CENTER),
                Transform2D(
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
                Transform2D(
                    position + glm::vec2(120, 2),
                    0,
                    glm::vec2(1, 1)
                )
            ),
            // Coin Icon
            world.newEnt(
                CoinIconInventoryBar(),
                UI(textureManager, HUDElementsUV, 5, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(144 + 8, +8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
        }
    );
}