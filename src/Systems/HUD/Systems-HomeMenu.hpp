#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void homeMenuBackgroundSlideSys(MainFixedSystem, World& world) {
    auto backgrounds = world.query<Transform2D, HomeMenuBackgroundSlide>();

    auto [time] = world.resource<const Time>();

    for (auto [_, transform, slide]: backgrounds) {
        if (transform.getPosition().x <= slide.destination.x) {
            transform.setPosition(slide.rollbackDestination);
        }
        transform.move(glm::normalize(glm::vec2(-160, -144)) * slide.speed * time.unscaledFixedDelta());
    }
}

void homeMenuSelectorSys(MainFixedSystem, World& world) {
    auto selectors = world.query<HomeMenuSelector, const Transform2D>(without<HomeMenuSelectorMoveDown, HomeMenuSelectorMoveUp>);

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_DOWN)) {
            if (selector.nextElement()) {
                world.add_components(selectorEnt, HomeMenuSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 40), 384.f));
                for (auto [curButtonEnt, transform]: world.query<Transform2D>(with<HomeMenuButtonId, HomeMenuSelectedButton>)) {
                    world.remove_components<HomeMenuSelectedButton>(curButtonEnt);
                    transform.scale(-0.05f, -0.05f);
                }
                for (auto [curButtonEnt, transform, buttonId]: world.query<Transform2D, const HomeMenuButtonId>(without<HomeMenuSelectedButton>)) {
                    if (buttonId.buttonId == selector.getCurElement()) {
                        world.add_components(curButtonEnt, HomeMenuSelectedButton());
                        transform.scale(0.05f, 0.05f);
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_UP)) {
            if (selector.previousElement()) {
                world.add_components(selectorEnt, HomeMenuSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -40), 384.f));
                for (auto [curButtonEnt, transform]: world.query<Transform2D>(with<HomeMenuButtonId, HomeMenuSelectedButton>)) {
                    world.remove_components<HomeMenuSelectedButton>(curButtonEnt);
                    transform.scale(-0.05f, -0.05f);
                }
                for (auto [curButtonEnt, transform, buttonId]: world.query<Transform2D, const HomeMenuButtonId>(without<HomeMenuSelectedButton>)) {
                    if (buttonId.buttonId == selector.getCurElement()) {
                        world.add_components(curButtonEnt, HomeMenuSelectedButton());
                        transform.scale(0.05f, 0.05f);
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::VALIDATE)) {
            for (auto [curButtonEnt, callback]: world.query<HomeMenuButtonCallback>(with<HomeMenuSelectedButton>)) {
                callback.callback(world, curButtonEnt);
            }
        } else if (vulkanEngine.window.isKeyUp(ButtonNameType::EXIT)) {
            vulkanEngine.window.close();
            world.stop_run();
        }
    }
}

void homeMenuSelectorMoveDownSys(MainFixedSystem, World& world) {
    auto selectors = world.query<Transform2D, const HomeMenuSelectorMoveDown>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, selector]: selectors) {
        if (glm::distance(transform.getPosition(), selector.destination) <= 4.f) {
            transform.setPosition(selector.destination);
            world.remove_components<HomeMenuSelectorMoveDown>(selectorEnt);
        } else {
            transform.moveY(selector.speed * time.unscaledFixedDelta());
        }
    }
}

void homeMenuSelectorMoveUpSys(MainFixedSystem, World& world) {
    auto selectors = world.query<Transform2D, const HomeMenuSelectorMoveUp>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, selector]: selectors) {
        if (glm::distance(transform.getPosition(), selector.destination) <= 4.f) {
            transform.setPosition(selector.destination);
            world.remove_components<HomeMenuSelectorMoveUp>(selectorEnt);
        } else {
            transform.moveY(-selector.speed * time.unscaledFixedDelta());
        }
    }
}