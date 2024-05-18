#define DISPLAY_FPS
#define GLFW_INCLUDE_VULKAN
#include <unordered_map>
#include <any>
#include <concepts>
#include <unordered_set>

#include <Zerengine.hpp>
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

void pollEventsSys(World& world) {
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
            .addRes<PipelineManager>()
            .addRes<FrameBufferManager>()
            .addRes<TextureManager>()
            .addRes<FontManager>()
            .addRes<SpatialHashMap>()
            .addRes<LayerBasedCollisions>()
            .addRes<InGameView>(glm::vec4(0, 0, 160, 144))
            .addRes<UIView>(glm::vec4(0, 0, 160, 144))
            .addStartSys(startSys)
            .addMainFixedSys(
                pollEventsSys
            )
            .addMainFixedSys(
                barbarianMovementSys, barbarianStartAttackSys, barbarianStopAttackSys, barbarianStartDashSys, barbarianStopDashSys,
                playerLootSys, playerLootAttractSys, playerHitSys,
                breakableHitSys, breakableOnHitSys,
                enemyHitSys, enemyDropLootsSys,
                invincibleFramesSys, knockbackSys, damageTextSys, combatParticleGeneratorSys, deathParticleSys,
                lootSpreadSys, cameraSys, innerMovementDownSys, innerMovementUpSys, dustParticleSys,
                doorTriggerSys, openDoorSys, doorCameraMovementSys,
                // Enemies scripts
                slimeMoveSys,
                insectMoveSys, insectAttackSys,
                anubisMoveSys, anubisAttackSys,
                batMoveSys, batAttackSys,
                mummyMoveSys, mummyPreAttackSys, mummyAttackSys,
                gasterolcanMoveSys, gasterolcanPreAttackSys, gasterolcanAttackSys,
                lavaSlimeMoveSys, lavaSlimeAttackSys,
                robobouleMoveSys, roboboulePreAttackSys,

                fireBallAttackSys, fireBallHitSys
            )
            .addMainFixedSys(
                // particleSystems, generatorParticleMovement,
                lifeTimeSys,
                cameraShakeRightSys, cameraShakeLeftSys,
                updatePositionSys, updateVelocitySys, collisionSys
            )
            .addLateFixedSys(
                spriteCreatorSys,
                uiCreatorSys,
                textCreatorSys,
                textUICreatorSys,
                tileMapCreatorSys,
                animationSys,
                updateTileMap,
                // onClickButtonsSys,
                // onHoverButtonsSys,
                purgeCollision
            )
            .addLateSys(renderSys)
            .run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    printf("Fin sans crash\n");

    return EXIT_SUCCESS;
}