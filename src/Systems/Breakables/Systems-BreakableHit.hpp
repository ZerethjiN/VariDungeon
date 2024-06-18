#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void breakableOnHitSys(MainFixedSystem, World& world) {
    auto breakables = world.view<Animation, OnBreakableHit, const Breakable>();

    auto [time] = world.resource<const Time>();

    for (auto [breakableEnt, animation, onBreakableHit, breakable]: breakables) {
        if (onBreakableHit.canStop(time.fixedDelta())) {
            animation.play(breakable.getNoHitAnimName());
            world.remove<OnBreakableHit>(breakableEnt);
        }
    }
}

void breakableHitSys(MainFixedSystem, World& world) {
    auto breakables = world.view<Transform, Life, Animation, ZIndex, const OnCollisionEnter, const Transform, const Breakable, const Loots>(without<OnBreakableHit, InvincibleFrame>);

    for (auto [breakableEnt, transform, life, animation, zindex, collisions, breakableTransform, breakable, loots]: breakables) {
        for (auto othEnt: collisions) {
            if (world.has<PlayerWeapon>(othEnt)) {
                // Damage:
                life -= 1;

                // Visual Effect:
                animation.play(breakable.getOnHitAnimName());
                world.add(breakableEnt,
                    InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f))
                );
                transform.scale(-0.2f, -0.2f);

                // IsDead:
                if (life.isDead()) {
                    appliedCameraShake(world, 0.5f, 128.f, 2);
                    appliedCurCameraAberation(world, 2, 0.1);

                    if (auto onBreakOpt = world.get<const OnBreakableBreak>(breakableEnt)) {
                        auto [onBreakableBreak] = onBreakOpt.value();

                        onBreakableBreak.onBreak(world, breakableEnt);
                    }

                    world.remove<Breakable, Life, Collider>(breakableEnt);
                    zindex = -3;
                    animation.play(breakable.getDestroyedAnimName());

                    std::vector<std::size_t> newLoots;
                    if (!loots.empty()) {
                        auto rndLootType = rand() % loots.size();
                        const auto& loot = loots[rndLootType];
                        auto newNbLoots = (rand() % loot.minLootDrop) + (loot.maxLootDrop - loot.minLootDrop) + 1;
                        for (std::size_t i = 0; i < newNbLoots; i++) {
                            newLoots.emplace_back(loot.lootType);
                        }
                    }

                    world.add(breakableEnt,
                        DustParticleGenerator(false, 0.2, 2),
                        EnemyDropLoots(newLoots, 0.2, 1)
                    );
                } else {
                    appliedCameraShake(world, 0.5f, 128.f, 2);

                    world.add(breakableEnt, OnBreakableHit(0.25f));
                }

                break;
            }
        }
    }
}