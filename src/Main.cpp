#define DISPLAY_FPS
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_VULKAN
#include <unordered_map>
#include <any>
#include <concepts>
#include <unordered_set>
#include <variant>

#include <Zerengine.hpp>
#include <Interfaces.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <Scenes.hpp>
#include <Systems.hpp>
#include <Pipelines.hpp>
#include <FrameBuffers.hpp>
#include <Render.hpp>
#include <StartSystems.hpp>

void pollEventsSys(MainFixedSystem, World& world) {
    vulkanEngine.window.pollEvents();

    if (!vulkanEngine.window.isOpen()) {
        vulkanEngine.window.close();
        world.stopRun();
    }
}

int main() {
    try {
        ZerEngine()
            .useMultithreading(false)
            .setFixedTimeStep(0.02f)
            .addResource<BuildVersion>("0.0.1R")
            .addResource<PipelineManager>()
            .addResource<FrameBufferManager>()
            .addResource<TextureManager>()
            .addResource<FontManager>()
            .addResource<SpatialHashMap>()
            .addResource<LayerBasedCollisions>()
            .addResource<InGameView>(glm::vec4(0, 0, 160, 144))
            .addResource<UIView>(glm::vec4(0, 0, 160, 144))
            .addResource<AppState>(APP_STATE_HOME_MENU)
            .addStartSystems(startSys)
            .addMainFixedSystems({
                pollEventsSys
            })
            .addMainFixedConditionSystems(
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_HOME_MENU;
                },
                {
                    cameraSys,
                    homeMenuBackgroundSlideSys, homeMenuSelectorSys, homeMenuSelectorMoveDownSys, homeMenuSelectorMoveUpSys
                }
            )
            .addMainFixedConditionSystems(
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_IN_GAME;
                },
                {
                barbarianMovementSys, barbarianStartAttackSys, barbarianStopAttackSys, barbarianStartDashSys, barbarianStopDashSys,
                playerLootSys, playerLootAttractSys, playerHitSys, playerFrenzySys,
                breakableHitSys, breakableOnHitSys,
                enemyHitSys, enemyDropLootsSys,
                shurikenRotationSys, cameraAberationSys, cameraEffectApplicationSys,
                invincibleFramesSys, knockbackSys, damageTextSys, combatParticleGeneratorSys, deathParticleSys,
                lootSpreadSys, cameraSys, innerMovementDownSys, innerMovementUpSys, dustParticleSys,
                doorTriggerSys, openDoorSys, doorCameraMovementSys, playerAttackWeightSys,
                playerDaggerSys, daggerMovementSys, laserMovementSys, laserHitSys, playerLaserSys,
                warpSys, particleGeneratorSys, bombSpreadSys, rerollSys,
                
                // Attacks:
                shadowMarkPreExplosionSys, shadowMarkExplosionSys,
                groundCrystalAttackCrossSys,
                playerBombSys, playerBombExplosionSys,
                smallCrystalRotationSys, smallCrystalThrowSys,
                megaLaserRotationSys,
                playerLightningBallSys, lightballMovementSys, lightningBallHitSys,

                // Enemies:
                enemyPreSpawnSys,
                slimeMoveSys,
                anubisMoveSys, anubisAttackSys,
                batMoveSys, batAttackSys,
                lavaSlimeMoveSys, lavaSlimeAttackSys,
                robobouleMoveSys, roboboulePreAttackSys,
                rockInsectMoveSys, rockInsectPreCastSys, rockInsectCastSys,
                voidSlimeMoveSys, voidSlimeAttractSys,
                miniRockSpawnerSys, miniRockMoveSys,
                scorpionMoveSys, scorpionAttackSys,

                // Enemies Lvl2:
                mummyLvl2MoveSys, mummyLvl2PreAttackSys, mummyLvl2AttackSys,
                batLvl2MoveSys, batLvl2AttackSys,
                slimeLvl2MoveSys, slimeLvl2JumpSys,
                anubisLvl2AttackSys, anubisLvl2VanishSys,

                // Bosses:
                megaSlimeMoveSys, megaSlimeFireballSys, megaSlimeBounceSys, megaSlimeSpawnSys,
                rockBossRollSys, rockBossStunSys, rockBossGroundCrystalsSys, rockBossSmallCrystalThrowSys, rockBossGroundCrystalsP2Sys, rockBossRollP2Sys,
                sarcophageShadowMarkSys, sarcophagePreLaserSys, sarcophageLaserSys, sarcophageObeliskSys, sarcophageShockwaveSys,
                golemRockAttackSys, golemRockSys, golemPreFootAttackSys, golemFootAttackSys, golemPreLaserAttackCardinalSys, golemLaserAttackCardinalSys, golemPreLaserAttackDiagonalSys, golemLaserAttackDiagonalSys,

                fireBallAttackSys, fireBallHitSys,

                // GroundItems:
                getBonusSphereSys,

                // Traps:
                spikeDownSys, spikeUpSys,
                voidSphereOffSys, voidSphereOnSys,
                torchIdleSys, torchCastSys,
                turretCardinalSys, turretDiagonalSys,

                // HUD
                levelUpKnockbackSys,
                levelUpPreMenuSys, menuBonusTranslationSys, menuBonusReverseTranslationSys, menuBonusSelectorSys, inventoryBarShrinkSys,
                menuBonusSelectorMoveDownSys, menuBonusSelectorMoveUpSys, MenuBonusCurSelectedRowScaleSys,
                pauseMenuOpenCloseSys, pauseMenuTranslationSys, pauseMenuReverseTranslationSys, pauseMenuSelectorSys
            })

            // Enemies Lvl1 Threads
            .addThreadedFixedConditionSystems( // Mummy Threads
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_IN_GAME && !world.view(with<Mummy>).empty();
                },
                {mummyMoveSys, mummyPreAttackSys, mummyAttackSys}
            )
            .addThreadedFixedConditionSystems( // Insect Threads
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_IN_GAME && !world.view(with<Insect>).empty();
                },
                {insectMoveSys, insectAttackSys}
            )
            .addThreadedFixedConditionSystems( // Gasterolcan Threads
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_IN_GAME && !world.view(with<Gasterolcan>).empty();
                },
                {gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys}
            )
            .addThreadedFixedConditionSystems( // Spectre Threads
                [](World& world) -> bool {
                    auto [appstate] = world.resource<const AppState>();
                    return appstate.state == APP_STATE_IN_GAME && !world.view(with<Spectre>).empty();
                },
                {spectreMoveSys, spectreVanishSys, spectreCastSys}
            )

            .addMainFixedSystems({
                // particleSystems, generatorParticleMovement,
                lifeTimeSys, unscaledLifeTimeSys,
                cameraShakeRightSys, cameraShakeLeftSys
            })
            .addLateFixedSystems({
                updatePositionSys,
                updateVelocitySys, collisionSys,
                spriteCreatorSys,
                uiCreatorSys,
                textCreatorSys,
                textUICreatorSys,
                tileMapCreatorSys,
                animationSys,
                updateTileMapSys,
                // onClickButtonsSys,
                // onHoverButtonsSys,
                purgeCollisionSys
            })
            .addLateSystems({renderSys})
            .run();
    } catch (const std::exception& e) {
        std::cerr << "Exception Catch:" << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    printf("Fin sans crash\n");

    return EXIT_SUCCESS;
}