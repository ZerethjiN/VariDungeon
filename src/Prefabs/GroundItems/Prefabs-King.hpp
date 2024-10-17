#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

void hubScene(SceneSystem, World&);

Ent instantiateKingGroundItem(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        // ShieldGroundItem(1.f),
        Sprite(textureManager, kingUV),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Trigger(-8 / 2, -8 / 2, 8, 8),
        Lootable(),
        Velocity(),
        LootCallback([](World& world, const Ent& this_entity, const Ent& target_entity) {
            if (world.has_components<Player>(target_entity)) {
                for (auto [player_ent]: world.view(with<Player>)) {
                    world.delete_entity(player_ent);
                }
                world.loadScene(hubScene);
            }
        })
    );
}