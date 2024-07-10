#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void homeMenuBackgroundSlideSys(MainFixedSystem, World& world) {
    auto backgrounds = world.view<Transform, HomeMenuBackgroundSlide>();

    auto [time] = world.resource<const Time>();

    for (auto [_, transform, slide]: backgrounds) {
        if (transform.getPosition().x <= slide.destination.x) {
            transform.setPosition(slide.rollbackDestination);
        }
        transform.move(glm::normalize(glm::vec2(-160, -144)) * slide.speed * time.unscaledFixedDelta());
    }
}

void homeMenuSelectorSys(MainFixedSystem, World& world) {
    auto selectors = world.view<HomeMenuSelector, const Transform>(without<HomeMenuSelectorMoveDown, HomeMenuSelectorMoveUp>);

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(MOVE_DOWN)) {
            if (selector.nextElement()) {
                world.add(selectorEnt, HomeMenuSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 40), 384.f));
                for (auto [curButtonEnt, transform]: world.view<Transform>(with<HomeMenuButtonId, HomeMenuSelectedButton>)) {
                    world.remove<HomeMenuSelectedButton>(curButtonEnt);
                    transform.scale(-0.05f, -0.05f);
                }
                for (auto [curButtonEnt, transform, buttonId]: world.view<Transform, const HomeMenuButtonId>(without<HomeMenuSelectedButton>)) {
                    if (buttonId.buttonId == selector.getCurElement()) {
                        world.add(curButtonEnt, HomeMenuSelectedButton());
                        transform.scale(0.05f, 0.05f);
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(MOVE_UP)) {
            if (selector.previousElement()) {
                world.add(selectorEnt, HomeMenuSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -40), 384.f));
                for (auto [curButtonEnt, transform]: world.view<Transform>(with<HomeMenuButtonId, HomeMenuSelectedButton>)) {
                    world.remove<HomeMenuSelectedButton>(curButtonEnt);
                    transform.scale(-0.05f, -0.05f);
                }
                for (auto [curButtonEnt, transform, buttonId]: world.view<Transform, const HomeMenuButtonId>(without<HomeMenuSelectedButton>)) {
                    if (buttonId.buttonId == selector.getCurElement()) {
                        world.add(curButtonEnt, HomeMenuSelectedButton());
                        transform.scale(0.05f, 0.05f);
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(VALIDATE)) {
            for (auto [curButtonEnt, callback]: world.view<HomeMenuButtonCallback>(with<HomeMenuSelectedButton>)) {
                callback.callback(world, curButtonEnt);
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::EXIT)) {
            vulkanEngine.window.close();
            world.stopRun();
        }
    }
}

void homeMenuSelectorMoveDownSys(MainFixedSystem, World& world) {
    auto selectors = world.view<Transform, const HomeMenuSelectorMoveDown>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, selector]: selectors) {
        if (glm::distance(transform.getPosition(), selector.destination) <= 4.f) {
            transform.setPosition(selector.destination);
            world.remove<HomeMenuSelectorMoveDown>(selectorEnt);
        } else {
            transform.moveY(selector.speed * time.unscaledFixedDelta());
        }
    }
}

void homeMenuSelectorMoveUpSys(MainFixedSystem, World& world) {
    auto selectors = world.view<Transform, const HomeMenuSelectorMoveUp>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, selector]: selectors) {
        if (glm::distance(transform.getPosition(), selector.destination) <= 4.f) {
            transform.setPosition(selector.destination);
            world.remove<HomeMenuSelectorMoveUp>(selectorEnt);
        } else {
            transform.moveY(-selector.speed * time.unscaledFixedDelta());
        }
    }
}