#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shurikenRotationSys(MainFixedSystem, World& world) {
    auto shurikens = world.view<Transform2D, const Shuriken>();

    auto [time] = world.resource<const Time>();

    for (auto [shurikenEnt, shurikenTransform, shuriken]: shurikens) {
        if (auto optParent = world.get_parent(shurikenEnt)) {
            auto parentEnt = optParent.value();

            if (auto opt = world.get_components<const Transform2D>(parentEnt)) {
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