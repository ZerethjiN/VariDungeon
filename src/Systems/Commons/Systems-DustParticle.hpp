#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void dustParticleSys(World& world) {
    auto generators = world.view<DustParticleGenerator, const Transform, const ZIndex>();

    auto [time] = world.getRes<const Time>();

    for (auto [generatorEnt, generator, transform, zindex]: generators) {
        if (generator.canStop(time.fixedDelta())) {
            if (generator.getNeedDestroy()) {
                world.destroy(generatorEnt);
            } else {
                world.del<DustParticleGenerator>(generatorEnt);
            }
        }

        if (generator.canSpawnParticle(time.fixedDelta())) {
            if (generator.getCurNbParticle() % 2 == 0) {
                world.appendChildren(generatorEnt, {
                    instantiateDustParticle(world, transform.getPosition() + glm::vec2(8, 8), zindex)
                });
            } else {
                world.appendChildren(generatorEnt, {
                    instantiateDustParticle(world, transform.getPosition() + glm::vec2(-8, -8), zindex)
                });
            }
        }
    }
}