#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePlayerBombParticle(World& world, const glm::vec2& position, std::size_t newZIndex, const glm::vec2& spreadDirection) {
    return world.newEnt(
        Bomb(1.f),
        PlayerWeapon(),
        Damage(1),
        SpriteCreator(playerBombUV),
        Animation(playerBombAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(newZIndex - 1),
        BombSpread(0.0625f, spreadDirection, 128.f),
        Velocity(),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );
}