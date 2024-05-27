#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shurikenBonusCallbackLvl1(World& world) {
    auto players = world.view<const Transform>(with<Player>);

    for (auto [playerEnt, transform]: players) {
        world.appendChildren(playerEnt, {
            instantiateShurikenParticle(world, transform.getPosition() + glm::vec2(-16, 0), 64.f, glm::vec2(-16, 0)),
            instantiateShurikenParticle(world, transform.getPosition() + glm::vec2(+16, 0), 64.f, glm::vec2(16, 0)),
        });
    }
}