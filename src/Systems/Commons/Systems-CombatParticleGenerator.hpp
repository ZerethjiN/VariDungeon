#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void combatParticleGeneratorSys(World& world) {
    auto generators = world.view<CombatParticleGenerator, const Transform, const ZIndex>();

    auto [time] = world.getRes<const Time>();

    for (auto [generatorEnt, generator, transform, zindex]: generators) {
        if (generator.canStop(time.fixedDelta())) {
            world.del<CombatParticleGenerator>(generatorEnt);
        }

        if (generator.canSpawnRepulseParticle(time.fixedDelta())) {
            instantiateRepulseCombatParticle(world, transform.getPosition(), zindex);
        }

        if (generator.canSpawnSmallParticle(time.fixedDelta())) {
            if (generator.getCurSmallParticle() % 2 == 0) {
                world.appendChildren(generatorEnt, {
                    instantiateSmallCombatParticle(world, transform.getPosition() + glm::vec2(8, 8), zindex)
                });
            } else {
                world.appendChildren(generatorEnt, {
                    instantiateSmallCombatParticle(world, transform.getPosition() + glm::vec2(-8, -8), zindex)
                });
            }
        }
    }
}