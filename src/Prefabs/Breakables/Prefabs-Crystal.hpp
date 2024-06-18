#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectStar(World&, const glm::vec2&);

Ent instantiateCrystal(World& world, const glm::vec2& position) {
    return world.newEnt(
        Breakable("NoHit", "Hit", "Destroyed"),
        Life(1),
        SpriteCreator(crystalUV),
        Animation(crystalAnim, "NoHit"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({
            {LOOT_TYPE_COIN, 2, 3},
            {LOOT_TYPE_HEART, 1, 1}
        }),
        ParticleGenerator(instantiateParticleEffectStar, 1.5f, 8.f),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (world.has<ParticleGenerator>(thisEnt)) {
                world.remove<ParticleGenerator>(thisEnt);
            }
        }),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}