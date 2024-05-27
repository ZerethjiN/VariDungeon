#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSpike(World& world, const glm::vec2& position) {
    return world.newEnt(
        EnemyWeapon(),
        Damage(1),
        Spike(1.0f, 1.0f),
        IsSpikeDown(1.0f),
        SpriteCreator(spikeUV, 0),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-15)
    );
}