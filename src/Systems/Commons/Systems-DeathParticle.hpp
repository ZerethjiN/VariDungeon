#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void deathParticleSys(MainFixedSystem, World& world) {
    auto generators = world.view<DeathParticleGenerator, const Transform2D, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [generatorEnt, generator, transform, zindex]: generators) {
        if (generator.canStop(time.fixedDelta())) {
            if (generator.getNeedDestroy()) {
                world.delete_entity(generatorEnt);
            } else {
                world.remove_component<DeathParticleGenerator>(generatorEnt);
            }
        }

        if (generator.canSpawnParticle(time.fixedDelta())) {
            if (generator.getCurNbParticle() % 2 == 0) {
                world.append_children(generatorEnt, {
                    instantiateDeathParticle(world, transform.getPosition() + glm::vec2(8, 8), zindex)
                });
            } else {
                world.append_children(generatorEnt, {
                    instantiateDeathParticle(world, transform.getPosition() + glm::vec2(-8, -8), zindex)
                });
            }
        }
    }
}