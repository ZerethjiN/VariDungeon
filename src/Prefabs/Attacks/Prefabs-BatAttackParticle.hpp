#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBatAttackParticle(World& world, const glm::vec2& position, float rotation) {
    return world.newEnt(
        SpriteCreator(batAttackParticleUV),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(0.25f),
        Trigger(-48 / 2, -32 / 2, 48, 32)
    );
}