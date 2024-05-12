#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateItemFeedbackParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(itemFeedbackParticleUV),
        Animation(itemFeedbackParticleAnim, "Big"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.2f)
    );
}