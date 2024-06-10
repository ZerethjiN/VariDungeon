#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateVoidSphere(World& world, const glm::vec2& position) {
    return world.newEnt(
        VoidSphere(1.5f, 1.5f, 32.f),
        IsVoidSphereOff(1.5f),
        SpriteCreator(voidSphereUV),
        Animation(voidSphereAnim, "Off"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}