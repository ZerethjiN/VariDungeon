#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void particleGeneratorSys(MainFixedSystem, World& world) {
    auto generators = world.query<ParticleGenerator, const Transform2D>();

    auto [time] = world.resource<const Time>();

    for (auto [generatorEnt, generator, transform]: generators) {
        if (generator.canSpawnParticle(time.fixedDelta())) {
            auto rndX = (rand() % static_cast<int>(generator.radius * 2)) - generator.radius;
            auto rndY = (rand() % static_cast<int>(generator.radius * 2)) - generator.radius;
            generator(world, transform.getPosition() + generator.offset + glm::vec2(rndX, rndY));
        }
    }
}