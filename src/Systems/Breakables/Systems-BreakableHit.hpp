#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void breakableOnHitSys(MainFixedSystem, World& world) {
    auto breakables = world.view<Animation, OnBreakableHitDuration>(with<Breakable>);

    auto [time] = world.resource<const Time>();

    for (auto [breakableEnt, animation, onBreakableHitduration]: breakables) {
        if (onBreakableHitduration.canSwitchState(time.fixedDelta())) {
            // animation.play(breakable.noHitAnimName);
            world.remove_component<OnBreakableHitDuration>(breakableEnt);

            if (auto onNoHitOpt = world.get<const OnBreakableNoHit>(breakableEnt)) {
                auto [onBreakableNoHit] = onNoHitOpt.value();

                onBreakableNoHit.callback(world, breakableEnt);
            }
        }
    }
}

void breakableHitSys(MainFixedSystem, World& world) {
    auto breakables = world.view<Transform2D, Life, Animation, ZIndex, const OnCollisionEnter, const Loots>(with<Breakable>, without<OnBreakableHitDuration, InvincibleFrame>);

    for (auto [breakableEnt, transform, life, animation, zindex, collisions, loots]: breakables) {
        for (auto othEnt: collisions) {
            if (world.has<PlayerWeapon>(othEnt) || world.has<EnemyWeaponForBreakables>(othEnt)) {
                // Damage:
                life -= 1;

                // Visual Effect:
                // animation.play(breakable.onHitAnimName);
                world.add_component(breakableEnt,
                    InvincibleFrame(0.25f, glm::vec2(-0.2f, -0.2f))
                );
                transform.scale(-0.2f, -0.2f);

                // IsDead:
                if (life.isDead()) {
                    appliedCameraShake(world, 0.5f, 128.f, 2);
                    appliedCurCameraAberation(world, 2, 0.1);

                    if (auto onBreakOpt = world.get<const OnBreakableBreak>(breakableEnt)) {
                        auto [onBreakableBreak] = onBreakOpt.value();

                        onBreakableBreak.callback(world, breakableEnt);
                    }

                    world.remove_component<Breakable, Life, Collider>(breakableEnt);
                    zindex = -3;
                    // animation.play(breakable.destroyedAnimName);

                    std::vector<std::size_t> newLoots;
                    if (!loots.empty()) {
                        auto rndLootType = rand() % loots.size();
                        const auto& loot = loots[rndLootType];
                        auto newNbLoots = (rand() % loot.minLootDrop) + (loot.maxLootDrop - loot.minLootDrop) + 1;
                        for (std::size_t i = 0; i < newNbLoots; i++) {
                            newLoots.emplace_back(loot.lootType);
                        }
                    }

                    world.add_component(breakableEnt,
                        DustParticleGenerator(false, 0.2, 2),
                        EnemyDropLoots(newLoots, 0.2, 1)
                    );
                } else {
                    appliedCameraShake(world, 0.5f, 128.f, 2);

                    world.add_component(breakableEnt, OnBreakableHitDuration(0.25f));

                    if (auto onHitOpt = world.get<const OnBreakableHit>(breakableEnt)) {
                        auto [onBreakableHit] = onHitOpt.value();

                        onBreakableHit.callback(world, breakableEnt);
                    }
                }

                break;
            }
        }
    }
}