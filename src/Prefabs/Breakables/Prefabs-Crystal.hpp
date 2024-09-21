#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectStar(World&, const glm::vec2&);

Ent instantiateCrystal(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Breakable(),
        Life(1),
        Sprite(textureManager, crystalUV),
        Animation(crystalAnim, CrystalAnimType::NO_HIT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({
            {LOOT_TYPE_COIN, 2, 3},
            {LOOT_TYPE_HEART, 1, 1}
        }),
        ParticleGenerator(instantiateParticleEffectStar, 1.5f, 8.f),
        OnBreakableHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(CrystalAnimType::HIT);
            }
        }),
        OnBreakableNoHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(CrystalAnimType::NO_HIT);
            }
        }),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (world.has<ParticleGenerator>(thisEnt)) {
                world.remove<ParticleGenerator>(thisEnt);
            }
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(CrystalAnimType::DESTROYED);
            }
        }),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}