#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBarbarian(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.appendChildren(
        // Parent
        world.create_entity(
            Unerasable(),
            Player(),
            Barbarian(),
            PlayerXp(25),
            Life(5),//(5),
            PlayerCoin(),
            PlayerDamage(1),//(1),
            PlayerBonuses(),
            PlayerFloor(
                /*MerchantFloor:*/ {2, 4}
            ),
            // PlayerBomb(2.0f),
            PlayerAttackCooldown(0.25f),
            PlayerKnockbackStrength(128.f),
            Sprite(textureManager, barbareUV),
            Animation(barbareAnim, BarbareAnimType::MOVE_DOWN),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(0),
            Velocity(),
            Speed(72),
            Orientation(Orientation::SOUTH),
            Collider(-8 / 2, -8 / 2, 8, 8)
        ),
        // Children
        {
            world.create_entity(
                PlayerAttractor(),
                Transform2D(
                    position,
                    0,
                    glm::vec2(1, 1)
                ),
                Velocity(),
                Trigger(-48 / 2, -48 / 2, 48, 48)
            )
        }
    );
}

Ent instantiateBarbarianPersistence(World& world, const glm::vec2& position, const BarbareAnimType& animationType, std::size_t zindex) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, barbareUV),
        Animation(barbareAnim, animationType),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(zindex),
        LifeTime(0.25f)
    );
}