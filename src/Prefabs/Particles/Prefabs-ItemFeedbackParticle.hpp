#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateItemFeedbackParticle(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, itemFeedbackParticleUV),
        Animation(itemFeedbackParticleAnim, ItemFeedbackParticleAnimType::BIG),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.1f)
    );
}