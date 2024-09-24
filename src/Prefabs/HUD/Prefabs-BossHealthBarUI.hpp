#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBossHealthBarUI(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            BossHealthBar(),
            UI(textureManager, bossHealthBarUV, 0, UIAnchor::TOP_CENTER),
            Transform2D(
                position + glm::vec2(-48, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(10)
        ),
        // Children
        {
            world.create_entity(
                UI(textureManager, bossHealthBarUV, 1, UIAnchor::TOP_CENTER),
                Transform2D(
                    position + glm::vec2(-48, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(8)
            ),
            world.create_entity(
                BossHealthBarInner(88),
                UI(textureManager, bossHealthBarUV, 2, UIAnchor::TOP_CENTER),
                Transform2D(
                    position + glm::vec2(-44, 4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(9)
            ),
            world.create_entity(
                BossHealthBarInner(88),
                UI(textureManager, bossHealthBarUV, 2, UIAnchor::TOP_CENTER),
                Transform2D(
                    position + glm::vec2(-44, 4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(9)
            ),
            // world.create_entity(
            //     BossHealthBarText(),
            //     TextUI("HP 0/0", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::TOP_CENTER, glm::vec2(88, 8), glm::vec4(173, 157, 115, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
            //     Transform2D(
            //         position + glm::vec2(-44, 4),
            //         0,
            //         glm::vec2(1, 1)
            //     )
            // ),
        }
    );
}