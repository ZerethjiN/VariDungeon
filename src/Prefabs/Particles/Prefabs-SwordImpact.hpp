#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSwordImpact(World& world, const glm::vec2& position, int baseZIndex) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, swordImpactUV),
        Animation(swordImpactAnim, SwordImpactAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex + 1),
        LifeTime(0.1f)
    );
}