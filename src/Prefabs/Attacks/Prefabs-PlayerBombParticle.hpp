#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePlayerBombParticle(World& world, const glm::vec2& position, std::size_t newZIndex, const glm::vec2& spreadDirection) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Bomb(1.f),
        PlayerWeapon(),
        Damage(1),
        Sprite(textureManager, playerBombUV),
        Animation(playerBombAnim, PlayerBombAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(newZIndex - 1),
        BombSpread(0.125f, spreadDirection, 64.f),
        Velocity(),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );
}