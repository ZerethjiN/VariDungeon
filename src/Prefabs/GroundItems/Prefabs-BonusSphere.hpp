#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBonusSphere(World& world, const glm::vec2& position) {
    auto bonusSphereEnt = world.newEnt(
        BonusSphere(),
        SpriteCreator(bonusSphereUV),
        Animation(bonusSphereAnim, "Default"),
        Transform(
            position + glm::vec2(-8, -12),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-1),
        InnerMovement(1, 2),
        InnerMovementUp(),
        Lootable(),
        Velocity(),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );

    world.appendChildren(bonusSphereEnt, {
        world.newEnt(
            SpriteCreator(shadowUV),
            Animation(shadowAnim, "Small"),
            Transform(
                position + glm::vec2(-8, -4),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-2)
        )
    });

    return bonusSphereEnt;
}