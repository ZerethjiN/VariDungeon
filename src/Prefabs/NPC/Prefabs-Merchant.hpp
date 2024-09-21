#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMerchant(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.appendChildren(
        // Parent
        world.newEnt(
            Merchant(),
            Sprite(textureManager, merchantUV),
            Animation(merchantAnim, MerchantAnimType::DEFAULT),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            Collider(-16 / 2, -16 / 2, 16, 16)
        ),
        // Children
        {
            world.newEnt(
                MerchantRadius(),
                    Transform2D(
                    position,
                    0,
                    glm::vec2(1, 1)
                ),
                Trigger(-48 / 2, -48 / 2, 48, 48)
            )
        }
    );
}