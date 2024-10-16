#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void combatParticleGeneratorSys(MainFixedSystem, World& world) {
    auto generators = world.query<CombatParticleGenerator, const Transform2D, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [generatorEnt, generator, transform, zindex]: generators) {
        if (generator.canStop(time.fixedDelta())) {
            world.remove_components<CombatParticleGenerator>(generatorEnt);
        }

        if (generator.canSpawnRepulseParticle(time.fixedDelta())) {
            instantiateRepulseCombatParticle(world, transform.getPosition(), zindex);
        }

        if (generator.canSpawnSmallParticle(time.fixedDelta())) {
            if (generator.getCurSmallParticle() % 2 == 0) {
                world.append_children(generatorEnt, {
                    instantiateSmallCombatParticle(world, transform.getPosition() + glm::vec2(8, 8), zindex)
                });
            } else {
                world.append_children(generatorEnt, {
                    instantiateSmallCombatParticle(world, transform.getPosition() + glm::vec2(-8, -8), zindex)
                });
            }
        }
    }
}