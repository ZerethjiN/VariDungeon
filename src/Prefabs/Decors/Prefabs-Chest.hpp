#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateChest(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Chest(),
        Sprite(textureManager, chestUV),
        // Animation(chestAnim, ChestAnimType::OPENING),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -16 / 2, 16, 16),
        ParticleGenerator(instantiateParticleEffectStar, 0.5f, 12.f)
    );
}