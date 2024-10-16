#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void torchIdleSys(MainFixedSystem, World& world) {
    auto traps = world.query<IsTorchIdle, Animation, Orientation, const Transform2D, const Torch, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [trapEnt, isTorchIdle, animation, orientation, transform, torch, zindex]: traps) {
        if (isTorchIdle.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<Torch, ParticleGenerator>(trapEnt);
                animation.play(TorchAnimType::OFF);
            } else {
                world.remove_components<IsTorchIdle>(trapEnt);
                world.add_components(trapEnt, IsTorchCast(torch.castDuration));
                glm::vec2 newdirection;
                for (auto [_, playerTransform]: world.query<const Transform2D>(with<Player>)) {
                    newdirection = glm::normalize(playerTransform.getPosition() - transform.getPosition());
                    for (int i = 1; i < 7; i++) {
                        if (fabs(newdirection.x) > fabs(newdirection.y)) {
                            if (newdirection.x > 0) {
                                orientation = Orientation::EAST;
                                world.append_children(trapEnt, {
                                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 0), zindex)
                                });
                            } else {
                                orientation = Orientation::WEST;
                                world.append_children(trapEnt, {
                                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 0), zindex)
                                });
                            }
                        } else {
                            if (newdirection.y > 0) {
                                orientation = Orientation::SOUTH;
                                world.append_children(trapEnt, {
                                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, 16 * i), zindex)
                                });
                            } else {
                                orientation = Orientation::NORTH;
                                world.append_children(trapEnt, {
                                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, -16 * i), zindex)
                                });
                            }
                        }
                    }
                }
            }
        }
    }
}

void torchCastSys(MainFixedSystem, World& world) {
    auto traps = world.query<IsTorchCast, Animation, const Transform2D, const Orientation, const Torch>();

    auto [time] = world.resource<const Time>();

    for (auto [trapEnt, isTorchCast, animation, transform, orientation, torch]: traps) {
        if (isTorchCast.canSwitchState(time.fixedDelta())) {
            if (world.query(with<Enemy>).empty()) {
                world.remove_components<Torch, ParticleGenerator>(trapEnt);
                animation.play(TorchAnimType::OFF);
            } else {
                world.remove_components<IsTorchCast>(trapEnt);
                world.add_components(trapEnt, IsTorchIdle(torch.idleDuration));
                instantiateFireBallParticle(world, transform.getPosition(), orientation, 128.f);
            }
        }
    }
}