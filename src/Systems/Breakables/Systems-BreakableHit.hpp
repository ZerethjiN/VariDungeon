#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void breakableNoHitSys(World& world) {
    auto breakables = world.view<Animation>(with<Breakable>, without<InvincibleFrame>);

    for (auto [_, animation]: breakables) {
        animation.play("NoHit");
    }
}

void breakableOnHitSys(World& world) {
    auto breakables = world.view<Animation>(with<Breakable, InvincibleFrame>);

    for (auto [_, animation]: breakables) {
        animation.play("Hit");
    }
}

void breakableHitSys(World& world) {
    auto breakables = world.view<Transform, Life, const OnCollisionEnter, const Transform>(with<Breakable>, without<InvincibleFrame>);

    for (auto [breakableEnt, transform, life, collisions, breakableTransform]: breakables) {
        for (auto othEnt: collisions) {
            if (world.has<PlayerWeapon>(othEnt)) {
                // Damage:
                life -= 1;

                // Visual Effect:
                world.add(breakableEnt, InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f)));
                transform.scale(-0.2f, -0.2f);

                // IsDead:
                if (life.isDead()) {
                    appliedCameraShake(world, 2.0f, 128.f, 2);

                    world.add(breakableEnt,
                        DustParticleGenerator(0.2, 2),
                        EnemyDropLoots(
                            {LootType::LOOT_TYPE_XP, LootType::LOOT_TYPE_XP},
                            0.2,
                            1
                        )
                    );
                } else {
                    appliedCameraShake(world, 2.0f, 64.f, 2);
                }

                break;
            }
        }
    }
}