#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void slimeMovementSys(World& world) {
    auto slimes = world.view<Velocity, Animation, const Speed, const Transform>(with<Slime>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.getRes<const Time>();

    for (auto [slimeEnt, velocity, animation, speed, slimeTransform]: slimes) {
        for (auto [_, playerTransform]: players) {
            auto newdirection = glm::normalize(playerTransform.getPosition() - slimeTransform.getPosition());
            velocity += newdirection * speed.speed * time.fixedDelta();
            if (fabs(newdirection.x) > fabs(newdirection.y)) {
                if (newdirection.x > 0) {
                    if (world.has<InvincibleFrame>(slimeEnt)) {
                        animation.play("HitMoveRight");
                    } else {
                        animation.play("MoveRight");
                    }
                } else {
                    if (world.has<InvincibleFrame>(slimeEnt)) {
                        animation.play("HitMoveLeft");
                    } else {
                        animation.play("MoveLeft");
                    }
                }
            } else {
                if (newdirection.y > 0) {
                    if (world.has<InvincibleFrame>(slimeEnt)) {
                        animation.play("HitMoveDown");
                    } else {
                        animation.play("MoveDown");
                    }
                } else {
                    if (world.has<InvincibleFrame>(slimeEnt)) {
                        animation.play("HitMoveUp");
                    } else {
                        animation.play("MoveUp");
                    }
                }
            }
        }
    }
}