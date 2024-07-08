#pragma once

#include "ZerengineCore.hpp"
#include "ZerengineCommon.hpp"
#include "ZerengineMaths.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////////

class Collider final {
public:
    constexpr Collider(float x, float y, float z, float w) noexcept:
        col(x, y, z, w) {
    }

    constexpr Collider(const glm::vec4& newCol) noexcept:
        col(newCol) {
    }

public:
    glm::vec4 col;
};

class Trigger final {
public:
    constexpr Trigger(float x, float y, float z, float w) noexcept:
        col(x, y, z, w) {
    }

    constexpr Trigger(const glm::vec4& newCol) noexcept:
        col(newCol) {
    }

public:
    glm::vec4 col;
};

///////////////////////////////////////////////////////////////////////////////////

class OnCollisionEnter final {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateFixedSystem, World&);
private:
    OnCollisionEnter() noexcept:
        othCols(),
        oldOthCols() {
    }

    OnCollisionEnter(const std::initializer_list<Ent>& newList) noexcept:
        othCols(newList),
        oldOthCols() {
    }

public:
    [[nodiscard]] const std::unordered_set<Ent>::const_iterator begin() const noexcept {
        return othCols.begin();
    }

    [[nodiscard]] const std::unordered_set<Ent>::const_iterator end() const noexcept {
        return othCols.end();
    }

private:
    std::unordered_set<Ent> othCols;
    std::unordered_set<Ent> oldOthCols;
};

class OnCollisionStay final {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateFixedSystem, World&);
private:
    OnCollisionStay() noexcept:
        othCols(),
        oldOthCols() {
    }

    OnCollisionStay(const std::initializer_list<Ent>& newList) noexcept:
        othCols(newList),
        oldOthCols() {
    }

public:
    [[nodiscard]] const std::unordered_set<Ent>::const_iterator begin() const noexcept {
        return othCols.begin();
    }

    [[nodiscard]] const std::unordered_set<Ent>::const_iterator end() const noexcept {
        return othCols.end();
    }

private:
    std::unordered_set<Ent> othCols;
    std::unordered_set<Ent> oldOthCols;
};

class OnCollisionExit final {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateFixedSystem, World&);
private:
    OnCollisionExit() noexcept:
        othCols(),
        oldOthCols() {
    }

    OnCollisionExit(const std::initializer_list<Ent>& newList) noexcept:
        othCols(newList),
        oldOthCols() {
    }

public:
    [[nodiscard]] const std::unordered_set<Ent>::const_iterator begin() const noexcept {
        return othCols.begin();
    }

    [[nodiscard]] const std::unordered_set<Ent>::const_iterator end() const noexcept {
        return othCols.end();
    }

private:
    std::unordered_set<Ent> othCols;
    std::unordered_set<Ent> oldOthCols;
};

///////////////////////////////////////////////////////////////////////////////////

class LayerCollision final {
public:
    constexpr LayerCollision(std::size_t newLayer) noexcept:
        layer(newLayer) {
    }

public:
    std::size_t layer;
};

///////////////////////////////////////////////////////////////////////////////////

class LayerBasedCollisions final {
public:
    void addExclusion(std::size_t typeA, std::size_t typeB) {
        // TypeB -> TypeA
        auto exclusionMatrixTypeAIt = exclusionMatrix.find(typeA);
        // if (!exclusionMatrix.contains(typeA)) {
        if (exclusionMatrixTypeAIt == exclusionMatrix.end()) {
            exclusionMatrix.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeA),
                std::forward_as_tuple(std::initializer_list<std::size_t>{typeB})
            );
        // } else if (!exclusionMatrix.at(typeA).contains(typeB)) {
        } else if (!exclusionMatrixTypeAIt->second.contains(typeB)) {
            // exclusionMatrix.at(typeA).emplace(typeB);
            exclusionMatrixTypeAIt->second.emplace(typeB);
        }
        // TypeA -> TypeB
        auto exclusionMatrixTypeBIt = exclusionMatrix.find(typeB);
        // if (!exclusionMatrix.contains(typeB)) {
        if (exclusionMatrixTypeBIt == exclusionMatrix.end()) {
            exclusionMatrix.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(typeB),
                std::forward_as_tuple(std::initializer_list<std::size_t>{typeA})
            );
        // } else if (!exclusionMatrix.at(typeB).contains(typeA)) {
        } else if (!exclusionMatrixTypeBIt->second.contains(typeA)) {
            // exclusionMatrix.at(typeB).emplace(typeA);
            exclusionMatrixTypeBIt->second.emplace(typeA);
        }
    }

    void removeExclusion(std::size_t typeA, std::size_t typeB) {
        if (auto exclusionMatrixTypeAIt = exclusionMatrix.find(typeA); exclusionMatrixTypeAIt != exclusionMatrix.end()) {
            exclusionMatrixTypeAIt->second.erase(typeB);
        }
        if (auto exclusionMatrixTypeBIt = exclusionMatrix.find(typeB); exclusionMatrixTypeBIt != exclusionMatrix.end()) {
            exclusionMatrixTypeBIt->second.erase(typeA);
        }
    }

    bool isSameLayer(const LayerCollision& layerA, const LayerCollision& layerB) const {
        auto exclusionMatrixTypeAIt = exclusionMatrix.find(layerA.layer);
        if (exclusionMatrixTypeAIt == exclusionMatrix.end()) {
            return true;
        }
        if (!exclusionMatrixTypeAIt->second.contains(layerB.layer)) {
            return true;
        }
        return false;
    }

private:
    std::unordered_map<std::size_t, std::unordered_set<std::size_t>> exclusionMatrix;
};

///////////////////////////////////////////////////////////////////////////////////

class SpatialHashMap final {
public:
    void clear() {
        cells.clear();
        entLocations.clear();
    }

    void erase(const Ent ent) {
        if (auto containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
            const auto& location = containEnt->second;
            for (float x = location.x; x < location.y; x++) {
                for (float y = location.z; y < location.w; y++) {
                    cells.at(x).at(y).erase(ent);
                }
            }
            entLocations.erase(containEnt);
        }
    }

    void emplace_or_replace(const Ent ent, const glm::vec4& col, const glm::mat4& model) {
        decltype(entLocations)::iterator containEnt;
        if (containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
            const auto& location = containEnt->second;
            for (float x = location.x; x < location.y; x++) {
                for (float y = location.z; y < location.w; y++) {
                    cells.at(x).at(y).erase(ent);
                }
            }
        }

        auto globalBoundingBox = getGlobalBoundingBox(col, model);

        glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
        glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

        for (float x = min.x; x < max.x; x++) {
            auto cellX = cells.find(x);
            if (cellX == cells.end()) {
                cellX = cells.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(x),
                    std::forward_as_tuple()
                ).first;
            }
            for (float y = min.y; y < max.y; y++) {
                auto cellY = cellX->second.find(y);
                if (cellY == cellX->second.end()) {
                    cellX->second.emplace(
                        std::piecewise_construct,
                        std::forward_as_tuple(y),
                        std::forward_as_tuple(std::initializer_list<Ent>{ent})
                    );
                } else {
                    cellY->second.emplace(ent);
                }
            }
        }

        if (containEnt != entLocations.end()) {
            containEnt->second = glm::vec4(min.x, max.x, min.y, max.y);
        } else {
            entLocations.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(ent),
                std::forward_as_tuple(min.x, max.x, min.y, max.y)
            );
        }
    }

    [[nodiscard]] std::unordered_set<Ent> getIntersectList(const Ent ent, const glm::vec4& col, const glm::mat4& model) const {
        std::unordered_set<Ent> othEnts;

        auto globalBoundingBox = getGlobalBoundingBox(col, model);

        glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
        glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

        for (float x = min.x; x < max.x; x++) {
            if (const auto cellX = cells.find(x); cellX != cells.end()) {
                for (float y = min.y; y < max.y; y++) {
                    if (const auto cellXY = cellX->second.find(y); cellXY != cellX->second.end()) {
                        othEnts.insert(cellXY->second.begin(), cellXY->second.end());
                    }
                }
            }
        }

        othEnts.erase(ent);

        return othEnts;
    }

    [[nodiscard]] std::unordered_set<Ent> getIntersectList(const glm::vec4& col, const glm::mat4& model) const {
        std::unordered_set<Ent> othEnts;

        auto globalBoundingBox = getGlobalBoundingBox(col, model);

        glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
        glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

        for (float x = min.x; x < max.x; x++) {
            if (const auto cellX = cells.find(x); cellX != cells.end()) {
                for (float y = min.y; y < max.y; y++) {
                    if (const auto cellXY = cellX->second.find(y); cellXY != cellX->second.end()) {
                        othEnts.insert(cellXY->second.begin(), cellXY->second.end());
                    }
                }
            }
        }

        return othEnts;
    }

private:
    glm::vec2 cellSize = glm::vec2(32.f, 32.f);
    std::unordered_map<float, std::unordered_map<float, std::unordered_set<Ent>>> cells;
    std::unordered_map<Ent, glm::vec4> entLocations;
};

///////////////////////////////////////////////////////////////////////////////////

void updateVelocityRec(World& world, Ent ent, const glm::vec2& vel) {
    if (auto childrenOpt = world.getChildren(ent)) {
        for (const auto childEnt: childrenOpt.value().get()) {
            if (auto opt = world.get<Transform>(childEnt)) {
                auto [childTrans] = opt.value();
                childTrans.moveVelocity(vel);
            }
            updateVelocityRec(world, childEnt, vel);
        }
    }
}

void updateVelocitySys(LateFixedSystem, World& world) {
    for (auto [ent, velocity, trans]: world.view<Velocity, Transform>()) {
        if (velocity.vel != glm::vec2(0, 0)) {
            trans.moveVelocity(velocity.vel);
            updateVelocityRec(world, ent, velocity.vel);
            velocity.vel = glm::vec2(0, 0);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

void updatePositionSys(LateFixedSystem, World& world) {
    for (auto [ent, trans]: world.view<Transform>()) {
        if (trans.needUpdatePosition) {
            trans.moveVelocity(trans.diffPosition);
            updateVelocityRec(world, ent, trans.diffPosition);
            trans.diffPosition = glm::vec2(0, 0);
            trans.needUpdatePosition = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

void collisionSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    for (auto [_, collision]: world.view<OnCollisionEnter>()) {
        collision.oldOthCols.swap(collision.othCols);
        collision.othCols.clear();
    }

    for (auto [_, collision]: world.view<OnCollisionStay>()) {
        collision.oldOthCols.swap(collision.othCols);
        collision.othCols.clear();
    }

    for (auto [_, collision]: world.view<OnCollisionExit>()) {
        collision.oldOthCols.swap(collision.othCols);
        collision.othCols.clear();
    }

    auto [layerBasedCollisions, spatialHashMap] = world.resource<const LayerBasedCollisions, SpatialHashMap>();

    for (auto [othEnt, othTrig, othTrans]: world.view<const Trigger, Transform>()) {
        if (othTrans.hashMapUpdated) {
            othTrans.hashMapUpdated = false;
            spatialHashMap.emplace_or_replace(othEnt, othTrig.col, othTrans.getModel());
        }
    }

    for (auto [othEnt, othCol, othTrans]: world.view<const Collider, Transform>()) {
        if (othTrans.hashMapUpdated) {
            othTrans.hashMapUpdated = false;
            spatialHashMap.emplace_or_replace(othEnt, othCol.col, othTrans.getModel());
        }
    }

    for (auto [dynEnt, dynTrig, dynTrans]: world.view<const Trigger, Transform>(with<Velocity>)) {
        auto list = spatialHashMap.getIntersectList(dynEnt, dynTrig.col, dynTrans.getModel());

        if (auto onCollisionEnterOpt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
            auto [dynCollisionEnter] = onCollisionEnterOpt.value();
            for (const auto oldEnt: dynCollisionEnter.oldOthCols) {
                if (world.exist(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [dynCollisionExit] = onCollisionExitOpt.value();
                            dynCollisionExit.othCols.emplace(oldEnt);
                        } else {
                            world.add(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [oldCollisionExit] = onCollisionExitOpt.value();
                            oldCollisionExit.othCols.emplace(dynEnt);
                        } else {
                            world.add(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform>(oldEnt)) {
                            if (world.has<Collider>(oldEnt) || world.has<Trigger>(oldEnt)) {
                                auto [oldTransform] = oldTransformOpt.value();
                                glm::vec4 col(0, 0, 0, 0);
                                if (auto opt = world.getThisFrame<const Collider>(oldEnt)) {
                                    auto [oldCollider] = opt.value();
                                    col = oldCollider.col;
                                } else if (auto opt = world.getThisFrame<const Trigger>(oldEnt)) {
                                    auto [oldTrigger] = opt.value();
                                    col = oldTrigger.col;
                                }
                                // if (intersect(dynTrans.getPosition(), dynTrig.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale())) {
                                if (intersectOBB(dynTrig.col, dynTrans.getModel(), col, oldTransform.getModel())) {
                                    bool layerOk = true;
                                    if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                                        if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(oldEnt)) {
                                            auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                            auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                            layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                                        }
                                    }
                                    if (layerOk) {
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
                                            auto [dynCollisionStay] = opt.value();
                                            dynCollisionStay.othCols.emplace(oldEnt);
                                        } else {
                                            world.add(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add(oldEnt, OnCollisionExit({dynEnt}));
                                    }
                                }
                            }
                        }
                        list.erase(oldEnt);
                    }
                }
            }
        }

        if (auto dynCollisionStayOpt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
            auto [dynCollisionStay] = dynCollisionStayOpt.value();
            for (const auto oldEnt: dynCollisionStay.oldOthCols) {
                if (world.exist(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [onCollisionExitDyn] = opt.value();
                            onCollisionExitDyn.othCols.emplace(oldEnt);
                        } else {
                            world.add(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [onCollisionExitOld] = opt.value();
                            onCollisionExitOld.othCols.emplace(dynEnt);
                        } else {
                            world.add(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform>(oldEnt)) {
                            if (world.has<Collider>(oldEnt) || world.has<Trigger>(oldEnt)) {
                                auto [oldTransform] = oldTransformOpt.value();
                                glm::vec4 col(0, 0, 0, 0);
                                if (auto opt = world.getThisFrame<const Collider>(oldEnt)) {
                                    auto [oldCollider] = opt.value();
                                    col = oldCollider.col;
                                } else if (auto opt = world.getThisFrame<const Trigger>(oldEnt)) {
                                    auto [oldTrigger] = opt.value();
                                    col = oldTrigger.col;
                                }
                                // if (intersect(dynTrans.getPosition(), dynTrig.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale())) {
                                if (intersectOBB(dynTrig.col, dynTrans.getModel(), col, oldTransform.getModel())) {
                                    bool layerOk = true;
                                    if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                                        if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(oldEnt)) {
                                            auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                            auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                            layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                                        }
                                    }
                                    if (layerOk) {
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
                                            auto [dynCollisionStay] = opt.value();
                                            dynCollisionStay.othCols.emplace(oldEnt);
                                        } else {
                                            world.add(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add(oldEnt, OnCollisionExit({dynEnt}));
                                    }
                                }
                            }
                        }
                        list.erase(oldEnt);
                    }
                }
            }
        }

        for (const auto othEnt: list) {
            if (auto oldTransformOpt = world.getThisFrame<Transform>(othEnt)) {
                if (world.has<Collider>(othEnt) || world.has<Trigger>(othEnt)) {
                    auto [othTransform] = oldTransformOpt.value();
                    glm::vec4 col(0, 0, 0, 0);
                    if (auto opt = world.getThisFrame<const Collider>(othEnt)) {
                        auto [oldCollider] = opt.value();
                        col = oldCollider.col;
                    } else if (auto opt = world.getThisFrame<const Trigger>(othEnt)) {
                        auto [oldTrigger] = opt.value();
                        col = oldTrigger.col;
                    }
                    // if (intersect(dynTrans.getPosition(), dynTrig.col, dynTrans.getScale(), othTransform.getPosition(), col, othTransform.getScale())) {
                    if (intersectOBB(dynTrig.col, dynTrans.getModel(), col, othTransform.getModel())) {
                        bool layerOk = true;
                        if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                            if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(othEnt)) {
                                auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                            }
                        }
                        if (layerOk) {
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
                                auto [onCollisionEnterDyn] = opt.value();
                                onCollisionEnterDyn.othCols.emplace(othEnt);
                            } else {
                                world.add(dynEnt, OnCollisionEnter({othEnt}));
                            }
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(othEnt)) {
                                auto [onCollisionEnterOth] = opt.value();
                                onCollisionEnterOth.othCols.emplace(dynEnt);
                            } else {
                                world.add(othEnt, OnCollisionEnter({dynEnt}));
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto [dynEnt, dynCol, dynTrans]: world.view<const Collider, Transform>(with<Velocity>)) {
        auto list = spatialHashMap.getIntersectList(dynEnt, dynCol.col, dynTrans.getModel());

        if (auto onCollisionEnterOpt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
            auto [dynCollisionEnter] = onCollisionEnterOpt.value();
            for (const auto oldEnt: dynCollisionEnter.oldOthCols) {
                if (world.exist(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [dynCollisionExit] = onCollisionExitOpt.value();
                            dynCollisionExit.othCols.emplace(oldEnt);
                        } else {
                            world.add(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [oldCollisionExit] = onCollisionExitOpt.value();
                            oldCollisionExit.othCols.emplace(dynEnt);
                        } else {
                            world.add(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform>(oldEnt)) {
                            if (world.has<Collider>(oldEnt) || world.has<Trigger>(oldEnt)) {
                                auto [oldTransform] = oldTransformOpt.value();
                                glm::vec4 col(0, 0, 0, 0);
                                if (auto opt = world.getThisFrame<const Collider>(oldEnt)) {
                                    auto [oldCollider] = opt.value();
                                    col = oldCollider.col;
                                } else if (auto opt = world.getThisFrame<const Trigger>(oldEnt)) {
                                    auto [oldTrigger] = opt.value();
                                    col = oldTrigger.col;
                                }
                                // if (intersect(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale())) {
                                auto intersectWithMTVRes = intersectOBBWithMTV(dynCol.col, dynTrans.getModel(), col, oldTransform.getModel());
                                if (intersectWithMTVRes.first) {
                                    bool layerOk = true;
                                    if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                                        if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(oldEnt)) {
                                            auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                            auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                            layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                                        }
                                    }
                                    if (layerOk) {
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
                                            auto [dynCollisionStay] = opt.value();
                                            dynCollisionStay.othCols.emplace(oldEnt);
                                        } else {
                                            world.add(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                        if (world.has<Collider>(oldEnt)) {
                                            // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale());
                                            glm::vec2 antiVel = intersectWithMTVRes.second;
                                            dynTrans.moveVelocity(antiVel);
                                            if (world.hasChildren(dynEnt)) {
                                                updateVelocityRec(world, dynEnt, antiVel);
                                            }
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add(oldEnt, OnCollisionExit({dynEnt}));
                                    }
                                }
                            }
                        }
                        list.erase(oldEnt);
                    }
                }
            }
        }

        if (auto dynCollisionStayOpt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
            auto [dynCollisionStay] = dynCollisionStayOpt.value();
            for (const auto oldEnt: dynCollisionStay.oldOthCols) {
                if (world.exist(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [onCollisionExitDyn] = opt.value();
                            onCollisionExitDyn.othCols.emplace(oldEnt);
                        } else {
                            world.add(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [onCollisionExitOld] = opt.value();
                            onCollisionExitOld.othCols.emplace(dynEnt);
                        } else {
                            world.add(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform>(oldEnt)) {
                            if (world.has<Collider>(oldEnt) || world.has<Trigger>(oldEnt)) {
                                auto [oldTransform] = oldTransformOpt.value();
                                glm::vec4 col(0, 0, 0, 0);
                                if (auto opt = world.getThisFrame<const Collider>(oldEnt)) {
                                    auto [oldCollider] = opt.value();
                                    col = oldCollider.col;
                                } else if (auto opt = world.getThisFrame<const Trigger>(oldEnt)) {
                                    auto [oldTrigger] = opt.value();
                                    col = oldTrigger.col;
                                }
                                // if (intersect(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale())) {
                                auto intersectWithMTVRes = intersectOBBWithMTV(dynCol.col, dynTrans.getModel(), col, oldTransform.getModel());
                                if (intersectWithMTVRes.first) {
                                    bool layerOk = true;
                                    if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                                        if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(oldEnt)) {
                                            auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                            auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                            layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                                        }
                                    }
                                    if (layerOk) {
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(dynEnt)) {
                                            auto [dynCollisionStay] = opt.value();
                                            dynCollisionStay.othCols.emplace(oldEnt);
                                        } else {
                                            world.add(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                        if (world.has<Collider>(oldEnt)) {
                                            // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale());
                                            glm::vec2 antiVel = intersectWithMTVRes.second;
                                            dynTrans.moveVelocity(antiVel);
                                            if (world.hasChildren(dynEnt)) {
                                                updateVelocityRec(world, dynEnt, antiVel);
                                            }
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add(oldEnt, OnCollisionExit({dynEnt}));
                                    }
                                }
                            }
                        }
                        list.erase(oldEnt);
                    }
                }
            }
        }

        for (const auto othEnt: list) {
            if (auto oldTransformOpt = world.getThisFrame<Transform>(othEnt)) {
                if (world.has<Collider>(othEnt) || world.has<Trigger>(othEnt)) {
                    auto [othTransform] = oldTransformOpt.value();
                    glm::vec4 col(0, 0, 0, 0);
                    if (auto opt = world.getThisFrame<const Collider>(othEnt)) {
                        auto [oldCollider] = opt.value();
                        col = oldCollider.col;
                    } else if (auto opt = world.getThisFrame<const Trigger>(othEnt)) {
                        auto [oldTrigger] = opt.value();
                        col = oldTrigger.col;
                    }
                    // if (intersect(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), othTransform.getPosition(), col, othTransform.getScale())) {
                    auto intersectWithMTVRes = intersectOBBWithMTV(dynCol.col, dynTrans.getModel(), col, othTransform.getModel());
                    if (intersectWithMTVRes.first) {
                        bool layerOk = true;
                        if (auto dynLayerCollisionOpt = world.getThisFrame<LayerCollision>(dynEnt)) {
                            if (auto oldLayerCollisionOpt = world.getThisFrame<LayerCollision>(othEnt)) {
                                auto [dynLayerCollision] = dynLayerCollisionOpt.value();
                                auto [oldLayerCollision] = oldLayerCollisionOpt.value();
                                layerOk = layerBasedCollisions.isSameLayer(dynLayerCollision, oldLayerCollision);
                            }
                        }
                        if (layerOk) {
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
                                auto [onCollisionEnterDyn] = opt.value();
                                onCollisionEnterDyn.othCols.emplace(othEnt);
                            } else {
                                world.add(dynEnt, OnCollisionEnter({othEnt}));
                            }
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(othEnt)) {
                                auto [onCollisionEnterOth] = opt.value();
                                onCollisionEnterOth.othCols.emplace(dynEnt);
                            } else {
                                world.add(othEnt, OnCollisionEnter({dynEnt}));
                            }
                            if (world.has<Collider>(othEnt)) {
                                // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), othTransform.getPosition(), col, othTransform.getScale());
                                glm::vec2 antiVel = intersectWithMTVRes.second;
                                dynTrans.moveVelocity(antiVel);
                                if (world.hasChildren(dynEnt)) {
                                    updateVelocityRec(world, dynEnt, antiVel);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Purge Empty Collisions
    for (auto [entCollision, collision]: world.view<OnCollisionEnter>()) {
        if (collision.othCols.empty()) {
            world.remove<OnCollisionEnter>(entCollision);
        }
    }

    for (auto [entCollision, collision]: world.view<OnCollisionStay>()) {
        if (collision.othCols.empty()) {
            world.remove<OnCollisionStay>(entCollision);
        }
    }

    for (auto [entCollision, collision]: world.view<OnCollisionExit>()) {
        if (collision.othCols.empty()) {
            world.remove<OnCollisionExit>(entCollision);
        }
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////

void purgeCollisionSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [spatialHashMap] = world.resource<SpatialHashMap>();

    for (const auto othEnt: world.getDestroyedEnts()) {
        spatialHashMap.erase(othEnt);
        if (world.has<OnCollisionEnter>(othEnt) || world.has<OnCollisionStay>(othEnt) || world.has<OnCollisionExit>(othEnt)) {
            for (auto [_, collision]: world.view<OnCollisionEnter>()) {
                // if (collision.othCols.contains(othEnt)) {
                    // printf("Purge Enter: [%zu]\n", othEnt);
                    collision.othCols.erase(othEnt);
                // }
            }

            for (auto [_, collision]: world.view<OnCollisionStay>()) {
                // if (collision.othCols.contains(othEnt)) {
                    // printf("Purge Stay: [%zu]\n", othEnt);
                    collision.othCols.erase(othEnt);
                // }
            }

            for (auto [_, collision]: world.view<OnCollisionExit>()) {
                // if (collision.othCols.contains(othEnt)) {
                    // printf("Purge Exit: [%zu]\n", othEnt);
                    collision.othCols.erase(othEnt);
                // }
            }
        }
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////