#pragma once

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "ImageAsset.hpp"
#include "TextureManager.hpp"
#include "Sprite.hpp"

#include "../ZerengineCommon.hpp"

class ParticleSystemData final {
friend void particleSystems(World& world);
public:
    enum class ParticleGeneratorMode: std::uint8_t {
        ONE_SHOT,
        LOOP
    };

public:
    ParticleSystemData(
        float newGeneratorDuration,
        ParticleGeneratorMode newGeneratorMode,
        const std::initializer_list<float>& newParticleGenerationCooldown,
        const ImageAsset& newImageAsset,
        float newParticleLifeTime,
        const std::initializer_list<float>& newParticleSpeed,
        const glm::ivec2& newDirectionInfSup,
        const std::initializer_list<glm::vec4>& newParticleColors
    ):
        generatorDuration(newGeneratorDuration),
        curGeneratorDurationTime(0),
        generatorMode(newGeneratorMode),
        particleGenerationCooldown(newParticleGenerationCooldown),
        curParticleGenerationIndex(0),
        curParticleGenerationTime(0),
        imageAsset(newImageAsset),
        particleLifeTime(newParticleLifeTime),
        particleSpeed(newParticleSpeed),
        directionInfSup(newDirectionInfSup),
        particleColors(newParticleColors),
        useLight(false) {
    }

public:
    bool isGeneratorEndOfLife(float delta) {
        curGeneratorDurationTime += delta;
        if (curGeneratorDurationTime >= generatorDuration) {
            if (generatorMode == ParticleGeneratorMode::ONE_SHOT) {
                return true;
            }
            curGeneratorDurationTime -= generatorDuration;
        }
        return false;
    }

    bool canSpawnANewParticle(float delta) {
        curParticleGenerationTime += delta;
        if (curParticleGenerationTime >= particleGenerationCooldown[curParticleGenerationIndex]) {
            curParticleGenerationTime -= particleGenerationCooldown[curParticleGenerationIndex];
            curParticleGenerationIndex = rand() % particleGenerationCooldown.size();
            return true;
        }
        return false;
    }

private:
    // Generator infos:
    float generatorDuration;
    float curGeneratorDurationTime;
    ParticleGeneratorMode generatorMode;
    std::vector<float> particleGenerationCooldown;
    std::size_t curParticleGenerationIndex;
    float curParticleGenerationTime;

    // Particles infos:
    const ImageAsset& imageAsset;
    float particleLifeTime;
    std::vector<float> particleSpeed;
    glm::ivec2 directionInfSup;
    std::vector<glm::vec4> particleColors;
    // alpha over life

    // Particles Lights:
    bool useLight;
    std::vector<float> lightRadius;
    std::vector<glm::vec4> lightColors;
    std::vector<float> lightIntensities;
};

// class ParticleGenerator {
// friend void particleSystems(World& world);
// public:
//     ParticleGenerator(const std::initializer_list<ParticleSystemData>& newDatas):
//         datas(newDatas) {
//     }

// public:
//     void add(const ParticleSystemData& newData) {
//         datas.emplace_back(newData);
//     }

//     void erase(std::size_t idx) {
//         datas.erase(datas.begin() + idx);
//     }

//     [[nodiscard]] std::vector<ParticleSystemData>::iterator begin() noexcept {
//         return datas.begin();
//     }

//     [[nodiscard]] std::vector<ParticleSystemData>::iterator end() noexcept {
//         return datas.end();
//     }

// private:
//     std::vector<ParticleSystemData> datas;
// };

///////////////////////////////////////////////////////////////////////////////////

class GeneratorParticle final  {
public:
    GeneratorParticle(float newSpeed, const glm::vec2& newDirection):
        speed(newSpeed),
        direction(newDirection) {
    }

public:
    float speed;
    glm::vec2 direction;
};

///////////////////////////////////////////////////////////////////////////////////

// void particleSystems(World& world) {
//     auto generators = world.view<ParticleGenerator, const Transform2D>();

//     auto [time] = world.getRes<const Time>();

//     for (auto [generatorEnt, generator, transform]: generators) {
//         for (auto& particleSystem: generator) {
//             if (particleSystem.isGeneratorEndOfLife(time.fixedDelta())) {
//                 generator.erase(particleSystem);
//                 break;
//             }
//             if (particleSystem.canSpawnANewParticle(time.fixedDelta())) {
//                 world.newEnt(
//                     SpriteCreator(particleSystem.imageAsset, particleSystem.particleColors[rand() % particleSystem.particleColors.size()]),
//                     Transform2D(
//                         transform.getPosition(),
//                         0,
//                         glm::vec2(1, 1)
//                     ),
//                     LifeTime(particleSystem.particleLifeTime),
//                     Velocity(),
//                     GeneratorParticle(
//                         particleSystem.particleSpeed[rand() % particleSystem.particleSpeed.size()],
//                         rotateAround(transform.getPosition(), glm::vec2(0, 0), rand() % 360)
//                     )
//                 );
//             }
//         }
//     }
// }

void generatorParticleMovement(World& world) {
    auto particles = world.view<Velocity, const GeneratorParticle>();

    auto [time] = world.resource<const Time>();

    for (auto [_, velocity, particle]: particles) {
        velocity = particle.direction * particle.speed * time.fixedDelta();
    }
}

///////////////////////////////////////////////////////////////////////////////////