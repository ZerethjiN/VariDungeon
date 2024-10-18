#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shurikenBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<const Transform2D>(with<Player>);

    for (auto [playerEnt, transform]: players) {
        world.append_children(playerEnt, {
            instantiateShurikenParticle(world, transform.getPosition() + glm::vec2(-16, 0), 64.f, glm::vec2(-16, 0)),
            instantiateShurikenParticle(world, transform.getPosition() + glm::vec2(+16, 0), 64.f, glm::vec2(16, 0)),
        });
    }
}