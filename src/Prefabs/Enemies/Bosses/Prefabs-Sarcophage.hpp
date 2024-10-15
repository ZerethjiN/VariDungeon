#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSarcophage(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Sarcophage(
            /*PreLaserDuration:*/ 0.75f,
            /*LaserDuration:*/ 2.0f,
            /*ShadowMarkDuration:*/ 1.5f,
            /*NbShadowMark:*/ 3,
            /*Obelisk:*/ 3.0f
        ),
        IsSarcophageShadowMark(1.5f, 3),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, sarcophageUV),
        Animation(sarcophageAnim, SarcophageAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 4, 6}}),
        ZIndex(0),
        Life(30),
        Velocity(),
        Speed(24),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24),
        OnEnemyDeath([](World& world, const Ent& this_ent) {
            for (auto [obelisk_ent]: world.view(with<SarcophageObelisk>)) {
                world.delete_entity(obelisk_ent);
            }
        })
    );
}

Ent instantiateSarcophageObelisk(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        SarcophageObelisk(),
        Sprite(textureManager, obeliskUV),
        Animation(obeliskAnim, ObeliskAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}