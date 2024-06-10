#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void turretCardinalSys(MainFixedSystem, World& world) {
    auto traps = world.view<IsTurretCardinal, Animation, const Transform, const Turret, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [trapEnt, isTurretCardinal, animation, transform, turret, zindex]: traps) {
        if (isTurretCardinal.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<Turret>(trapEnt);
                animation.play("TurretOff");
            } else {
                animation.play("TurretDiagonal");
                world.remove<IsTurretCardinal>(trapEnt);
                world.add(trapEnt, IsTurretDiagonal(turret.diagonalDuration, turret.diagonalPreShotDuration));
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, -1), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 1), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 1), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, -1), 64.f);
            }
        }
        if (isTurretCardinal.canPreShot(time.fixedDelta())) {
            for (int i = 1; i < 7; i++) {
                world.appendChildren(trapEnt, {
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, -16 * i), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, -16 * i), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                });
            }
        }
    }
}

void turretDiagonalSys(MainFixedSystem, World& world) {
    auto traps = world.view<IsTurretDiagonal, Animation, const Transform, const Turret, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [trapEnt, isTurretDiagonal, animation, transform, turret, zindex]: traps) {
        if (isTurretDiagonal.canSwitchState(time.fixedDelta())) {
            if (world.view(with<Enemy>).empty()) {
                world.remove<Turret>(trapEnt);
                animation.play("TurretOff");
            } else {
                animation.play("TurretCardinal");
                world.remove<IsTurretDiagonal>(trapEnt);
                world.add(trapEnt, IsTurretCardinal(turret.cardinalDuration, turret.cardinalPreShotDuration));
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(1, 0), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(-1, 0), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, 1), 64.f);
                instantiateFireBallParticle(world, transform.getPosition(), glm::vec2(0, -1), 64.f);
            }
        }
        if (isTurretDiagonal.canPreShot(time.fixedDelta())) {
            for (int i = 1; i < 7; i++) {
                world.appendChildren(trapEnt, {
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, 16 * i), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, -16 * i), zindex),
                });
            }
        }
    }
}
