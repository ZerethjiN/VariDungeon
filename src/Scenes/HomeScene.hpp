#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>

void homeScene(World& world) {
    // Purge
    auto [textureManager, fontManager, pipelineManager, time] = world.getRes<TextureManager, FontManager, PipelineManager, Time>();
    textureManager.clear();
    fontManager.clear();
    pipelineManager.clear();

    // Reset Time
    time.setTimeScale(1.0f);

    auto mainButtonEnt = world.newEnt(
        UICreator(mainButtonUV, UIAnchor::CENTER_CENTER),
        Animation(mainButtonAnim, "Inactive"),
        Transform(
            glm::vec2(0, 0),
            0,
            glm::vec2(1, 1)
        ),
        MainButton(
            /*Speed:*/ 0.025,
            /*GrowDuration:*/ 0.8
        ),
        OnClickButton(
            glm::vec4(-40, -16, 80, 32),
            [](World& world, Ent selfEnt) {
                world.loadScene(testScene);
            }
        ),
        OnHoverButton(
            glm::vec4(-40, -16, 80, 32),
            [](World& world, Ent selfEnt) {
                if (auto opt = world.get<Animation, Transform>(selfEnt)) {
                    auto [anim, transform] = opt.value();
                    anim.play("Active");
                    transform.scale(glm::vec2(0.1, 0.1));
                }
                if (auto childrenObj = world.getChildren(selfEnt)) {
                    for (const auto childEnt: childrenObj.value().get()) {
                        if (auto opt = world.get<TextUI, Transform, MainButtonText1>(childEnt)) {
                            auto [textUI, transform, _] = opt.value();
                            textUI.setColor(glm::vec4(255, 255, 255, 255));
                            transform.move(0, -1);
                        }
                    }
                }
            },
            [](World& world, Ent selfEnt) {
                if (auto opt = world.get<Animation, Transform>(selfEnt)) {
                    auto [anim, transform] = opt.value();
                    anim.play("Inactive");
                    transform.scale(glm::vec2(-0.1, -0.1));
                }
                if (auto childrenObj = world.getChildren(selfEnt)) {
                    for (const auto childEnt: childrenObj.value().get()) {
                        if (auto opt = world.get<TextUI, Transform, MainButtonText1>(childEnt)) {
                            auto [textUI, transform, _] = opt.value();
                            textUI.setColor(glm::vec4(127, 127, 127, 255));
                            transform.move(0, +1);
                        }
                    }
                }
            }
        )
    );

    auto mainButtonText1Ent = world.newEnt(
        TextUICreator("Jouer", "Fonts/Zepto-Regular.ttf", 16, UIAnchor::CENTER_CENTER, glm::vec2(80, 32), glm::vec4(127, 127, 127, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
        Transform(
            glm::vec2(-36, -12),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(5),
        MainButtonText1()
    );

    auto mainButtonText2Ent = world.newEnt(
        TextUICreator("Jouer", "Fonts/Zepto-Regular.ttf", 16, UIAnchor::CENTER_CENTER, glm::vec2(80, 32), glm::vec4(0, 0, 0, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
        Transform(
            glm::vec2(-36, -12),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(2)
    );

    world.appendChildren(mainButtonEnt, {mainButtonText1Ent, mainButtonText2Ent});
}