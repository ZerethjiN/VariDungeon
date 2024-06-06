#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void damageTextSys(MainFixedSystem, World& world) {
    auto texts = world.view<Velocity, Transform, DamageText>();

    auto [time] = world.resource<const Time>();

    for (auto [textEnt, velocity, transform, text]: texts) {
        velocity.vel += text.direction * text.speed * time.fixedDelta();

        transform.scale(glm::vec2(text.maxScale, text.maxScale) / text.duration * time.fixedDelta());

        if (text.canDestroyText(time.fixedDelta())) {
            world.destroy(textEnt);
        }
    }
}