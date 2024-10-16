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

void pollEventsSys(MainUnscaledFixedSystem, World& world) {
    vulkanEngine.window.pollEvents();

    if (!vulkanEngine.window.isOpen()) {
        vulkanEngine.window.close();
        world.stop_run();
    }
}

int main() {
    ZerEngine()
        .use_multithreading(false)
        .set_fixed_time_step(0.02f)
        .add_resource<BuildVersion>("0.0.1R")
        .add_resource<PipelineManager>()
        .add_resource<FrameBufferManager>()
        .add_resource<TextureManager>()
        .add_resource<FontManager>()
        .add_resource<SpatialHashMap>()
        .add_resource<LayerBasedCollisions>()
        .add_resource<InGameView>(glm::vec4(0, 0, 160, 144))
        .add_resource<UIView>(glm::vec4(0, 0, 160, 144))
        .add_resource<AppState>(AppStateType::APP_STATE_HOME_MENU)
        .add_systems(startSystem, startSys)
        .add_systems(mainUnscaledFixedSystem, {
            pollEventsSys
        })
        .add_systems(mainFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_HOME_MENU;
            },
            {
                cameraSys,
                homeMenuBackgroundSlideSys, homeMenuSelectorSys, homeMenuSelectorMoveDownSys, homeMenuSelectorMoveUpSys
            }
        )
        .add_systems(mainFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME;
            },
            {
            barbarianMovementSys, barbarianStartAttackSys, barbarianStopAttackSys, barbarianStartDashSys, barbarianStopDashSys,
            playerLootSys, playerLootAttractSys, playerHitSys, playerFrenzySys,
            breakableHitSys, breakableOnHitSys,
            enemyHitSys, enemyDropLootsSys,
            shurikenRotationSys, cameraAberationSys, cameraEffectApplicationSys,
            invincibleFramesSys, knockbackSys, damageTextSys, combatParticleGeneratorSys, deathParticleSys,
            lootSpreadSys, cameraSys, innerMovementDownSys, innerMovementUpSys, dustParticleSys,
            doorTriggerSys, openDoorSys, openDoorWithKeySys, doorCameraMovementSys, playerAttackWeightSys,
            playerDaggerSys, daggerMovementSys, laserMovementSys, laserHitSys, playerLaserSys,
            warpSys, particleGeneratorSys, bombSpreadSys, rerollSys,
            chestOpenSys,
            
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
            megaSlimeMoveSys, megaSlimeFireballSys, megaSlimeBounceSys, megaSlimeBounceTotalSys, megaSlimePreSpawnSys,
            rockBossPreRollSys, rockBossRollSys, rockBossStunSys, rockBossGroundCrystalsSys, rockBossSmallCrystalThrowSys,
            sarcophageShadowMarkSys, sarcophagePreLaserSys, sarcophageLaserSys, sarcophageObeliskSys, sarcophageShockwaveSys,
            golemRockAttackSys, golemRockSys, golemPreFootAttackSys, golemFootAttackSys, golemPreLaserAttackCardinalSys, golemLaserAttackCardinalSys, golemPreLaserAttackDiagonalSys, golemLaserAttackDiagonalSys,
            shadowBossHubMovementSys,

            fireBallAttackSys, fireBallHitSys,

            // Traps:
            spikeDownSys, spikeUpSys,
            voidSphereOffSys, voidSphereOnSys,
            torchIdleSys, torchCastSys,
            turretCardinalSys, turretDiagonalSys,

            // HUD
            levelUpKnockbackSys,
            pauseMenuOpenCloseSys,
            inventoryBarShrinkSys,

            // NPC:
            merchantOpenCloseSys
        })

        .add_systems(
            mainUnscaledFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME && !world.view(with<MenuChest>).empty();
            },
            {
                menuChestValidateSys,
            }
        )

        .add_systems(
            mainUnscaledFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME;// && !world.view(with<MapMenu>).empty();
            },
            {
                mapMenuOpenCloseSys, mapMenuTranslationSys, mapMenuReverseTranslationSys,
            }
        )

        .add_systems(
            mainUnscaledFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME;// && !world.view(with<MapMenu>).empty();
            },
            {
                talentSphereOpenSys, talentSphererCloseSys, talentSphereMenuTranslationSys, talentSphereMenuReverseTranslationSys
            }
        )

        .add_systems(
            mainUnscaledFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME && (!world.view(with<LevelUpPreMenu>).empty() || !world.view(with<MenuBonus>).empty());
            },
            {
                levelUpPreMenuSys, menuBonusTranslationSys, menuBonusPreReverseTranslationSys, menuBonusReverseTranslationSys, menuBonusSelectorSys,
                menuBonusSelectorMoveDownSys, menuBonusSelectorMoveUpSys, menuBonusCurSelectedRowScaleSys,
            }
        )

        .add_systems(
            mainUnscaledFixedSystem,
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME && !world.view(with<PauseMenu>).empty();
            },
            {pauseMenuTranslationSys, pauseMenuReverseTranslationSys, pauseMenuSelectorSys, pauseMenuSelectorMoveDownSys, pauseMenuSelectorMoveUpSys}
        )

        // Enemies Lvl1 Threads
        .add_systems(ThreadedFixedSet(
            [](World& world) -> bool {
                auto [appstate] = world.resource<const AppState>();
                return appstate == AppStateType::APP_STATE_IN_GAME && !world.view(with<Enemy>).empty();
            },
            {
                ThreadedFixedSet( // Mummy Threads
                    [](World& world) -> bool {
                        return !world.view(with<Mummy>).empty();
                    },
                    {mummyMoveSys, mummyPreAttackSys, mummyAttackSys}
                ),
                ThreadedFixedSet( // Insect Threads
                    [](World& world) -> bool {
                        return !world.view(with<Insect>).empty();
                    },
                    {insectChangeDirectionSys, insectMoveSys, insectAttackSys}
                ),
                ThreadedFixedSet( // Gasterolcan Threads
                    [](World& world) -> bool {
                        return !world.view(with<Gasterolcan>).empty();
                    },
                    {gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys}
                ),
                ThreadedFixedSet( // Spectre Threads
                    [](World& world) -> bool {
                        return !world.view(with<Spectre>).empty();
                    },
                    {spectreMoveSys, spectreVanishSys, spectreCastSys}
                ),

                // Boss Threads
                ThreadedFixedSet(
                    [](World& world) -> bool {
                        return !world.view(with<Boss>).empty();
                    },
                    {
                        ThreadedFixedSet( // Shadow Boss Threads
                            [](World& world) -> bool {
                                return !world.view(with<ShadowBoss>).empty();
                            },
                            {shadow_boss_move_sys, shadow_boss_pre_laser_sys, shadow_boss_laser_sys, shadow_boss_shadow_mark_duration_sys, shadow_boss_shadow_mark_invocation_sys, shadow_boss_minion_pre_spawn_sys, shadowMinionSys, shadow_boss_shadow_explosion_sys}
                        ),
                    }
                ),
            }
        ))

        .add_systems(mainFixedSystem, {
            // particleSystems, generatorParticleMovement,
            lifeTimeSys,
        })

        .add_systems(mainUnscaledFixedSystem, {
            // particleSystems, generatorParticleMovement,
            unscaledLifeTimeSys,
        })

        // Camera Set
        .add_systems(ThreadedFixedSet([](World& world) { return !world.view(with<CameraShakeRight>).empty() || !world.view(with<CameraShakeLeft>).empty(); }, {
            cameraShakeRightSys, cameraShakeLeftSys
        }))
        .add_systems(lateUnscaledFixedSystem, {
            updatePositionSys
        })
        .add_systems(lateFixedSystem, {
            updateVelocitySys, collisionSys, updateTileMapSys,
        })
        .add_systems(lateUnscaledFixedSystem, {
            textCreatorSys,
            textUICreatorSys,
            animationSys,
            // onClickButtonsSys,
            // onHoverButtonsSys,
            purgeCollisionSys
        })
        .add_systems(lateSystem, {
            renderSys
        })
        .run();

    printf("Fin sans crash\n");

    return EXIT_SUCCESS;
}