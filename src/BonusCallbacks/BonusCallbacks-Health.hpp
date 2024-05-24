#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void healthBonusCallbackLvl1(World& world) {
    auto players = world.view<Life>(with<Player>);

    for (auto [_, life]: players) {
        life.increaseMaxLife(life.getCurNbLife() * 0.25f);

        for (auto [_, lifeTextUI]: world.view<TextUI>(with<PlayerLifeText>)) {
            lifeTextUI.setString("HP " + std::to_string(static_cast<int>(life.getNbLife())) + "/" + std::to_string(static_cast<int>(life.getCurNbLife())));
        }

        auto lifeRatio = life.getCurNbLife() / life.getNbLife();

        for (auto [_, lifeInnerBarUI, lifeInnerBar]: world.view<UI, const PlayerLifeBarInner>()) {
            lifeInnerBarUI.setTextureRect(glm::vec4(0, 16, static_cast<unsigned int>(lifeRatio * lifeInnerBar.getMaxLength()), 8));
        }
    }
}