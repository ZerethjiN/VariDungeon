#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePlayerEnemyExplosionAttackParticle(World&, const glm::vec2&);

Ent instantiateTNTBarel(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Breakable(),
        OnBreakableHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(TntBarelAnimType::HIT);
            }
        }),
        OnBreakableNoHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(TntBarelAnimType::NO_HIT);
            }
        }),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (auto opt = world.get<const Transform2D>(thisEnt)) {
                auto [transform] = opt.value();
                instantiatePlayerEnemyExplosionAttackParticle(world, transform.getPosition());
            }
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(TntBarelAnimType::DESTROYED);
            }
        }),
        Life(1),
        Sprite(textureManager, tntBarelUV),
        Animation(tntBarelAnim, TntBarelAnimType::NO_HIT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots(),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}