#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shadowMarkPreExplosionSys(MainFixedSystem, World& world) {
    auto marks = world.view<Animation, IsShadowMarkPreExplosion, const ShadowMark>();

    auto [time] = world.resource<const Time>();

    for (auto [markEnt, animation, preExplosion, shadowMark]: marks) {
        if (preExplosion.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsShadowMarkPreExplosion>(markEnt);
            world.add_component(markEnt,
                IsShadowMarkExplosion(shadowMark.explosionDuration),
                Trigger(-40 / 2, -40 / 2, 40, 40)
            );
            animation.play(ShadowMarkParticleAnimType::EXPLOSION);
        }
    }
}

void shadowMarkExplosionSys(MainFixedSystem, World& world) {
    auto marks = world.view<IsShadowMarkExplosion>();

    auto [time] = world.resource<const Time>();

    for (auto [markEnt, explosion]: marks) {
        if (explosion.canSwitchState(time.fixedDelta())) {
            world.delete_entity(markEnt);
        }
    }
}