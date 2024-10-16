#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void healthBonusCallbackLvl1(BonusCallback, World& world) {
    auto players = world.query<Life>(with<Player>);

    for (auto [_, life]: players) {
        life.increaseMaxLife(life.getNbLife() * 0.25f);

        if (life.getCurNbShield() > 0) {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[3]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("Shield " + std::to_string(static_cast<int>(life.getCurNbShield())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbShield() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        } else {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[2]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getCurNbLife())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbLife() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        }
    }
}

void healthBonusCallbackLvl2(BonusCallback, World& world) {
    auto players = world.query<Life>(with<Player>);

    for (auto [_, life]: players) {
        life.increaseMaxLife(life.getNbLife() * 0.25f);

        if (life.getCurNbShield() > 0) {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[3]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("Shield " + std::to_string(static_cast<int>(life.getCurNbShield())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbShield() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        } else {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[2]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getCurNbLife())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbLife() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        }
    }
}

void healthBonusCallbackLvl3(BonusCallback, World& world) {
    auto players = world.query<Life>(with<Player>);

    for (auto [_, life]: players) {
        life.increaseMaxLife(life.getNbLife() * 0.25f);

        if (life.getCurNbShield() > 0) {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[3]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("Shield " + std::to_string(static_cast<int>(life.getCurNbShield())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbShield() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        } else {
            for (auto [_, lifeIcon]: world.query<UI>(with<LifeIconInventoryBar>)) {
                lifeIcon.setTextureRect(HUDElementsUV[2]);
            }

            for (auto [_, lifeTextUI]: world.query<TextUI>(with<PlayerLifeText>)) {
                lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getCurNbLife())) + "/" + std::to_string(static_cast<int>(life.getNbLife())));
            }

            auto lifeRatio = life.getCurNbLife() / life.getNbLife();

            for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.query<UI, const PlayerLifeBarInner>()) {
                lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
            }
        }
    }
}