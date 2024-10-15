#pragma once
#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void talentSphereOpenSys(MainUnscaledFixedSystem, World& world) {
    auto spheres = world.view<const OnCollisionEnter>(with<TalentSphere>);
    auto menus = world.view(with<Menu>);

    auto [time] = world.resource<Time>();

    if (menus.empty()) {
        for (auto [_, collisions]: spheres) {
            for (const auto& oth_ent: collisions) {
                if (world.has_components<Player>(oth_ent)) {
                    time.setTimeScale(0);
                    instantiateTalentSphereMenuUI(world, glm::vec2(-72, -64));
                }
            }
        }
    }
}

void talentSphererCloseSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<const Transform2D>(with<TalentSphereMenu>, without<TalentSphereMenuReverseTranslation, TalentSphereMenuTranslation>);

    if (!menus.empty() && vulkanEngine.window.isKeyDown(ButtonNameType::EXIT)) {
        for (auto [menu_ent, menuTransform]: menus) {
            world.add_components(menu_ent, TalentSphereMenuReverseTranslation(menuTransform.getPosition() + glm::vec2(0, 144), 512.f));
        }
    }
}

void talentSphereMenuTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const TalentSphereMenuTranslation>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [menuEnt, transform, talentSphereMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), talentSphereMenuTranslation.finalPosition) <= 4.f) {
            transform.setPositionGlobal(talentSphereMenuTranslation.finalPosition);

            world.remove_components<TalentSphereMenuTranslation>(menuEnt);
        } else {
            transform.move(glm::normalize(talentSphereMenuTranslation.finalPosition - transform.getPosition()) * talentSphereMenuTranslation.translationSpeed * time.unscaledFixedDelta());
        }
    }
}

void talentSphereMenuReverseTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const TalentSphereMenuReverseTranslation>();

    auto [time] = world.resource<Time>();

    for (auto [menuEnt, transform, talentSphereMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), talentSphereMenuTranslation.finalPosition) <= 4.f) {
            transform.setPositionGlobal(talentSphereMenuTranslation.finalPosition);

            world.delete_entity(menuEnt);
            time.setTimeScale(1.0f);
        } else {
            transform.move(glm::normalize(talentSphereMenuTranslation.finalPosition - transform.getPosition()) * talentSphereMenuTranslation.translationSpeed * time.unscaledFixedDelta());
        }
    }
}