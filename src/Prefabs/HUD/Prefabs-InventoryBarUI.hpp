#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateInventoryBarUI(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
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
            world.create_entity(
                UI(textureManager, HUDElementsUV, 2, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(0, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Life Inner Bar
            world.create_entity(
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
            world.create_entity(
                UI(textureManager, HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(8, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(2)
            ),
            // Life Text
            world.create_entity(
                PlayerLifeText(),
                TextUICreator("HP 5/5", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::BOTTOM_CENTER, glm::vec2(56, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                Transform2D(
                    position + glm::vec2(8, -1),
                    0,
                    glm::vec2(1, 1)
                )
            ),
            // Xp Icon
            world.create_entity(
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
            world.create_entity(
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
            world.create_entity(
                UI(textureManager, HUDElementsUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(8, 8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(2)
            ),
            // Xp Text
            world.create_entity(
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
            world.create_entity(
                UI(textureManager, bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(80, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Icon
            world.create_entity(
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
            world.create_entity(
                UI(textureManager, bottomBarUV, 0, UIAnchor::BOTTOM_CENTER),
                Transform2D(
                    position + glm::vec2(104, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            // Icon
            world.create_entity(
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
            world.create_entity(
                PlayerCoinText(),
                TextUICreator("0", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::BOTTOM_CENTER, glm::vec2(24, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_RIGHT),
                Transform2D(
                    position + glm::vec2(120, 2),
                    0,
                    glm::vec2(1, 1)
                )
            ),
            // Coin Icon
            world.create_entity(
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