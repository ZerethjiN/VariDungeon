#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void damageTextSys(World& world) {
    auto texts = world.view<Velocity, Transform, DamageText>();

    auto [time] = world.getRes<const Time>();

    for (auto [textEnt, velocity, transform, text]: texts) {
        velocity.vel += text.direction * text.speed * time.fixedDelta();

        if (time.getTimeScale() != 0) {
            transform.scale(glm::vec2((text.maxScale - 0.5) * text.duration, (text.maxScale - 0.5) * text.duration));
        }

        if (text.canDestroyText(time.fixedDelta())) {
            world.destroy(textEnt);
        }
    }
}