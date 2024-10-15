#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void playerHitSys(MainFixedSystem, World& world) {
    auto players = world.view<Transform2D, Life, const OnCollisionEnter>(with<Player>, without<Unhittable, InvincibleFrame>);

    for (auto [playerEnt, playerTransform, life, collisions]: players) {
        for (auto othEnt: collisions) {
            if (world.has_components<EnemyWeapon, Damage>(othEnt)) {
                // Damage:
                if (auto opt = world.get_components<const Damage>(othEnt)) {
                    auto [damage] = opt.value();

                    life -= damage;
                }

                // Visual Effect:
                world.add_components(playerEnt, InvincibleFrame(0.5f, glm::vec2(-0.2f, -0.2f)));
                playerTransform.scale(-0.2f, -0.2f);

                if (auto opt = world.get_components<const Transform2D>(othEnt)) {
                    auto [enemyTransform] = opt.value();

                    world.add_components(playerEnt,
                        Knockback(0.15f, -glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()), 192.f),
                        CombatParticleGenerator(0.15f, 3, 2)
                    );
                }

                // Refresh Life Bar:
                if (life.getCurNbShield() > 0) {
                    for (auto [_, lifeIcon]: world.view<UI>(with<LifeIconInventoryBar>)) {
                        lifeIcon.setTextureRect(HUDElementsUV[3]);
                    }

                    for (auto [_, lifeTextUI]: world.view<TextUI>(with<PlayerLifeText>)) {
                        lifeTextUI.setString("Shield " + std::to_string(static_cast<int>(life.getCurNbShield())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
                    }

                    auto lifeRatio = life.getCurNbShield() / life.getNbLife();

                    for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.view<UI, const PlayerLifeBarInner>()) {
                        lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
                    }
                } else {
                    for (auto [_, lifeIcon]: world.view<UI>(with<LifeIconInventoryBar>)) {
                        lifeIcon.setTextureRect(HUDElementsUV[2]);
                    }

                    for (auto [_, lifeTextUI]: world.view<TextUI>(with<PlayerLifeText>)) {
                        lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getCurNbLife())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
                    }

                    auto lifeRatio = life.getCurNbLife() / life.getNbLife();

                    for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.view<UI, const PlayerLifeBarInner>()) {
                        lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
                    }
                }

                // IsDead:
                if (life.isDead()) {
                    world.delete_entity(playerEnt);
                    world.loadScene(hubScene);
                } else {
                    appliedCameraShake(world, 0.5f, 128.f, 2);
                    appliedCurCameraAberation(world, 4, 0.1);
                }

                break;
            }
        }
    }
}