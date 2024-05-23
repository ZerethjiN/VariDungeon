#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShurikenParticle(World& world, const glm::vec2& position, float rotationSpeed) {
    return world.newEnt(
        Shuriken(rotationSpeed),
        PlayerWeapon(),
        Damage(1),
        SpriteCreator(shurikenParticleUV),
        // Animation(shurikenParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Velocity(),
        Trigger(-8 / 2, -8 / 2, 8, 8)
    );
}