#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateTalentSphere(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        TalentSphere(),
        Sprite(textureManager, talentSphereUV),
        Animation(talentSphereAnim, TalentSphereAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -16 / 2, 16, 16)
    );
}