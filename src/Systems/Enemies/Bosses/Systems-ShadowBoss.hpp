#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void shadowBossHubMovementSys(MainFixedSystem, World& world) {
    auto bosses = world.view<Velocity, ShadowBossHubPattern, const Speed, const Transform>();

    auto [time] = world.resource<const Time>();

    for (auto [bossEnt, velocity, shadowBoss, speed, transform]: bosses) {
        if (glm::distance(transform.getPosition(), shadowBoss.movePoints[shadowBoss.curPoint]) <= 4.f) {
            shadowBoss.curPoint++;
            if (shadowBoss.curPoint >= shadowBoss.movePoints.size()) {
                world.destroy(bossEnt);
                for (auto [kingEnt, kingTransform]: world.view<const Transform>(with<King>)) {
                    instantiateWarp(world, kingTransform.getPosition());
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(-24, 24));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(24, 40));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(-40, 72));
                    instantiateFragments(world, kingTransform.getPosition() + glm::vec2(56, 8));
                    world.destroy(kingEnt);
                }
                appliedCameraShake(world, 0.5f, 128.f, 2);
                appliedCurCameraAberation(world, 4, 0.1);
                for (auto [torchEnt, torchAnimation]: world.view<Animation>(with<TorchDecor, ParticleGenerator>)) {
                    torchAnimation.play("Off");
                    world.remove<ParticleGenerator>(torchEnt);
                }
            }
        } else {
            glm::vec2 newdirection = glm::normalize(shadowBoss.movePoints[shadowBoss.curPoint] - transform.getPosition());

            velocity += newdirection * speed.speed * time.fixedDelta();
        }
    }
}