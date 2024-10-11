#pragma once

#include "ZerengineCore.hpp"
#include "ZerengineCommon.hpp"
#include "ZerengineMaths.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <type_traits>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////////

class Collider final: public IComponent {
public:
    [[nodiscard]] constexpr Collider(float x, float y, float z, float w) noexcept:
        col(x, y, z, w) {
    }

    [[nodiscard]] constexpr Collider(const glm::vec4& newCol) noexcept:
        col(newCol) {
    }

public:
    glm::vec4 col;
};

class Trigger final: public IComponent {
public:
    [[nodiscard]] constexpr Trigger(float x, float y, float z, float w) noexcept:
        col(x, y, z, w) {
    }

    [[nodiscard]] constexpr Trigger(const glm::vec4& newCol) noexcept:
        col(newCol) {
    }

public:
    glm::vec4 col;
};

///////////////////////////////////////////////////////////////////////////////////

class OnCollisionEnter final: public IComponent {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateUnscaledFixedSystem, World&);
private:
    [[nodiscard]] OnCollisionEnter() noexcept:
        othCols(),
        oldOthCols() {
    }

    [[nodiscard]] OnCollisionEnter(const std::initializer_list<Ent>& newList) noexcept:
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

class OnCollisionStay final: public IComponent {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateUnscaledFixedSystem, World&);
private:
    [[nodiscard]] OnCollisionStay() noexcept:
        othCols(),
        oldOthCols() {
    }

    [[nodiscard]] OnCollisionStay(const std::initializer_list<Ent>& newList) noexcept:
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

class OnCollisionExit final: public IComponent {
friend void collisionSys(LateFixedSystem, World&);
friend void purgeCollisionSys(LateUnscaledFixedSystem, World&);
private:
    [[nodiscard]] OnCollisionExit() noexcept:
        othCols(),
        oldOthCols() {
    }

    [[nodiscard]] OnCollisionExit(const std::initializer_list<Ent>& newList) noexcept:
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

class LayerCollision final: public IComponent {
public:
    template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
    [[nodiscard]] constexpr LayerCollision(const E& newLayer) noexcept:
        layer(static_cast<std::size_t>(newLayer)) {
    }

public:
    std::size_t layer;
};

///////////////////////////////////////////////////////////////////////////////////

class LayerBasedCollisions final: public IResource {
public:
    template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
    void addExclusion(const E& typeAE, const E& typeBE) {
        auto typeA = static_cast<std::size_t>(typeAE);
        auto typeB = static_cast<std::size_t>(typeBE);

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

    template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
    void removeExclusion(const E& typeAE, const E& typeBE) {
        auto typeA = static_cast<std::size_t>(typeAE);
        auto typeB = static_cast<std::size_t>(typeBE);

        if (auto exclusionMatrixTypeAIt = exclusionMatrix.find(typeA); exclusionMatrixTypeAIt != exclusionMatrix.end()) {
            exclusionMatrixTypeAIt->second.erase(typeB);
        }
        if (auto exclusionMatrixTypeBIt = exclusionMatrix.find(typeB); exclusionMatrixTypeBIt != exclusionMatrix.end()) {
            exclusionMatrixTypeBIt->second.erase(typeA);
        }
    }

    [[nodiscard]] bool isSameLayer(const LayerCollision& layerA, const LayerCollision& layerB) const {
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

class SpatialHashMap final: public IResource {
public:
    void clear() {
        cells.clear();
        entLocations.clear();
    }

    void erase(const Ent ent) {
        if (auto containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
            const auto& location = containEnt->second;
            for (int xi = location.x; xi < location.y; xi++) {
                float x = xi;
                for (int yi = location.z; yi < location.w; yi++) {
                    float y = yi;
                    cells.at(x).at(y).erase(ent);
                    if (cells.at(x).at(y).empty()) {
                        cells.at(x).erase(y);
                        if (cells.at(x).empty()) {
                            cells.erase(x);
                        }
                    }
                }
            }
            entLocations.erase(containEnt);
        }
    }

    void emplace_or_replace(const Ent ent, const glm::vec4& col, const glm::mat4& model) {
        decltype(entLocations)::iterator containEnt;
        if (containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
            const auto& location = containEnt->second;
            for (int xi = location.x; xi < location.y; xi++) {
                float x = xi;
                for (int yi = location.z; yi < location.w; yi++) {
                    float y = yi;
                    cells.at(x).at(y).erase(ent);
                    if (cells.at(x).at(y).empty()) {
                        cells.at(x).erase(y);
                        if (cells.at(x).empty()) {
                            cells.erase(x);
                        }
                    }
                }
            }
        }

        auto globalBoundingBox = getGlobalBoundingBox(col, model);

        glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
        glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

        for (int xi = min.x; xi < max.x; xi++) {
            float x = xi;
            auto cellX = cells.find(x);
            if (cellX == cells.end()) {
                cellX = cells.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(x),
                    std::forward_as_tuple()
                ).first;
            }
            for (int yi = min.y; yi < max.y; yi++) {
                float y = yi;
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

        for (int xi = min.x; xi < max.x; xi++) {
            float x = xi;
            if (const auto cellX = cells.find(x); cellX != cells.end()) {
                for (int yi = min.y; yi < max.y; yi++) {
                    float y = yi;
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

        for (int xi = min.x; xi < max.x; xi++) {
            float x = xi;
            if (const auto cellX = cells.find(x); cellX != cells.end()) {
                for (int yi = min.y; yi < max.y; yi++) {
                    float y = yi;
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

// struct SpatialHashMapPosition {
// friend struct std::hash<SpatialHashMapPosition>;
// public:
//     [[nodiscard]] constexpr SpatialHashMapPosition() noexcept:
//         x(0.f),
//         y(0.f) {
//     }

//     [[nodiscard]] constexpr SpatialHashMapPosition(float newX, float newY) noexcept:
//         x(newX),
//         y(newY) {
//     }

//     [[nodiscard]] constexpr bool operator==(const SpatialHashMapPosition&) const noexcept = default;

// private:
//     float x;
//     float y;
// };

// template<>
// struct std::hash<SpatialHashMapPosition> {
//     std::size_t operator()(const SpatialHashMapPosition& s) const noexcept {
//         std::size_t h1 = std::hash<float>()(s.x);
//         std::size_t h2 = std::hash<float>()(s.y);
//         return h1 ^ (h2 << 1);
//     }
// };

// class SpatialHashMap final {
// public:
//     void clear() {
//         cells.clear();
//         entLocations.clear();
//     }

//     void erase(const Ent ent) {
//         if (auto containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
//             const auto& location = containEnt->second;
//             for (float x = location.x; x < location.y; x++) {
//                 for (float y = location.z; y < location.w; y++) {
//                     cells.at({x, y}).erase(ent);
//                 }
//             }
//             entLocations.erase(containEnt);
//         }
//     }

//     void emplace_or_replace(const Ent ent, const glm::vec4& col, const glm::mat4& model) {
//         decltype(entLocations)::iterator containEnt;
//         if (containEnt = entLocations.find(ent); containEnt != entLocations.end()) {
//             const auto& location = containEnt->second;
//             for (float x = location.x; x < location.y; x++) {
//                 for (float y = location.z; y < location.w; y++) {
//                     cells.at({x, y}).erase(ent);
//                 }
//             }
//         }

//         auto globalBoundingBox = getGlobalBoundingBox(col, model);

//         glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
//         glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

//         for (float x = min.x; x < max.x; x++) {
//             for (float y = min.y; y < max.y; y++) {
//                 auto cellIt = cells.find({x, y});
//                 if (cellIt == cells.end()) {
//                     cells.emplace(
//                         std::piecewise_construct,
//                         std::forward_as_tuple(x, y),
//                         std::forward_as_tuple(std::initializer_list<Ent>{ent})
//                     );
//                 } else {
//                     cellIt->second.emplace(ent);
//                 }
//             }
//         }

//         if (containEnt != entLocations.end()) {
//             containEnt->second = glm::vec4(min.x, max.x, min.y, max.y);
//         } else {
//             entLocations.emplace(
//                 std::piecewise_construct,
//                 std::forward_as_tuple(ent),
//                 std::forward_as_tuple(min.x, max.x, min.y, max.y)
//             );
//         }
//     }

//     [[nodiscard]] std::unordered_set<Ent> getIntersectList(const Ent ent, const glm::vec4& col, const glm::mat4& model) const {
//         std::unordered_set<Ent> othEnts;

//         auto globalBoundingBox = getGlobalBoundingBox(col, model);

//         glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
//         glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

//         for (float x = min.x; x < max.x; x++) {
//             for (float y = min.y; y < max.y; y++) {
//                 if (const auto cellIt = cells.find({x, y}); cellIt != cells.end()) {
//                     othEnts.insert(cellIt->second.begin(), cellIt->second.end());
//                 }
//             }
//         }

//         othEnts.erase(ent);

//         return othEnts;
//     }

//     [[nodiscard]] std::unordered_set<Ent> getIntersectList(const glm::vec4& col, const glm::mat4& model) const {
//         std::unordered_set<Ent> othEnts;

//         auto globalBoundingBox = getGlobalBoundingBox(col, model);

//         glm::vec2 min = glm::floor(glm::vec2(globalBoundingBox.x, globalBoundingBox.y) / cellSize);
//         glm::vec2 max = glm::ceil(glm::vec2(globalBoundingBox.z, globalBoundingBox.w) / cellSize);

//         for (float x = min.x; x < max.x; x++) {
//             for (float y = min.y; y < max.y; y++) {
//                 if (const auto cellIt = cells.find({x, y}); cellIt != cells.end()) {
//                     othEnts.insert(cellIt->second.begin(), cellIt->second.end());
//                 }
//             }
//         }

//         return othEnts;
//     }

// private:
//     glm::vec2 cellSize = glm::vec2(32.f, 32.f);
//     std::unordered_map<SpatialHashMapPosition, std::unordered_set<Ent>> cells;
//     std::unordered_map<Ent, glm::vec4> entLocations;
// };

///////////////////////////////////////////////////////////////////////////////////

inline void updateVelocityRec(World& world, Ent ent, const glm::vec2& vel) {
    if (auto childrenOpt = world.get_children(ent)) {
        for (const auto childEnt: childrenOpt.value().get()) {
            if (auto opt = world.get_components<Transform2D>(childEnt)) {
                auto [childTrans] = opt.value();
                childTrans.moveVelocity(vel);
            }
            updateVelocityRec(world, childEnt, vel);
        }
    }
}

inline void updateVelocitySys(LateFixedSystem, World& world) {
    for (auto [ent, velocity, trans]: world.view<Velocity, Transform2D>()) {
        if (velocity.vel != glm::vec2(0, 0)) {
            trans.moveVelocity(velocity.vel);
            updateVelocityRec(world, ent, velocity.vel);
            velocity.vel = glm::vec2(0, 0);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

inline void updatePositionSys(LateUnscaledFixedSystem, World& world) {
    for (auto [ent, trans]: world.view<Transform2D>()) {
        if (trans.needUpdatePosition) {
            trans.moveVelocity(trans.diffPosition);
            updateVelocityRec(world, ent, trans.diffPosition);
            trans.diffPosition = glm::vec2(0, 0);
            trans.needUpdatePosition = false;
        } else if (trans.needUpdatePositionGlobal) {
            trans.moveVelocity(trans.diffPosition);
            trans.diffPosition = glm::vec2(0, 0);
            trans.needUpdatePositionGlobal = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

inline void collisionSys(LateFixedSystem, World& world) {
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

    for (auto [othEnt, othTrig, othTrans]: world.view<const Trigger, Transform2D>()) {
        if (othTrans.hashMapUpdated) {
            othTrans.hashMapUpdated = false;
            spatialHashMap.emplace_or_replace(othEnt, othTrig.col, othTrans.getModel());
        }
    }

    for (auto [othEnt, othCol, othTrans]: world.view<const Collider, Transform2D>()) {
        if (othTrans.hashMapUpdated) {
            othTrans.hashMapUpdated = false;
            spatialHashMap.emplace_or_replace(othEnt, othCol.col, othTrans.getModel());
        }
    }

    for (auto [dynEnt, dynTrig, dynTrans]: world.view<const Trigger, Transform2D>(with<Velocity>)) {
        auto list = spatialHashMap.getIntersectList(dynEnt, dynTrig.col, dynTrans.getModel());

        if (auto onCollisionEnterOpt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
            auto [dynCollisionEnter] = onCollisionEnterOpt.value();
            for (const auto oldEnt: dynCollisionEnter.oldOthCols) {
                if (world.entity_exists(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [dynCollisionExit] = onCollisionExitOpt.value();
                            dynCollisionExit.othCols.emplace(oldEnt);
                        } else {
                            world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [oldCollisionExit] = onCollisionExitOpt.value();
                            oldCollisionExit.othCols.emplace(dynEnt);
                        } else {
                            world.add_components(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform2D>(oldEnt)) {
                            if (world.has_components<Collider>(oldEnt) || world.has_components<Trigger>(oldEnt)) {
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
                                            world.add_components(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add_components(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add_components(oldEnt, OnCollisionExit({dynEnt}));
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
                if (world.entity_exists(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [onCollisionExitDyn] = opt.value();
                            onCollisionExitDyn.othCols.emplace(oldEnt);
                        } else {
                            world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [onCollisionExitOld] = opt.value();
                            onCollisionExitOld.othCols.emplace(dynEnt);
                        } else {
                            world.add_components(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform2D>(oldEnt)) {
                            if (world.has_components<Collider>(oldEnt) || world.has_components<Trigger>(oldEnt)) {
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
                                            world.add_components(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add_components(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add_components(oldEnt, OnCollisionExit({dynEnt}));
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
            if (auto oldTransformOpt = world.getThisFrame<Transform2D>(othEnt)) {
                if (world.has_components<Collider>(othEnt) || world.has_components<Trigger>(othEnt)) {
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
                                world.add_components(dynEnt, OnCollisionEnter({othEnt}));
                            }
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(othEnt)) {
                                auto [onCollisionEnterOth] = opt.value();
                                onCollisionEnterOth.othCols.emplace(dynEnt);
                            } else {
                                world.add_components(othEnt, OnCollisionEnter({dynEnt}));
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto [dynEnt, dynCol, dynTrans]: world.view<const Collider, Transform2D>(with<Velocity>)) {
        auto list = spatialHashMap.getIntersectList(dynEnt, dynCol.col, dynTrans.getModel());

        if (auto onCollisionEnterOpt = world.getThisFrame<OnCollisionEnter>(dynEnt)) {
            auto [dynCollisionEnter] = onCollisionEnterOpt.value();
            for (const auto oldEnt: dynCollisionEnter.oldOthCols) {
                if (world.entity_exists(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [dynCollisionExit] = onCollisionExitOpt.value();
                            dynCollisionExit.othCols.emplace(oldEnt);
                        } else {
                            world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto onCollisionExitOpt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [oldCollisionExit] = onCollisionExitOpt.value();
                            oldCollisionExit.othCols.emplace(dynEnt);
                        } else {
                            world.add_components(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform2D>(oldEnt)) {
                            if (world.has_components<Collider>(oldEnt) || world.has_components<Trigger>(oldEnt)) {
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
                                            world.add_components(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add_components(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                        if (world.has_components<Collider>(oldEnt)) {
                                            // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale());
                                            glm::vec2 antiVel = intersectWithMTVRes.second;
                                            dynTrans.moveVelocity(antiVel);
                                            if (world.has_children(dynEnt)) {
                                                updateVelocityRec(world, dynEnt, antiVel);
                                            }
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add_components(oldEnt, OnCollisionExit({dynEnt}));
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
                if (world.entity_exists(oldEnt)) {
                    if (!list.contains(oldEnt)) {
                        if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                            auto [onCollisionExitDyn] = opt.value();
                            onCollisionExitDyn.othCols.emplace(oldEnt);
                        } else {
                            world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                        }
                        if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                            auto [onCollisionExitOld] = opt.value();
                            onCollisionExitOld.othCols.emplace(dynEnt);
                        } else {
                            world.add_components(oldEnt, OnCollisionExit({dynEnt}));
                        }
                    } else {
                        if (auto oldTransformOpt = world.getThisFrame<Transform2D>(oldEnt)) {
                            if (world.has_components<Collider>(oldEnt) || world.has_components<Trigger>(oldEnt)) {
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
                                            world.add_components(dynEnt, OnCollisionStay({oldEnt}));
                                        }
                                        if (auto opt = world.getThisFrame<OnCollisionStay>(oldEnt)) {
                                            auto [oldCollisionStay] = opt.value();
                                            oldCollisionStay.othCols.emplace(dynEnt);
                                        } else {
                                            world.add_components(oldEnt, OnCollisionStay({dynEnt}));
                                        }
                                        if (world.has_components<Collider>(oldEnt)) {
                                            // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), oldTransform.getPosition(), col, oldTransform.getScale());
                                            glm::vec2 antiVel = intersectWithMTVRes.second;
                                            dynTrans.moveVelocity(antiVel);
                                            if (world.has_children(dynEnt)) {
                                                updateVelocityRec(world, dynEnt, antiVel);
                                            }
                                        }
                                    }
                                } else {
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(dynEnt)) {
                                        auto [onCollisionExitDyn] = opt.value();
                                        onCollisionExitDyn.othCols.emplace(oldEnt);
                                    } else {
                                        world.add_components(dynEnt, OnCollisionExit({oldEnt}));
                                    }
                                    if (auto opt = world.getThisFrame<OnCollisionExit>(oldEnt)) {
                                        auto [onCollisionExitOld] = opt.value();
                                        onCollisionExitOld.othCols.emplace(dynEnt);
                                    } else {
                                        world.add_components(oldEnt, OnCollisionExit({dynEnt}));
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
            if (auto oldTransformOpt = world.getThisFrame<Transform2D>(othEnt)) {
                if (world.has_components<Collider>(othEnt) || world.has_components<Trigger>(othEnt)) {
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
                                world.add_components(dynEnt, OnCollisionEnter({othEnt}));
                            }
                            if (auto opt = world.getThisFrame<OnCollisionEnter>(othEnt)) {
                                auto [onCollisionEnterOth] = opt.value();
                                onCollisionEnterOth.othCols.emplace(dynEnt);
                            } else {
                                world.add_components(othEnt, OnCollisionEnter({dynEnt}));
                            }
                            if (world.has_components<Collider>(othEnt)) {
                                // glm::vec2 antiVel = collisionResolution(dynTrans.getPosition(), dynCol.col, dynTrans.getScale(), othTransform.getPosition(), col, othTransform.getScale());
                                glm::vec2 antiVel = intersectWithMTVRes.second;
                                dynTrans.moveVelocity(antiVel);
                                if (world.has_children(dynEnt)) {
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
            world.remove_components<OnCollisionEnter>(entCollision);
        }
    }

    for (auto [entCollision, collision]: world.view<OnCollisionStay>()) {
        if (collision.othCols.empty()) {
            world.remove_components<OnCollisionStay>(entCollision);
        }
    }

    for (auto [entCollision, collision]: world.view<OnCollisionExit>()) {
        if (collision.othCols.empty()) {
            world.remove_components<OnCollisionExit>(entCollision);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

inline void purgeCollisionSys(LateUnscaledFixedSystem, World& world) {
    auto [spatialHashMap] = world.resource<SpatialHashMap>();

    for (const auto othEnt: world.getDestroyedEnts()) {
        spatialHashMap.erase(othEnt);
        if (world.has_components<OnCollisionEnter>(othEnt) || world.has_components<OnCollisionStay>(othEnt) || world.has_components<OnCollisionExit>(othEnt)) {
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
}

///////////////////////////////////////////////////////////////////////////////////
