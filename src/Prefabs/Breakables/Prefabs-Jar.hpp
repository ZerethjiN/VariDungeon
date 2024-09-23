#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateJar(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Breakable(),
        Life(1),
        Sprite(textureManager, jarUV),
        Animation(jarAnim, JarAnimType::NO_HIT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({
            {LOOT_TYPE_COIN, 2, 3},
            {LOOT_TYPE_HEART, 1, 1}
        }),
        OnBreakableHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(JarAnimType::HIT);
            }
        }),
        OnBreakableNoHit([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(JarAnimType::NO_HIT);
            }
        }),
        OnBreakableBreak([](World& world, Ent thisEnt) {
            if (auto opt = world.get<Animation>(thisEnt)) {
                auto [animation] = opt.value();
                animation.play(JarAnimType::DESTROYED);
            }
        }),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}