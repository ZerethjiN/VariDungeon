#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBat(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            Enemy(),
            EnemyPreSpawn(0.5f, 2),
            Bat(
                /*MoveDuration:*/ 1.0f,
                /*AttackDuration:*/ 0.75f,
                /*AttackRadius:*/ 32.f
            ),
            IsBatMove(1.0f),
            EnemyWeapon(),
            Damage(1),
            Sprite(textureManager, batUV),
            Animation(batAnim, BatAnimType::MOVE_DOWN),
            Transform2D(
                position,
                0,
                glm::vec2(1, 1)
            ),
            Loots({{LOOT_TYPE_XP, 2, 3}}),
            ZIndex(0),
            Life(2),
            Velocity(),
            Speed(24),
            Orientation(Orientation::SOUTH),
            Collider(-12 / 2, -12 / 2, 12, 12)
        ),
        // Children
        {
            world.create_entity(
                Sprite(textureManager, shadowUV),
                Animation(shadowAnim, ShadowAnimType::SMALL),
                Transform2D(
                    position + glm::vec2(0, 2),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-2)
            )
        }
    );
}