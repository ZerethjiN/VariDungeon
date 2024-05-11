#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSwordImpact(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(swordImpactUV),
        Animation(swordImpactAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.1f)
    );
}