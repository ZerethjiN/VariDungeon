#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void slimeMoveSys(World& world) {
    auto slimes = world.view<Velocity, Animation, Orientation, Slime, const Speed>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [slimeEnt, velocity, animation, orientation, slime, speed]: slimes) {
        if (slime.canChangeDirection(time.fixedDelta())) {
            switch (rand() % 4) {
                case 0: orientation = Orientation::NORTH; break;
                case 1: orientation = Orientation::SOUTH; break;
                case 2: orientation = Orientation::EAST; break;
                case 3: orientation = Orientation::WEST; break;
            }
        }

        velocity += orientation.orientation * speed.speed * time.fixedDelta();
        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
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
            if (orientation.y > 0) {
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