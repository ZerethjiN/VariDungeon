#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

void testScene(SceneSystem, World&);

void testScene2(SceneSystem, World& world) {
    // Purge
    // auto [textureManager, fontManager, pipelineManager, time] = world.resource<TextureManager, FontManager, PipelineManager, Time>();
    // textureManager.clear();
    // fontManager.clear();
    // pipelineManager.clear();

    auto [spatialHashMap] = world.resource<SpatialHashMap>();
    spatialHashMap.clear();

    // AppState
    auto [appstate] = world.resource<AppState>();
    appstate.state = APP_STATE_HOME_MENU;

    // Reset Time
    auto [time] = world.resource<Time>();
    time.setTimeScale(1.0f);

    world.newEnt(
        AmbientLight(glm::vec4(255, 255, 255, 255))
    );

    // Camera
    auto cameraOrigin = world.newEnt(
        Transform(
            glm::vec2(0, 0),// + glm::vec2(160 * 2, 144 * 2),
            0,
            glm::vec2(1, 1)
        )
    );

    world.appendChildren(cameraOrigin, {
        // Camera
        world.newEnt(
            Transform(
                glm::vec2(0, 0),// + glm::vec2(160 * 2, 144 * 2),
                0,
                glm::vec2(1, 1)
            ),
            Camera(),
            CurCamera()
        )
    });

    // Background
    world.newEnt(
        UICreator(homeBackgroundUV, UIAnchor::CENTER_CENTER),
        Transform(
            glm::vec2(0, 0),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-10),
        HomeMenuBackgroundSlide(glm::vec2(-80, -72), glm::vec2(80, 72), 32.f)
    );

    // Logo
    world.newEnt(
        UICreator(logoUV, UIAnchor::CENTER_CENTER),
        Transform(
            glm::vec2(0, -44),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-9)
    );

    // Play Button
    world.newEnt(
        UICreator(homeButtonUV, 0, UIAnchor::CENTER_CENTER),
        Transform(
            glm::vec2(0, 0),
            0,
            glm::vec2(1.05f, 1.05f)
        ),
        ZIndex(-9),
        HomeMenuButtonId(0),
        HomeMenuSelectedButton(),
        HomeMenuButtonCallback([](World& world, Ent thisEnt) {
            world.loadScene(testScene);
        })
    );

    world.newEnt(
        TextUICreator("Play", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(96, 16), glm::vec4(255, 255, 255, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
        Transform(
            glm::vec2(-70, -8),
            0,
            glm::vec2(1.5, 1.5)
        ),
        ZIndex(-8)
    );

    // Settings Button
    world.newEnt(
        UICreator(homeButtonUV, 0, UIAnchor::CENTER_CENTER),
        Transform(
            glm::vec2(0, 40),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-9),
        HomeMenuButtonId(1)
    );

    world.newEnt(
        TextUICreator("Settings", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(96, 16), glm::vec4(255, 255, 255, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
        Transform(
            glm::vec2(-70, 32),
            0,
            glm::vec2(1.5, 1.5)
        ),
        ZIndex(-8)
    );

    // Selector
    world.newEnt(
        UICreator(homeButtonUV, 1, UIAnchor::CENTER_CENTER),
        Animation(homeButtonAnim, "LightSelector"),
        Transform(
            glm::vec2(0, 0),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-7),
        HomeMenuSelector(2, 0)
    );

    // Version Text
    auto [buildVersion] = world.resource<const BuildVersion>();

    world.newEnt(
        TextUICreator(std::string("Version ") + buildVersion.version, "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(96, 16), glm::vec4(255, 255, 255, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_RIGHT),
        Transform(
            glm::vec2(-16, 60),
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-8)
    );
}