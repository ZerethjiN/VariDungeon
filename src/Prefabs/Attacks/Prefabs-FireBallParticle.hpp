#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateFireBallParticle(World& world, const glm::vec2& position, const glm::vec2& direction, float speed) {
    return world.newEnt(
        FireBall(direction),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(fireBallParticleUV),
        Animation(fireBallParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(1.5f),
        Velocity(),
        Speed(speed),
        Trigger(-12 / 2, -12 / 2, 12, 12)
    );
}