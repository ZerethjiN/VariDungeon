#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shurikenRotationSys(MainFixedSystem, World& world) {
    auto shurikens = world.view<Transform, const Shuriken>();

    auto [time] = world.resource<const Time>();

    for (auto [shurikenEnt, shurikenTransform, shuriken]: shurikens) {
        if (auto optParent = world.getParent(shurikenEnt)) {
            auto parentEnt = optParent.value();

            if (auto opt = world.get<const Transform>(parentEnt)) {
                auto [parentTransform] = opt.value();

                auto diff = parentTransform.getPosition() - shurikenTransform.getPosition();

                shurikenTransform.rotate(shuriken.rotationSpeed * time.fixedDelta());

                shurikenTransform.move(
                    rotateAround(-diff, diff, shuriken.rotationSpeed * time.fixedDelta())
                );
            }
        }
    }
}