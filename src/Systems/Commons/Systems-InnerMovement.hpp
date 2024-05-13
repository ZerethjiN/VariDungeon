#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void innerMovementDownSys(World& world) {
    auto objs = world.view<InnerMovement, Transform>(with<InnerMovementDown>);

    auto [time] = world.getRes<const Time>();

    for (auto [ent, innerMovement, transform]: objs) {
        transform.moveYGlobal(innerMovement.getSpeed() * time.fixedDelta());

        if (innerMovement.canChangeDirection(time.fixedDelta())) {
            world.del<InnerMovementDown>(ent);
            world.add(ent, InnerMovementUp());
        }
    }
}

void innerMovementUpSys(World& world) {
    auto objs = world.view<InnerMovement, Transform>(with<InnerMovementUp>);

    auto [time] = world.getRes<const Time>();

    for (auto [ent, innerMovement, transform]: objs) {
        transform.moveYGlobal(-innerMovement.getSpeed() * time.fixedDelta());

        if (innerMovement.canChangeDirection(time.fixedDelta())) {
            world.del<InnerMovementUp>(ent);
            world.add(ent, InnerMovementDown());
        }
    }
}