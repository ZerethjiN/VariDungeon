#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePlayerEnemyExplosionAttackParticle(World&, const glm::vec2&);

Ent instantiateTNTBarel(World& world, const glm::vec2& position) {
    return world.newEnt(
        Breakable("NoHit", "Hit", "Destroyed"),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (auto opt = world.get<const Transform>(thisEnt)) {
                auto [transform] = opt.value();
                instantiatePlayerEnemyExplosionAttackParticle(world, transform.getPosition());
            }
        }),
        Life(1),
        SpriteCreator(tntBarelUV),
        Animation(tntBarelAnim, "NoHit"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}