#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void innerMovementDownSys(MainFixedSystem, World& world) {
    auto objs = world.query<InnerMovement, Transform2D>(with<InnerMovementDown>);

    auto [time] = world.resource<const Time>();

    for (auto [ent, innerMovement, transform]: objs) {
        transform.moveYGlobal(innerMovement.getSpeed() * time.fixedDelta());

        if (innerMovement.canChangeDirection(time.fixedDelta())) {
            world.remove_components<InnerMovementDown>(ent);
            world.add_components(ent, InnerMovementUp());
        }
    }
}

void innerMovementUpSys(MainFixedSystem, World& world) {
    auto objs = world.query<InnerMovement, Transform2D>(with<InnerMovementUp>);

    auto [time] = world.resource<const Time>();

    for (auto [ent, innerMovement, transform]: objs) {
        transform.moveYGlobal(-innerMovement.getSpeed() * time.fixedDelta());

        if (innerMovement.canChangeDirection(time.fixedDelta())) {
            world.remove_components<InnerMovementUp>(ent);
            world.add_components(ent, InnerMovementDown());
        }
    }
}