#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shadowMinionSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, Orientation, const Speed, const Transform2D>(with<ShadowMinion>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, velocity, animation, orientation, speed, enemy_transform]: enemies) {
        glm::vec2 new_direction;
        for (auto [_, player_transform]: players) {
            new_direction = glm::normalize(player_transform.getPosition() - enemy_transform.getPosition());
        }

        velocity += new_direction * speed.speed * time.fixedDelta();
        if (fabs(new_direction.x) > fabs(new_direction.y)) {
            if (new_direction.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowMinionAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(ShadowMinionAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowMinionAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(ShadowMinionAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (new_direction.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowMinionAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(ShadowMinionAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemy_ent)) {
                    animation.play(ShadowMinionAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(ShadowMinionAnimType::MOVE_UP);
                }
            }
        }
    }
}