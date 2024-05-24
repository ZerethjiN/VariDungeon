#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBarbarian(World& world, const glm::vec2& position) {
    auto playerEnt = world.newEnt(
        Player(),
        Barbarian(),
        PlayerXp(25),
        Life(5),
        PlayerCoin(),
        PlayerDamage(1),
        PlayerBonuses(),
        PlayerAttackCooldown(0.25f),
        PlayerKnockbackStrength(128.f),
        SpriteCreator(barbareUV),
        Animation(barbareAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Velocity(),
        Speed(80),
        Orientation(Orientation::SOUTH),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );

    world.appendChildren(playerEnt, {
        world.newEnt(
            PlayerAttractor(),
            Transform(
                position,
                0,
                glm::vec2(1, 1)
            ),
            Velocity(),
            Trigger(-64 / 2, -64 / 2, 64, 64)
        )
    });

    return playerEnt;
}