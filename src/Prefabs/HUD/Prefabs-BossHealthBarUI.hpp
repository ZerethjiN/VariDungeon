#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBossHealthBarUI(World& world, const glm::vec2& position) {
    auto bossHealthBarOuterEnt = world.newEnt(
        BossHealthBar(),
        UICreator(bossHealthBarUV, 0, UIAnchor::TOP_CENTER),
        Transform(
            position + glm::vec2(-48, 0),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(10)
    );

    world.appendChildren(bossHealthBarOuterEnt, {
        world.newEnt(
            UICreator(bossHealthBarUV, 1, UIAnchor::TOP_CENTER),
            Transform(
                position + glm::vec2(-48, 0),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(8)
        ),

        world.newEnt(
            BossHealthBarInner(88),
            UICreator(bossHealthBarUV, 2, UIAnchor::TOP_CENTER),
            Transform(
                position + glm::vec2(-44, 4),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(9)
        ),
        world.newEnt(
            BossHealthBarInner(88),
            UICreator(bossHealthBarUV, 2, UIAnchor::TOP_CENTER),
            Transform(
                position + glm::vec2(-44, 4),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(9)
        ),
        // world.newEnt(
        //     BossHealthBarText(),
        //     TextUICreator("HP 0/0", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::TOP_CENTER, glm::vec2(88, 8), glm::vec4(173, 157, 115, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
        //     Transform(
        //         position + glm::vec2(-44, 4),
        //         0,
        //         glm::vec2(1, 1)
        //     )
        // ),
    });

    return bossHealthBarOuterEnt;
}