#pragma once

#include <Zerengine.hpp>

class ParticleGenerator final {
public:
    ParticleGenerator(Ent(*const newParticlePrefab)(World&, const glm::vec2&), float newCooldown, float newRadius, const glm::vec2& newOffset = glm::vec2(0, 0)):
        radius(newRadius),
        offset(newOffset),
        particlePrefab(newParticlePrefab),
        cooldown(newCooldown),
        curTime(0) {
    }

    bool canSpawnParticle(float delta) {
        curTime += delta;
        if (curTime >= cooldown) {
            curTime -= cooldown;
            return true;
        }
        return false;
    }

    ParticleGenerator& operator()(World& world, const glm::vec2& position) {
        particlePrefab(world, position);
        return *this;
    }

public:
    const float radius;
    const glm::vec2 offset;

private:
    Ent(*const particlePrefab)(World&, const glm::vec2&);
    const float cooldown;
    float curTime;
};