#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <any>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <semaphore>
#include <functional>
#include <concepts>
#include <optional>
#include <cmath>

using Ent = std::size_t;
using Type = std::size_t;

template <typename... Filters>
struct With final {};
template <typename... Filters>
constinit With<Filters...> with;

template <typename... Excludes>
struct Without final {};
template <typename... Excludes>
constinit Without<Excludes...> without;

struct WithInactive final {};
constinit WithInactive withInactive;

class IsInactive final {};
class DontDestroyOnLoad final {};

class StartSystem final {};
constinit StartSystem startSystem;
class MainSystem final {};
constinit MainSystem mainSystem;
class MainFixedSystem final {};
constinit MainFixedSystem mainFixedSystem;
class ThreadedSystem final {};
constinit ThreadedSystem threadedSystem;
class ThreadedFixedSystem final {};
constinit ThreadedFixedSystem threadedFixedSystem;
class LateSystem final {};
constinit LateSystem lateSystem;
class LateFixedSystem final {};
constinit LateFixedSystem lateFixedSystem;
class SceneSystem final {};

template <typename T>
concept IsNotEmptyConcept = [] -> bool {
    static_assert(!std::is_empty_v<T>, "Impossible de requeter un Marker (objet de taille 0)");
    return true;
}();

template <typename T>
concept IsFinalConcept = [] -> bool {
    static_assert(std::is_final_v<T>, "Impossible d'ajouter un composant non final (class *** final {})");
    return true;
}();

///////////////////////////////////////////////////////////////////////////////////

// class CompAny final {
// public:
//     constexpr CompAny() noexcept:
//         manager(nullptr) {
//     }

//     CompAny(const CompAny& other) {
//         if (!other.has_value()) {
//             manager = nullptr;
//         } else {
//             CompArg arg;
//             arg.any = this;
//             other.manager(OP_CLONE, &other, &arg);
//         }
//     }

//     CompAny(CompAny&& other) noexcept {
//         if (!other.has_value()) {
//             manager = nullptr;
//         } else {
//             CompArg arg;
//             arg.any = this;
//             other.manager(OP_TRANSFER, &other, &arg);
//         }
//     }

//     template <typename T> requires (std::copy_constructible<T>)
//     CompAny(T&& value):
//         data(new T{std::move(value)}),
//         manager(&compAnyManager<T>) {
//     }

//     template <typename T, typename... Args> requires (std::constructible_from<T, Args...>)
//     CompAny(std::in_place_type_t<T>, Args&&... args):
//         data(new T{std::forward<Args>(args)...}),
//         manager(&compAnyManager<T>) {
//     }

//     ~CompAny() {
//         reset();
//     }

//     CompAny& operator=(const CompAny& rhs) {
//         *this = CompAny(rhs);
//         return *this;
//     }

//     CompAny& operator=(CompAny&& rhs) noexcept {
//         if (!rhs.has_value()) {
//             reset();
//         } else if (this != &rhs) {
//             reset();
//             CompArg arg;
//             arg.any = this;
//             rhs.manager(OP_TRANSFER, &rhs, &arg);
//         }
//         return *this;
//     }

//     template <typename T> requires (std::copy_constructible<T>)
//     CompAny& operator=(T&& rhs) {
//         *this = CompAny(std::move(rhs));
//         return *this;
//     }

// public:
//     template <typename T, typename... Args> requires (std::constructible_from<T, Args...>)
//     T& emplace(Args&&... args) {
//         data = new T{std::forward<Args>(args)...};
//         manager = &compAnyManager<T>;
//         return *static_cast<T*>(data);
//     }

//     void swap(CompAny& rhs) noexcept {
//         if (!has_value() && !rhs.has_value()) {
//             return;
//         }

//         if (has_value() && rhs.has_value()) {
//             if (this == &rhs) {
//                 return;
//             }

//             CompAny tmp;
//             CompArg arg;
//             arg.any = &tmp;
//             rhs.manager(OP_TRANSFER, &rhs, &arg);
//             arg.any = &rhs;
//             manager(OP_TRANSFER, this, &arg);
//             arg.any = this;
//             tmp.manager(OP_TRANSFER, &tmp, &arg);
//         } else {
//             CompAny* empty = !has_value() ? this : &rhs;
//             CompAny* full = !has_value() ? &rhs : this;
//             CompArg arg;
//             arg.any = empty;
//             full->manager(OP_TRANSFER, full, &arg);
//         }
//     }

//     void reset() noexcept {
//         if (has_value()) {
//             manager(OP_DESTROY, this, nullptr);
//             manager = nullptr;
//         }
//     }

//     bool has_value() const {
//         return manager != nullptr;
//     }

//     const std::type_info& type() const noexcept {
//         if (!has_value()) {
//             return typeid(void);
//         }
//         CompArg arg;
//         manager(OP_TYPE, this, &arg);
//         return *arg.typeinfo;
//     }

// private:
//     enum CompOp: uint8_t {
//         OP_ACCESS, OP_TYPE, OP_CLONE, OP_DESTROY, OP_TRANSFER
//     };

//     union CompArg {
//         void* data;
//         const std::type_info* typeinfo;
//         CompAny* any;
//     };

// private:
//     template <typename T>
//     static void compAnyManager(CompOp op, const CompAny* any, CompArg* arg) {
//         auto ptr = static_cast<const T*>(any->data);
//         switch (op) {
//             case CompOp::OP_ACCESS:
//                 arg->data = const_cast<T*>(ptr);
//                 break;
//             case CompOp::OP_TYPE:
//                 arg->typeinfo = &typeid(T);
//                 break;
//             case CompOp::OP_CLONE:
//                 arg->any->data = new T{*ptr};
//                 arg->any->manager = any->manager;
//                 break;
//             case CompOp::OP_DESTROY:
//                 delete ptr;
//                 break;
//             case CompOp::OP_TRANSFER:
//                 arg->any->data = any->data;
//                 arg->any->manager = any->manager;
//                 const_cast<CompAny*>(any)->manager = nullptr;
//                 break;
//         }
//     }

// public:
//     template <typename T> requires (!std::same_as<T, void> && (std::copy_constructible<T> || std::is_rvalue_reference_v<T> || std::is_lvalue_reference_v<T>))
//     constexpr std::optional<T> comp_any_cast(CompAny& any) {
//         if (any.manager == &CompAny::compAnyManager<T> || any.type() == typeid(T)) {
//             CompArg arg;
//             any.manager(OP_ACCESS, &any, &arg);
//             return static_cast<T>(*arg.data);
//         }
//         return std::nullopt;
//     }

// private:
//     void* data;
//     void(*manager)(CompOp, const CompAny*, CompArg*);
// };

///////////////////////////////////////////////////////////////////////////////////

class CompPool final {
friend class Archetype;
friend class LiteArchetype;
friend class LateUpgrade;
public:
    [[nodiscard]] CompPool() noexcept = default;

    [[nodiscard]] CompPool(const Ent ent, const std::any& a) noexcept:
        comps({{ent, a}}) {
    }

private:
    constexpr auto emplace(this auto&& self, const Ent ent, const std::any& a) noexcept -> void {
        std::move(self).comps.emplace(ent, a);
    }

    [[nodiscard]] constexpr auto get(this auto&& self, const Ent ent) noexcept -> auto&& {
        return std::move(self).comps.at(ent);
    }

    constexpr auto copy(this auto&& self, const Ent ent, const CompPool& oth) noexcept -> void {
        std::move(self).comps.emplace(ent, oth.comps.at(ent));
    }

    constexpr auto remove(this auto&& self, const Ent ent) noexcept -> void {
        std::move(self).comps.erase(ent);
    }

private:
    std::unordered_map<Ent, std::any> comps;
};

///////////////////////////////////////////////////////////////////////////////////

struct ArchetypeCreateWith final {};
constinit ArchetypeCreateWith archetypeCreateWith;

struct ArchetypeCreateWithout final {};
constinit ArchetypeCreateWithout archetypeCreateWithout;

class Archetype final {
friend class Registry;
friend class LiteArchetype;
friend class LateUpgrade;
template<typename... Ts>
friend class View;
private:
    Archetype() noexcept = default;

    Archetype(const Ent ent, const std::unordered_map<Type, std::any>& anyes) noexcept:
        ents({ent}),
        pools(anyes.size()) {
        for (const auto& pair: anyes) {
            pools.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(pair.first),
                std::forward_as_tuple(ent, pair.second)
            );
        }
    }

    Archetype(ArchetypeCreateWith, Archetype& oldArch, const Ent ent, const std::any& a) noexcept:
        ents({ent}),
        pools(oldArch.pools.size() + 1) {
        for (const auto& pair: oldArch.pools) {
            pools.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(pair.first),
                std::forward_as_tuple(ent, pair.second.comps.at(ent))
            );
        }
        pools.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(a.type().hash_code()),
            std::forward_as_tuple(ent, a)
        );
        oldArch.destroy(ent);
    }

    Archetype(ArchetypeCreateWithout, Archetype& oldArch, const Ent ent, const Type type) noexcept:
        ents({ent}),
        pools(oldArch.pools.size() - 1) {
        for (const auto& pair: oldArch.pools) {
            if (pair.first != type) {
                pools.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(pair.first),
                    std::forward_as_tuple(ent, pair.second.comps.at(ent))
                );
            }
        }
        oldArch.destroy(ent);
    }

private:
    constexpr auto newEnt(this auto&& self, const Ent ent, const std::unordered_map<Type, std::any>& anyes) noexcept -> void {
        std::move(self).ents.emplace(ent);
        for (const auto& pair: anyes) {
            std::move(self).pools.at(pair.first).emplace(ent, pair.second);
        }
    }

    constexpr auto add(this auto&& self, const Ent ent, Archetype& oldArch, const std::any& a) noexcept -> void {
        std::move(self).ents.emplace(ent);
        for (const auto& pair: oldArch.pools) {
            std::move(self).pools.at(pair.first).copy(ent, pair.second);
        }
        std::move(self).pools.at(a.type().hash_code()).emplace(ent, a);
        oldArch.destroy(ent);
    }

    constexpr auto remove(this auto&& self, const Ent ent, Archetype& oldArch, const Type type) noexcept -> void {
        std::move(self).ents.emplace(ent);
        for (const auto& pair: oldArch.pools) {
            if (pair.first != type) {
                std::move(self).pools.at(pair.first).copy(ent, pair.second);
            }
        }
        oldArch.destroy(ent);
    }

    [[nodiscard]] constexpr auto get(this auto&& self, const Ent ent, const Type type) noexcept -> auto&& {
        return std::move(self).pools.at(type).get(ent);
    }

    [[nodiscard]] constexpr auto getTypes(this auto&& self, const Ent ent) noexcept -> const std::vector<std::string> {
        std::vector<std::string> types;
        for (auto& pool: std::move(self).pools) {
            types.emplace_back(pool.second.comps.at(ent).type().name());
        }
        return types;
    }

    auto destroy(this auto&& self, const Ent ent) noexcept -> void {
        std::move(self).ents.erase(ent);
        for (auto& pool: std::move(self).pools) {
            pool.second.remove(ent);
        }
    }

    [[nodiscard]] constexpr auto empty(this auto&& self) noexcept -> bool {
        return std::move(self).ents.empty();
    }

    [[nodiscard]] constexpr auto size(this auto&& self) noexcept -> std::size_t {
        return std::move(self).ents.size();
    }

    [[nodiscard]] constexpr auto containsType(this auto&& self, const Type type) noexcept -> bool {
        return std::move(self).pools.contains(type);
    }

private:
    template <typename... Ts>
    [[nodiscard]] constexpr auto getTupleWithEnt(this auto&& self, const Ent ent) noexcept -> std::tuple<const Ent, Ts&...> {
        return std::forward_as_tuple(ent, std::any_cast<Ts&>(std::move(self).get(ent, typeid(Ts).hash_code()))...);
    }

private:
    [[nodiscard]] constexpr auto isTotalyCompatibleLate(this auto&& self, const std::unordered_map<Type, std::any>& anyes) noexcept -> bool {
        if (anyes.size() != std::move(self).pools.size()) {
            return false;
        }
        for (const auto& pair: anyes) {
            if (!std::move(self).pools.contains(pair.first)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr auto isTotalyCompatibleLate(this auto&& self, const Archetype& oldArch, const Type type) noexcept -> bool {
        if (oldArch.pools.size() + 1 != std::move(self).pools.size()) {
            return false;
        }
        if (!std::move(self).pools.contains(type)) {
            return false;
        }
        for (const auto& pair: oldArch.pools) {
            if (!std::move(self).pools.contains(pair.first)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr auto isTotalyCompatibleWithoutLate(this auto&& self, const Archetype& oldArch, const Type type) noexcept -> bool {
        if (oldArch.pools.size() - 1 != std::move(self).pools.size() || std::move(self).pools.contains(type)) {
            return false;
        }
        for (const auto& pair: oldArch.pools) {
            if (!std::move(self).pools.contains(pair.first) && pair.first != type) {
                return false;
            }
        }
        return true;
    }

private:
    std::unordered_set<Ent> ents;
    std::unordered_map<Type, CompPool> pools;
};

///////////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
class View final {
friend class Registry;
friend class LiteRegistry;
private:
    constexpr View(std::unordered_set<Archetype*>&& newArchs) noexcept:
        archs(std::move(newArchs)) {
    }

public:
    [[nodiscard]] constexpr auto empty() const noexcept -> bool {
        if (archs.empty()) {
            return true;
        }
        for (const auto* arch: archs) {
            if (arch->size() > 0) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t {
        std::size_t newSize = 0;
        for (const auto* arch: archs) {
            newSize += arch->size();
        }
        return newSize;
    }

private:
    class ViewIterator final {
    friend class View;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::tuple<const Ent, Ts&...>;
        using element_type = value_type;
        using pointer = value_type*;
        using reference = value_type&;
        using difference_type = std::ptrdiff_t;

    public:
        ViewIterator(const std::unordered_set<Archetype*>& newArchs, std::unordered_set<Archetype*>::const_iterator newArchsIt) noexcept:
            archsIt(newArchsIt),
            archs(newArchs) {
            if (archsIt != newArchs.end()) {
                entsIt = (*archsIt)->ents.begin();
            }
        }

        [[nodiscard]] constexpr auto operator *() const noexcept -> value_type {
            return (*archsIt)->getTupleWithEnt<Ts...>((*entsIt));
        }

        constexpr auto operator ++() noexcept -> ViewIterator& {
            entsIt++;
            if (entsIt == (*archsIt)->ents.end()) {
                archsIt++;
                if (archsIt != archs.end()) {
                    entsIt = (*archsIt)->ents.begin();
                }
            }
            return *this;
        }

        [[nodiscard]] friend constexpr auto operator !=(const ViewIterator& a, const ViewIterator& b) noexcept -> bool {
            return a.archsIt != b.archsIt;
        }

    private:
        std::unordered_set<Archetype*>::const_iterator archsIt;
        std::unordered_set<Ent>::iterator entsIt;
        const std::unordered_set<Archetype*>& archs;
    };

public:
    [[nodiscard]] constexpr auto begin() const noexcept -> ViewIterator{
        return {archs, archs.begin()};
    }

    [[nodiscard]] constexpr auto end() const noexcept -> ViewIterator {
        return {archs, archs.end()};
    }

private:
    const std::unordered_set<Archetype*> archs;
};

///////////////////////////////////////////////////////////////////////////////////

class Registry final {
friend class World;
friend class LateUpgrade;
private:
    Registry() noexcept:
        emptyArch(new Archetype()) {
    }

private:
    ~Registry() noexcept {
        for (auto* arch: archs) {
            delete arch;
        }
        delete emptyArch;
    }

    [[nodiscard]] constexpr auto getEntToken() noexcept -> Ent {
        Ent ent = lastEnt++;

        if (!entTokens.empty()) {
            lastEnt--;
            ent = entTokens.back();
            entTokens.pop_back();
        }

        entArch.emplace(ent, emptyArch);

        return ent;
    }

    constexpr auto newEnt(const Ent ent, const std::unordered_map<Type, std::any>& anyes) noexcept -> void {
        auto entArchIt = entArch.find(ent);
        if (entArchIt->second->size() > 0) {
            printf("ZerEngine: Impossible d'inserer une entité deja existante - [%zu]\n", ent);
            return;
        }

        std::unordered_set<Archetype*> compatiblesArchs(archs);
        for (const auto& pairAny: anyes) {
            filterArchsByType(pairAny.first, compatiblesArchs);
        }
        for (auto* arch: compatiblesArchs) {
            if (arch->isTotalyCompatibleLate(anyes)) {
                arch->newEnt(ent, anyes);
                entArchIt->second = arch;
                return;
            }
        }

        auto* arch = new Archetype(ent, anyes);
        archs.emplace(arch);
        entArchIt->second = arch;
        for (const auto& pair: arch->pools) {
            emplaceArchByType(pair.first, arch);
        }
    }

    constexpr auto add(const Ent ent, const std::any& any) noexcept -> void {
        auto entArchIt = entArch.find(ent);
        if (entArchIt == entArch.end()) {
            printf("ZerEngine: Impossible d'ajouter un composant sur une entité inexistante - [%zu]\n", ent);
            return;
        }

        if (entArchIt->second->containsType(any.type().hash_code())) {
            printf("ZerEngine: Impossible d'ajouter 2 composants identiques  - [%zu] - %s\n", ent, any.type().name());
            return;
        }

        auto* oldArch = entArchIt->second;

        std::unordered_set<Archetype*> compatiblesArchs(archs);
        for (const auto& pairPools: oldArch->pools) {
            filterArchsByType(pairPools.first, compatiblesArchs);
        }
        filterArchsByType(any.type().hash_code(), compatiblesArchs);
        for (auto* arch: compatiblesArchs) {
            if (arch->isTotalyCompatibleLate(*oldArch, any.type().hash_code())) {
                arch->add(ent, *oldArch, any);
                entArchIt->second = arch;
                emplaceArchByType(any.type().hash_code(), arch);
                removeOldArchIfEmpty(oldArch);
                return;
            }
        }

        auto* arch = new Archetype(archetypeCreateWith, *oldArch, ent, any);
        archs.emplace(arch);
        entArchIt->second = arch;
        for (const auto& pair: arch->pools) {
            emplaceArchByType(pair.first, arch);
        }
        removeOldArchIfEmpty(oldArch);
    }

    constexpr auto remove(const Ent ent, const Type type) noexcept -> void {
        auto entArchIt = entArch.find(ent);
        if (entArchIt == entArch.end()) {
            printf("ZerEngine: Impossible de supprimer un composant sur une entite inexistante - [%zu]\n", ent);
            return;
        }

        if (!entArchIt->second->containsType(type)) {
            printf("ZerEngine: Impossible de supprimer un composant qui n'existe pas - [%zu]\n", ent);
            return;
        }

        auto* oldArch = entArchIt->second;

        std::unordered_set<Archetype*> compatiblesArchs(archs);
        for (const auto& pairPools: oldArch->pools) {
            if (pairPools.first != type) {
                filterArchsByType(pairPools.first, compatiblesArchs);
            }
        }
        for (auto* arch: compatiblesArchs) {
            if (arch->isTotalyCompatibleWithoutLate(*oldArch, type)) {
                arch->remove(ent, *oldArch, type);
                entArchIt->second = arch;
                removeOldArchIfEmpty(oldArch);
                return;
            }
        }

        auto* arch = new Archetype(archetypeCreateWithout, *oldArch, ent, type);
        archs.emplace(arch);
        entArchIt->second = arch;
        for (const auto& pair: arch->pools) {
            emplaceArchByType(pair.first, arch);
        }
        removeOldArchIfEmpty(oldArch);
    }

    [[nodiscard]] constexpr auto exist(const Ent ent) const noexcept -> bool {
        return entArch.contains(ent);
    }

    [[nodiscard]] constexpr auto has(const Ent ent, const std::initializer_list<Type>& types) const noexcept -> bool {
        auto entArchIt = entArch.find(ent);
        if (entArchIt == entArch.end()) {
            return false;
        }
        for (const auto type: types) {
            if (!entArchIt->second->pools.contains(type)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr auto get(this auto&& self, const Ent ent, const Type type) noexcept -> auto&& {
        return self.entArch.at(ent)->get(ent, type);
    }

    constexpr auto getTypes(const Ent ent) const noexcept -> const std::vector<std::string> {
        return entArch.at(ent)->getTypes(ent);
    }

    constexpr auto destroy(const Ent ent) noexcept -> void {
        auto entArchIt = entArch.find(ent);
        if (entArchIt == entArch.end()) {
            printf("ZerEngine: Impossible de detruire une entitée qui n'existe pas\n");
            return;
        }
 
        auto* arch = entArchIt->second;
        arch->destroy(ent);
        removeOldArchIfEmpty(arch);
        entArch.erase(entArchIt);
        entTokens.push_back(ent);
        detachChildren(ent);
        removeParent(ent);
    }

    constexpr auto clean() noexcept -> void {
        for (auto* arch: archs) {
            delete arch;
        }
        delete emptyArch;

        emptyArch = new Archetype();
        lastEnt = 1;
        entTokens.clear();
        archs.clear();
        entArch.clear();
        archsByType.clear();
        parentChildrens.clear();
        childrenParent.clear();
    }

private:
    constexpr auto appendChildrenInactiveRecDown(const Ent parentEnt) noexcept -> void {
        if (auto childrenOpt = getChildren(parentEnt)) {
            for (auto childEnt: childrenOpt.value().get()) {
                if (!has(childEnt, {typeid(IsInactive).hash_code()})) {
                    add(childEnt, std::make_any<IsInactive>());
                }
                appendChildrenInactiveRecDown(childEnt);
            }
        }
    }

    constexpr auto appendChildrenInactiveRecUp(const Ent parentEnt) noexcept -> void {
        if (has(parentEnt, {typeid(IsInactive).hash_code()})) {
            if (auto childrenOpt = getChildren(parentEnt)) {
                for (auto childEnt: childrenOpt.value().get()) {
                    if (!has(childEnt, {typeid(IsInactive).hash_code()})) {
                        add(childEnt, std::make_any<IsInactive>());
                    }
                    appendChildrenInactiveRecDown(childEnt);
                }
            }
            return;
        } else if (auto parentOpt = getParent(parentEnt)) {
            appendChildrenInactiveRecUp(parentOpt.value());
        }
    }

    constexpr auto appendChildrenDontDestroyOnLoadRecDown(const Ent parentEnt) noexcept -> void {
        if (auto childrenOpt = getChildren(parentEnt)) {
            for (auto childEnt: childrenOpt.value().get()) {
                if (!has(childEnt, {typeid(DontDestroyOnLoad).hash_code()})) {
                    add(childEnt, std::make_any<DontDestroyOnLoad>());
                }
                appendChildrenDontDestroyOnLoadRecDown(childEnt);
            }
        }
    }

    constexpr auto appendChildrenDontDestroyOnLoadRecUp(const Ent parentEnt) noexcept -> void {
        if (has(parentEnt, {typeid(DontDestroyOnLoad).hash_code()})) {
            if (auto childrenOpt = getChildren(parentEnt)) {
                for (auto childEnt: childrenOpt.value().get()) {
                    if (!has(childEnt, {typeid(DontDestroyOnLoad).hash_code()})) {
                        add(childEnt, std::make_any<DontDestroyOnLoad>());
                    }
                    appendChildrenDontDestroyOnLoadRecDown(childEnt);
                }
            }
            return;
        } else if (auto parentOpt = getParent(parentEnt)) {
            appendChildrenDontDestroyOnLoadRecUp(parentOpt.value());
        }
    }

    constexpr auto appendChildren(const Ent parentEnt, const std::unordered_set<Ent>& childrenEnt) noexcept -> void {
        auto parentIt = parentChildrens.find(parentEnt);
        if (parentIt == parentChildrens.end()) {
            parentIt = parentChildrens.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(parentEnt),
                std::forward_as_tuple()
            ).first;
        }
        for (const auto childEnt: childrenEnt) {
            if (childrenParent.contains(childEnt)) {
                printf("Children: Tu ne peux pas avoir deux parents Billy[%zu]\n", childEnt);
            } else if (parentEnt == childEnt) {
                printf("Children: Impossible d'etre son propre pere\n");  
            } else {
                childrenParent.emplace(childEnt, parentEnt);
                parentIt->second.emplace(childEnt);
            }
        }
        if (parentIt->second.empty()) {
            parentChildrens.erase(parentIt);
        }
        appendChildrenInactiveRecUp(parentEnt);
        appendChildrenDontDestroyOnLoadRecUp(parentEnt);
    }

    constexpr auto appendChildren(const Ent parentEnt, const std::vector<Ent>& childrenEnt) noexcept -> void {
        auto parentIt = parentChildrens.find(parentEnt);
        if (parentIt == parentChildrens.end()) {
            parentIt = parentChildrens.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(parentEnt),
                std::forward_as_tuple()
            ).first;
        }
        for (const auto childEnt: childrenEnt) {
            if (childrenParent.contains(childEnt)) {
                printf("Children: Tu ne peux pas avoir deux parents Billy[%zu]\n", childEnt);
            } else if (parentEnt == childEnt) {
                printf("Children: Impossible d'etre son propre pere\n");  
            } else {
                childrenParent.emplace(childEnt, parentEnt);
                parentIt->second.emplace(childEnt);
            }
        }
        if (parentIt->second.empty()) {
            parentChildrens.erase(parentIt);
        }
        appendChildrenInactiveRecUp(parentEnt);
        appendChildrenDontDestroyOnLoadRecUp(parentEnt);
    }

    constexpr auto detachChildren(const Ent parentEnt) noexcept -> void {
        if (auto parentIt = parentChildrens.find(parentEnt); parentIt != parentChildrens.end()) {
            for (const auto childEnt: parentIt->second) {
                if (auto childrenIt = childrenParent.find(childEnt); childrenIt != childrenParent.end()) {
                    childrenParent.erase(childrenIt);
                }
            }
            parentChildrens.erase(parentIt);
        }
    }

    constexpr auto removeParent(const Ent childEnt) noexcept -> void {
        if (auto childrenIt = childrenParent.find(childEnt); childrenIt != childrenParent.end()) {
            if (auto parentIt = parentChildrens.find(childrenIt->second); parentIt != parentChildrens.end()) {
                parentIt->second.erase(childEnt);
                if (parentIt->second.empty()) {
                    parentChildrens.erase(parentIt);
                }
            }
            childrenParent.erase(childrenIt);
        }
    }

    [[nodiscard]] constexpr auto hasChildren(const Ent parentEnt) const noexcept -> bool {
        return parentChildrens.contains(parentEnt);
    }

    [[nodiscard]] constexpr auto getChildren(const Ent parentEnt) const noexcept -> std::optional<std::reference_wrapper<const std::unordered_set<Ent>>> {
        if (auto parentIt = parentChildrens.find(parentEnt); parentIt != parentChildrens.end()) {
            return std::make_optional<std::reference_wrapper<const std::unordered_set<Ent>>>(std::reference_wrapper<const std::unordered_set<Ent>>(parentIt->second));
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr auto hasParent(const Ent childEnt) const noexcept -> bool {
        return childrenParent.contains(childEnt);
    }

    [[nodiscard]] constexpr auto getParent(const Ent childEnt) const noexcept -> std::optional<Ent> {
        if (auto childIt = childrenParent.find(childEnt); childIt != childrenParent.end()) {
            return childIt->second;
        }
        return std::nullopt;
    }

private:
    template <typename... Comps>
    [[nodiscard]] constexpr auto view(const std::initializer_list<Type>& compFilterTypes, const std::initializer_list<Type>& excludeTypes) const noexcept -> const View<Comps...> {
        std::unordered_set<Archetype*> internalArchs;
        if (compFilterTypes.size() > 0) {
            viewAddComp(internalArchs, compFilterTypes);
        } else {
            internalArchs = archs;
        }
        if (excludeTypes.size() > 0) {
            viewWithoutComp(internalArchs, excludeTypes);
        }
        return {std::move(internalArchs)};
    }

private:
    constexpr auto viewAddComp(std::unordered_set<Archetype*>& internalArchs, const std::initializer_list<Type>& compTypes) const noexcept -> void {
        std::size_t i = 0;
        for (const auto compType: compTypes) {
            if (i == 0) {
                if (auto archsByTypeIt = archsByType.find(compType); archsByTypeIt != archsByType.end()) {
                    internalArchs = archsByTypeIt->second;
                } else {
                    internalArchs.clear();
                    return;
                }
                i++;
            } else {
                if (auto archsByTypeIt = archsByType.find(compType); archsByTypeIt != archsByType.end()) {
                    const auto& othArchs = archsByTypeIt->second;
                    std::vector<Archetype*> toErase;
                    for (auto* arch: internalArchs) {
                        if (!othArchs.contains(arch)) {
                            toErase.emplace_back(arch);
                        }
                    }
                    for (auto* arch: toErase) {
                        internalArchs.erase(arch);
                    }
                } else {
                    internalArchs.clear();
                    return;
                }
            }
        }
    }

    constexpr auto viewWithoutComp(std::unordered_set<Archetype*>& internalArchs, const std::initializer_list<Type>& compTypes) const noexcept -> void {
        for (const auto compType: compTypes) {
            if (auto archsByTypeIt = archsByType.find(compType); archsByTypeIt != archsByType.end()) {
                for (auto* arch: archsByTypeIt->second) {
                    if (internalArchs.contains(arch)) {
                        internalArchs.erase(arch);
                    }
                }
            }
        }
    }

    constexpr auto filterArchsByType(const Type type, std::unordered_set<Archetype*>& compatibleArchs) noexcept -> void {
        std::unordered_set<Archetype*> newArchs;
        if (auto archsByTypeIt = archsByType.find(type); archsByTypeIt != archsByType.end()) {
            for (auto* arch: archsByTypeIt->second) {
                if (compatibleArchs.contains(arch)) {
                    newArchs.emplace(arch);
                }
            }
        }
        compatibleArchs = newArchs;
    }

private:
    constexpr auto emplaceArchByType(const Type type, Archetype* arch) noexcept -> void {
        if (auto archsByTypeIt = archsByType.find(type); archsByTypeIt != archsByType.end()) {
            archsByTypeIt->second.emplace(arch);
        } else {
            archsByType.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(type),
                std::forward_as_tuple(std::initializer_list<Archetype*>{arch})
            );
        }
    }

    constexpr auto removeOldArchIfEmpty(Archetype* oldArch) noexcept -> void {
        if (oldArch->size() <= 0 && oldArch != emptyArch) {
            for (const auto& pair: oldArch->pools) {
                archsByType.at(pair.first).erase(oldArch);
            }
            delete oldArch;
            archs.erase(oldArch);
        }
    }

private:
    Ent lastEnt = 1;
    std::vector<Ent> entTokens;
    Archetype* emptyArch;
    std::unordered_set<Archetype*> archs;
    std::unordered_map<Ent, Archetype*> entArch;
    std::unordered_map<Type, std::unordered_set<Archetype*>> archsByType;
    std::unordered_map<Ent, std::unordered_set<Ent>> parentChildrens;
    std::unordered_map<Ent, Ent> childrenParent;
};

///////////////////////////////////////////////////////////////////////////////////

class World;

class LateUpgrade final {
friend class World;
private:
    LateUpgrade() = default;

private:
    Ent newEnt(const Ent ent, const std::initializer_list<std::pair<const Type, std::any>>& newList) noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        addEnts.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(ent),
            std::forward_as_tuple(newList)
        );
        return ent;
    }

    void add(const Ent ent, const std::initializer_list<std::pair<const Type, std::any>>& newList) noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        if (auto addEntsIt = addEnts.find(ent); addEntsIt != addEnts.end()) {
            for (const auto& pair: newList) {
                if (!addEntsIt->second.contains(pair.first)) {
                    addEntsIt->second.emplace(
                        std::piecewise_construct,
                        std::forward_as_tuple(pair.first),
                        std::forward_as_tuple(pair.second)
                    );
                } else {
                    printf("No Add Sur Ent: Le Composant %s existe deja\n", pair.second.type().name());
                }
            }
        } else {
            auto addCompsIt = addComps.find(ent);
            if (addCompsIt == addComps.end()) {
                addComps.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(ent),
                    std::forward_as_tuple(newList)
                );
            } else {
                for (const auto& pair: newList) {
                    if (!addCompsIt->second.contains(pair.first)) {
                        addCompsIt->second.emplace(
                            std::piecewise_construct,
                            std::forward_as_tuple(pair.first),
                            std::forward_as_tuple(pair.second)
                        );
                    } else {
                        printf("No Add Sur Comp: Le Composant %s existe deja\n", pair.second.type().name());
                    }
                }
            }
        }
    }

    void remove(const Ent ent, const Type type) noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        if (!delEnts.contains(ent)) {
            auto addEntsIt = addEnts.find(ent);
            if (addEntsIt == addEnts.end() || !addEntsIt->second.contains(type)) {
                auto addCompsIt = addComps.find(ent);
                if (addCompsIt == addComps.end() || !addCompsIt->second.contains(type)) {
                    auto delCompsIt = delComps.find(ent);
                    if (delCompsIt == delComps.end()) {
                        delComps.emplace(
                            std::piecewise_construct,
                            std::forward_as_tuple(ent),
                            std::forward_as_tuple(
                                std::initializer_list<Type>{
                                    type
                                }
                            )
                        );
                    } else {
                        delCompsIt->second.emplace(
                            type
                        );
                    }
                } else {
                    addCompsIt->second.erase(type);
                }
            } else {
                addEntsIt->second.erase(type);
            }
        }
    }

    void appendChildren(const Ent parentEnt, const std::vector<Ent>& childrenEnt) {
        std::unique_lock<std::mutex> lock(mtx);
        if (auto addParentChildrenIt = addParentChildren.find(parentEnt); addParentChildrenIt != addParentChildren.end()) {
            for (const auto childEnt: childrenEnt) {
                addParentChildrenIt->second.emplace(childEnt);
            }
        } else {
            addParentChildren.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(parentEnt),
                std::forward_as_tuple(childrenEnt.begin(), childrenEnt.end())
            );
        }
    }

    void setActive(const Ent ent) {
        setActiveEnts.emplace(ent);
    }

    void setInactive(const Ent ent) {
        setInactiveEnts.emplace(ent);
    }

    void addDontDestroyOnLoad(const Ent ent) {
        addDontDestroyOnLoadEnts.emplace(ent);
    }

    void destroyChildRec(Registry& reg, const Ent parentEnt) noexcept {
        addEnts.erase(parentEnt);
        addComps.erase(parentEnt);
        delComps.erase(parentEnt);
        delEnts.emplace(parentEnt);
        if (addComps.contains(parentEnt)) {
            addComps.erase(parentEnt);
        }
        if (auto childrenOpt = reg.getChildren(parentEnt)) {
            for (const auto childEnt: childrenOpt.value().get()) {
                destroyChildRec(reg, childEnt);
            }
        }
    }

    void destroy(Registry& reg, const Ent ent) noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        destroyChildRec(reg, ent);
    }

    void loadScene(void(*newScene)(SceneSystem, World&)) noexcept {
        needClean = true;
        newSceneFunc = newScene;
    }

private:
    const std::vector<std::string> getTypes(const Ent ent) noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        std::vector<std::string> types;
        for (const auto& pairType: addEnts.at(ent)) {
            types.emplace_back(pairType.second.type().name());
        }
        for (const auto& pairType: addComps.at(ent)) {
            types.emplace_back(pairType.second.type().name());
        }
        return types;
    }

private:
    void setActiveRec(Registry& reg, const Ent ent) {
        if (reg.has(ent, {typeid(IsInactive).hash_code()})) {
            reg.remove(ent, typeid(IsInactive).hash_code());
            if (auto childrenOpt = reg.getChildren(ent)) {
                for (auto childEnt: childrenOpt.value().get()) {
                    setActiveRec(reg, childEnt);
                }
            }
        }
    }

    void setInactiveRec(Registry& reg, const Ent ent) {
        if (!reg.has(ent, {typeid(IsInactive).hash_code()})) {
            reg.add(ent, std::make_any<IsInactive>());
            if (auto childrenOpt = reg.getChildren(ent)) {
                for (auto childEnt: childrenOpt.value().get()) {
                    setInactiveRec(reg, childEnt);
                }
            }
        }
    }

    void addDontDetroyOnLoadRec(Registry& reg, const Ent ent) {
        if (!reg.has(ent, {typeid(DontDestroyOnLoad).hash_code()})) {
            reg.add(ent, std::make_any<DontDestroyOnLoad>());
            if (auto childrenOpt = reg.getChildren(ent)) {
                for (auto childEnt: childrenOpt.value().get()) {
                    addDontDetroyOnLoadRec(reg, childEnt);
                }
            }
        }
    }

private:
    void upgrade(World& world, Registry& reg) noexcept {
        for (const auto& pair: addComps) {
            for (const auto& pairType: pair.second) {
                reg.add(pair.first, pairType.second);
            }
        }

        for (const auto& pair: delComps) {
            for (const auto& type: pair.second) {
                reg.remove(pair.first, type);
            }
        }

        for (const auto& pair: addEnts) {
            reg.newEnt(pair.first, pair.second);
        }

        for (const Ent ent: delEnts) {
            reg.destroy(ent);
        }

        for (const auto ent: setActiveEnts) {
            setActiveRec(reg, ent);
        }

        for (const auto ent: setInactiveEnts) {
            setInactiveRec(reg, ent);
        }

        for (const auto ent: addDontDestroyOnLoadEnts) {
            addDontDetroyOnLoadRec(reg, ent);
        }

        for (const auto& pair: addParentChildren) {
            reg.appendChildren(pair.first, pair.second);
        }

        delEnts.clear();
        addEnts.clear();
        delComps.clear();
        addComps.clear();
        setActiveEnts.clear();
        setInactiveEnts.clear();
        addDontDestroyOnLoadEnts.clear();
        addParentChildren.clear();

        if (needClean) {
            needClean = false;
            std::unordered_map<Ent, std::unordered_set<Ent>> dontDestroyesHierarchies;
            for (auto [dontDestroyEnt]: reg.view({typeid(DontDestroyOnLoad).hash_code()}, {})) {
                auto* arch = reg.entArch.at(dontDestroyEnt);
                std::unordered_map<Type, std::any> comps;
                for (auto& pair: arch->pools) {
                    comps.emplace(pair.first, pair.second.comps.at(dontDestroyEnt));
                }
                dontDestroyes.emplace(dontDestroyEnt, comps);
                if (auto childrenIt = reg.parentChildrens.find(dontDestroyEnt); childrenIt != reg.parentChildrens.end()) {
                    dontDestroyesHierarchies.emplace(dontDestroyEnt, childrenIt->second);
                }
            }
            reg.clean();

            std::unordered_map<Ent, Ent> oldToNewEnts;
            for (const auto& pair: dontDestroyes) {
                auto newEntId = reg.getEntToken();
                reg.newEnt(newEntId, pair.second);
                oldToNewEnts.emplace(pair.first, newEntId);
            }
            dontDestroyes.clear();

            for (const auto& pair: dontDestroyesHierarchies) {
                auto newEntId = oldToNewEnts.at(pair.first);
                std::unordered_set<Ent> newChildrens;
                for (auto oldChildEnt: pair.second) {
                    if (auto oldToNewEntsIt = oldToNewEnts.find(oldChildEnt); oldToNewEntsIt != oldToNewEnts.end()) {
                        newChildrens.emplace(oldToNewEntsIt->second);
                    } else {
                        printf("Probleme sur la purge des scenes\n");
                    }
                }
                reg.appendChildren(newEntId, newChildrens);
            }

            newSceneFunc({}, world);
        }
    }

private:
    std::mutex mtx;
    std::unordered_map<Ent, std::unordered_map<Type, std::any>> addEnts;
    std::unordered_map<Ent, std::unordered_map<Type, std::any>> addComps;
    std::unordered_set<Ent> delEnts;
    std::unordered_map<Ent, std::unordered_set<Type>> delComps;
    std::unordered_map<Ent, std::unordered_map<Type, std::any>> dontDestroyes;

    std::unordered_map<Ent, std::unordered_set<Ent>> addParentChildren;

    std::unordered_set<Ent> setActiveEnts;
    std::unordered_set<Ent> setInactiveEnts;

    std::unordered_set<Ent> addDontDestroyOnLoadEnts;

    bool needClean = false;
    void(*newSceneFunc)(SceneSystem, World&);
};

///////////////////////////////////////////////////////////////////////////////////

class TypeMap final {
friend class World;
friend class ZerEngine;
private:
    constexpr void emplace(Type&& type, std::any&& any) noexcept {
        typeMap.emplace(std::move(type), std::move(any));
    }

    [[nodiscard]] constexpr auto&& get(this auto&& self, const Type type) noexcept {
        return self.typeMap.at(type);
    }

    constexpr void clear() noexcept {
        typeMap.clear();
    }

private:
    std::unordered_map<std::size_t, std::any> typeMap;
};

///////////////////////////////////////////////////////////////////////////////////

class World;

class ThreadPool final {
friend class Sys;
private:
    ThreadPool(World& newWorld, std::size_t newNbThreads) noexcept:
        world(newWorld),
        nbTasksDone(0),
        nbTasks(0),
        nbThreads(newNbThreads),
        isStop(false) {
        for (std::size_t i = 0; i < nbThreads; i++) {
            threads.emplace_back(std::bind(&ThreadPool::task, this));
        }
    }

private:
    ~ThreadPool() noexcept {
        stop();
        for (auto& thread: threads) {
            thread.join();
        }
    }

    void addTasks(const std::vector<void(*)(ThreadedSystem, World&)>& newTasks) noexcept {
        tasks.emplace_back(newTasks);
    }

    void addFixedTasks(const std::vector<void(*)(ThreadedFixedSystem, World&)>& newTasks) noexcept {
        fixedTasks.emplace_back(newTasks);
    }

    void run() noexcept {
        if (!tasks.empty()) {
            nbTasksDone = tasks[0].size();
            cvTask.notify_all();
        } else {
            nbTasksDone = 0;
        }
    }

    void fixedRun() noexcept {
        if (!fixedTasks.empty()) {
            nbTasksDone = fixedTasks[0].size();
            cvTask.notify_all();
        } else {
            nbTasksDone = 0;
        }
    }

    void wait() noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        cvFinished.wait(lock, [&]() {
            if (!tasks.empty() && nbTasksDone != 0) {
               cvTask.notify_all(); 
            }
            return (tasks.empty() && (nbTasks == 0));
        });
    }

    void fixedWait() noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        cvFinished.wait(lock, [&]() {
            if (!tasks.empty() && nbTasksDone != 0) {
               cvTask.notify_all(); 
            }
            return (fixedTasks.empty() && (nbTasks == 0));
        });
    }

private:
    void task() noexcept {
        srand(time(NULL));
        std::unique_lock<std::mutex> lock(mtx);
        while (true) {
            cvTask.wait(lock, [&]() {
                return (nbTasks < nbThreads) && (((!tasks.empty() || !fixedTasks.empty()) && nbTasksDone != 0) || isStop);
            });
            if (isStop && tasks.empty() && fixedTasks.empty()) {
                return;
            }

            if (!tasks.empty()) {
                nbTasks++;
                auto newTask = tasks[0].back();
                tasks[0].pop_back();
                nbTasksDone--;
                lock.unlock();

                newTask({}, world);

                lock.lock();
                nbTasks--;

                if (nbTasksDone == 0 && nbTasks == 0) {
                    tasks.erase(tasks.begin());
                    if (!tasks.empty()) {
                        nbTasksDone = tasks[0].size();
                        cvFinished.notify_one();
                    }
                }

                if (tasks.empty() && nbTasks == 0) {
                    cvFinished.notify_one();
                }
            } else {
                nbTasks++;
                auto newTask = fixedTasks[0].back();
                fixedTasks[0].pop_back();
                nbTasksDone--;
                lock.unlock();

                newTask({}, world);

                lock.lock();
                nbTasks--;

                if (nbTasksDone == 0 && nbTasks == 0) {
                    fixedTasks.erase(fixedTasks.begin());
                    if (!fixedTasks.empty()) {
                        nbTasksDone = fixedTasks[0].size();
                        cvFinished.notify_one();
                    }
                }

                if (fixedTasks.empty() && nbTasks == 0) {
                    cvFinished.notify_one();
                }
            }
        }
    }

    void stop() noexcept {
        std::unique_lock<std::mutex> lock(mtx);
        isStop = true;
        cvTask.notify_all();
    }

private:
    World& world;
    std::vector<std::vector<void(*)(ThreadedSystem, World&)>> tasks;
    std::vector<std::vector<void(*)(ThreadedFixedSystem, World&)>> fixedTasks;
    std::mutex mtx;
    std::size_t nbTasksDone;
    std::condition_variable cvTask;
    std::condition_variable cvFinished;
    std::vector<std::thread> threads;
    std::size_t nbTasks;
    std::size_t nbThreads;
    bool isStop;
};

///////////////////////////////////////////////////////////////////////////////////

class Sys final {
friend class World;
friend class ZerEngine;
private:
    Sys(World& world) noexcept:
        threadpool(world, std::thread::hardware_concurrency() - 1),
        isUseMultithreading(true)
    {
        srand(time(NULL));
    }

private:
    constexpr void useMultithreading(bool newVal) noexcept {
        isUseMultithreading = newVal;
    }

    constexpr void addStartSys(void(*const func)(StartSystem, World&)) noexcept {
        startSystems.emplace_back(func);
    }

    constexpr void addMainCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(MainSystem, World&)>&& funcs) noexcept {
        mainSystems.emplace_back(cond, std::move(funcs));
    }

    constexpr void addMainFixedCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(MainFixedSystem, World&)>&& funcs) noexcept {
        mainFixedSystems.emplace_back(cond, std::move(funcs));
    }

    constexpr void addThreadedCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(ThreadedSystem, World&)>&& funcs) noexcept {
        threadedSystems.emplace_back(cond, std::move(funcs));
    }

    constexpr void addThreadedFixedCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(ThreadedFixedSystem, World&)>&& funcs) noexcept {
        threadedFixedSystems.emplace_back(cond, std::move(funcs));
    }

    constexpr void addLateCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(LateSystem, World&)>&& funcs) noexcept {
        lateSystems.emplace_back(cond, std::move(funcs));
    }

    constexpr void addLateFixedCondSys(bool(*const cond)(World&), std::initializer_list<void(*)(LateFixedSystem, World&)>&& funcs) noexcept {
        lateFixedSystems.emplace_back(cond, std::move(funcs));
    }

    void start(World& world) const noexcept {
        for (const auto& func: startSystems) {
            func({}, world);
        }
    }

    void run(World& world) noexcept {
        for (const auto& mainFunc: mainSystems) {
            if (mainFunc.first == nullptr || mainFunc.first(world)) {
                for (const auto& mainRow: mainFunc.second) {
                    mainRow({}, world);
                }
            }
        }

        for (const auto& funcs: threadedSystems) {
            if (funcs.first == nullptr || funcs.first(world)) {
                if (!isUseMultithreading) {
                    for (auto& func: funcs.second) {
                        func({}, world);
                    }
                } else {
                    threadpool.addTasks(funcs.second);
                }
            }
        }

        threadpool.run();

        threadpool.wait();
    }

    void runLate(World& world) noexcept {
        for (const auto& lateFunc: lateSystems) {
            if (lateFunc.first == nullptr || lateFunc.first(world)) {
                for (const auto& lateRow: lateFunc.second) {
                    lateRow({}, world);
                }
            }
        }
    }

    void runFixed(World& world) noexcept {
        for (const auto& mainFunc: mainFixedSystems) {
            if (mainFunc.first == nullptr || mainFunc.first(world)) {
                for (const auto& mainRow: mainFunc.second) {
                    mainRow({}, world);
                }
            }
        }

        for (const auto& funcs: threadedFixedSystems) {
            if (funcs.first == nullptr || funcs.first(world)) {
                if (!isUseMultithreading) {
                    for (auto& func: funcs.second) {
                        func({}, world);
                    }
                } else {
                    threadpool.addFixedTasks(funcs.second);
                }
            }
        }

        threadpool.fixedRun();

        threadpool.fixedWait();

        for (const auto& lateFunc: lateFixedSystems) {
            if (lateFunc.first == nullptr || lateFunc.first(world)) {
                for (const auto& lateRow: lateFunc.second) {
                    lateRow({}, world);
                }
            }
        }
    }

private:
    std::vector<void(*)(StartSystem, World&)> startSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(MainSystem, World&)>>> mainSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(MainFixedSystem, World&)>>> mainFixedSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(ThreadedSystem, World&)>>> threadedSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(ThreadedFixedSystem, World&)>>> threadedFixedSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(LateSystem, World&)>>> lateSystems;
    std::vector<std::pair<bool(*)(World&), std::vector<void(*)(LateFixedSystem, World&)>>> lateFixedSystems;
    ThreadPool threadpool;
    bool isUseMultithreading;
};

///////////////////////////////////////////////////////////////////////////////////

class Time final {
friend class ZerEngine;
public:
    Time(float newFixedTimeStep = 0.02f) noexcept:
        t2(std::chrono::high_resolution_clock::now()),
        fixedTimeStep(newFixedTimeStep) {
    }

private:    
    constexpr void setFixedTimeStep(float newFixedTimeStep) noexcept {
        fixedTimeStep = newFixedTimeStep;
    }

    void update() noexcept {
        auto t1 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::duration<float>>(t1 - t2).count();
        t2 = t1;
        timeScale = newTimeScale;
        #ifdef DISPLAY_FPS
            frameCounter();
        #endif
        timeStepBuffer += dt;
        isTimeStepFrame = false;
        if (timeStepBuffer >= fixedTimeStep) {
            isTimeStepFrame = true;
            nbFixedSteps = std::floor(timeStepBuffer / fixedTimeStep);
            timeStepBuffer -= fixedTimeStep * nbFixedSteps;
        }
    }

public:
    [[nodiscard]] constexpr float delta() const noexcept {
        return dt * timeScale;
    }

    [[nodiscard]] constexpr float unscaledDelta() const noexcept {
        return dt;
    }

    [[nodiscard]] constexpr float unscaledFixedDelta() const noexcept {
        return fixedTimeStep;
    }

    [[nodiscard]] constexpr float fixedDelta() const noexcept {
        return fixedTimeStep * timeScale;
    }

    [[nodiscard]] constexpr bool isTimeStep() const noexcept {
        return isTimeStepFrame;
    }

    [[nodiscard]] constexpr unsigned int getNbFixedSteps() const noexcept {
        return nbFixedSteps;
    }

    constexpr float getTimeScale() const noexcept {
        return newTimeScale;
    }

    constexpr void setTimeScale(const float newScale) noexcept {
        newTimeScale = newScale;
    }

private:
    #ifdef DISPLAY_FPS
        void frameCounter() noexcept {
            nbFrames++;
            timer += dt;
            if (timer >= FRAME_COOLDOWN) {
                printf("FPS: %zu\n", nbFrames);
                timer -= FRAME_COOLDOWN;
                nbFrames = 0;
            }
        }
    #endif

private:
    float newTimeScale = 1.0;
    float timeScale = 1.0;

private:
    double dt = 0;
    std::chrono::high_resolution_clock::time_point t2;
    bool isTimeStepFrame = false;
    float fixedTimeStep;
    float timeStepBuffer = 0;
    unsigned int nbFixedSteps = 0;

    #ifdef DISPLAY_FPS
        float timer = 0;
        size_t nbFrames = 0;
        constexpr static float FRAME_COOLDOWN = 1.0;
    #endif
};

///////////////////////////////////////////////////////////////////////////////////

class World final {
friend class ZerEngine;
private:
    World() noexcept:
        sys(*this) {
    }

public:
    [[nodiscard("La valeur de retour d'une commande Exist doit toujours etre evalue")]] bool exist(const Ent ent) const noexcept {
        return reg.exist(ent);
    }

    template <typename T, typename... Ts>
    [[nodiscard("La valeur de retour d'une commande Has doit toujours etre evalue")]] bool has(const Ent ent) const noexcept {
        if (!reg.exist(ent)) {
            return false;
        } else if (reg.has(ent, {typeid(T).hash_code()})) {
            if constexpr (sizeof...(Ts) > 0) {
                return has<Ts...>(ent);
            }
            return true;
        }
        return false;
    }

public:
    [[nodiscard("La valeur de retour d'une commande GetTypes doit toujours etre recupere")]] const std::vector<std::string> getTypes(const Ent ent) noexcept {
        auto types = reg.getTypes(ent);
        for (const auto& type: lateUpgrade.getTypes(ent)) {
            types.emplace_back(type);
        }
        return types;
    }

private:
    template <typename T>
    [[nodiscard]] std::optional<std::reference_wrapper<T>> internalGet(const Ent ent) noexcept {
        if (reg.has(ent, {typeid(T).hash_code()})) {
            auto& any = reg.get(ent, typeid(T).hash_code());
            return std::any_cast<T&>(any);
        }
        return std::nullopt;
    }

    template <typename T>
    [[nodiscard]] std::optional<const std::reference_wrapper<T>> internalGet(const Ent ent) const noexcept {
        if (reg.has(ent, {typeid(T).hash_code()})) {
            auto& any = reg.get(ent, typeid(T).hash_code());
            return std::any_cast<const T&>(any);
        }
        return std::nullopt;
    }

    template <typename T>
    [[nodiscard]] std::optional<std::reference_wrapper<T>> internalGetThisFrame(const Ent ent) noexcept {
        if (auto addEntsIt = lateUpgrade.addEnts.find(ent); addEntsIt != lateUpgrade.addEnts.end()) {
            if (auto addEntsTypeIt = addEntsIt->second.find(typeid(T).hash_code()); addEntsTypeIt != addEntsIt->second.end()) {
                return std::any_cast<T&>(addEntsTypeIt->second);
            }
        }
        if (auto addCompsIt = lateUpgrade.addComps.find(ent); addCompsIt != lateUpgrade.addComps.end()) {
            if (auto addCompsTypeIt = addCompsIt->second.find(typeid(T).hash_code()); addCompsTypeIt != addCompsIt->second.end()) {
                return std::any_cast<T&>(addCompsTypeIt->second);
            }
        }
        if (reg.has(ent, {typeid(T).hash_code()})) {
            auto& any = reg.get(ent, typeid(T).hash_code());
            return std::any_cast<T&>(any);
        }
        return std::nullopt;
    }

    template <typename T>
    [[nodiscard]] std::optional<const std::reference_wrapper<T>> internalGetThisFrame(const Ent ent) const noexcept {
        if (auto addEntsIt = lateUpgrade.addEnts.find(ent); addEntsIt != lateUpgrade.addEnts.end()) {
            if (auto addEntsTypeIt = addEntsIt->second.find(typeid(T).hash_code()); addEntsTypeIt != addEntsIt->second.end()) {
                return std::any_cast<const T&>(addEntsTypeIt->second);
            }
        }
        if (auto addCompsIt = lateUpgrade.addComps.find(ent); addCompsIt != lateUpgrade.addComps.end()) {
            if (auto addCompsTypeIt = addCompsIt->second.find(typeid(T).hash_code()); addCompsTypeIt != addCompsIt->second.end()) {
                return std::any_cast<const T&>(addCompsTypeIt->second);
            }
        }
        if (reg.has(ent, {typeid(T).hash_code()})) {
            auto& any = reg.get(ent, typeid(T).hash_code());
            return std::any_cast<const T&>(any);
        }
        return std::nullopt;
    }

public:
    template <typename T, typename... Ts> requires (IsNotEmptyConcept<T>)
    [[nodiscard("La valeur de retour d'une commande Get doit toujours etre recupere")]] std::optional<std::tuple<T&, Ts&...>> getThisFrame(const Ent ent) noexcept {
        if (auto opt = internalGetThisFrame<T>(ent)) {
            if constexpr (sizeof...(Ts) > 0) {
                if (auto othOpt = getThisFrame<Ts...>(ent)) {
                    return std::tuple_cat(std::forward_as_tuple(opt.value()), othOpt.value());
                } else {
                    return std::nullopt;
                }
            } else {
                return std::forward_as_tuple(opt.value());
            }
        }
        return std::nullopt;
    }

    template <typename T, typename... Ts> requires (IsNotEmptyConcept<T>)
    [[nodiscard("La valeur de retour d'une commande Get doit toujours etre recupere")]] std::optional<std::tuple<T&, Ts&...>> get(const Ent ent) noexcept {
        if (auto opt = internalGet<T>(ent)) {
            if constexpr (sizeof...(Ts) > 0) {
                if (auto othOpt = get<Ts...>(ent)) {
                    return std::tuple_cat(std::forward_as_tuple(opt.value()), othOpt.value());
                } else {
                    return std::nullopt;
                }
            } else {
                return std::forward_as_tuple(opt.value());
            }
        }
        return std::nullopt;
    }

    [[nodiscard("La valeur de retour d'une commande HasParent doit toujours etre evaluer")]] bool hasParent(const Ent childEnt) const noexcept {
        return reg.hasParent(childEnt);
    }

    [[nodiscard("La valeur de retour d'une commande GetParent doit toujours etre recupere")]] std::optional<Ent> getParent(const Ent childEnt) const noexcept {
        return reg.getParent(childEnt);
    }

    [[nodiscard("La valeur de retour d'une commande HasChildren doit toujours etre evaluer")]] bool hasChildren(const Ent parentEnt) const noexcept {
        return reg.hasChildren(parentEnt);
    }

    [[nodiscard("La valeur de retour d'une commande GetChildren doit toujours etre recupere")]] std::optional<std::reference_wrapper<const std::unordered_set<Ent>>> getChildren(const Ent parentEnt) const noexcept {
        return reg.getChildren(parentEnt);
    }

    constexpr Ent appendChildren(const Ent parentEnt, const std::vector<Ent>& childrenEnt) noexcept {
        lateUpgrade.appendChildren(parentEnt, childrenEnt);
        return parentEnt;
    }

    template <typename... Ts> requires (sizeof...(Ts) > 0)
    [[nodiscard("La valeur de retour d'une commande Resource doit toujours etre recupere")]] decltype(auto) resource(this auto&& self) noexcept {
        return std::forward_as_tuple(std::any_cast<Ts&>(std::move(self).res.get(typeid(Ts).hash_code()))...);
    }

    [[nodiscard]] const std::unordered_set<Ent>& getDestroyedEnts() const noexcept {
        return lateUpgrade.delEnts;
    }

    [[nodiscard]] const std::unordered_map<Ent, std::unordered_map<Type, std::any>>& getAddedEnts() const noexcept {
        return lateUpgrade.addEnts;
    }

    [[nodiscard]] const std::unordered_map<Ent, std::unordered_map<Type, std::any>>& getAddedComps() const noexcept {
        return lateUpgrade.addComps;
    }

    [[nodiscard]] const std::unordered_map<Ent, std::unordered_set<Type>>& getDestroyedComps() const noexcept {
        return lateUpgrade.delComps;
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const With<Filters...>& = {}, const Without<Excludes...>& = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(IsInactive).hash_code(), typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const Without<Excludes...>&, const With<Filters...>& = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(IsInactive).hash_code(), typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const With<Filters...>&, const Without<Excludes...>&, const WithInactive&) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const Without<Excludes...>&, const With<Filters...>&, const WithInactive&) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const With<Filters...>&, const WithInactive&, const Without<Excludes...>& = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const Without<Excludes...>& excludes, const WithInactive&, const With<Filters...>& filters = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const WithInactive&, const With<Filters...>& = {}, const Without<Excludes...>& = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps, typename... Filters, typename... Excludes> requires (IsNotEmptyConcept<Comps> && ...)
    [[nodiscard]] const View<Comps...> view(const WithInactive&, const Without<Excludes...>&, const With<Filters...>& = {}) noexcept {
        return reg.view<Comps...>({typeid(Comps).hash_code()..., typeid(Filters).hash_code()...}, {typeid(Excludes).hash_code()...});
    }

    template <typename... Comps> requires ((std::copy_constructible<Comps> && ...) && (IsFinalConcept<Comps> && ...))
    Ent newEnt(const Comps&... comps) noexcept {
        return lateUpgrade.newEnt(
            reg.getEntToken(),
            {{typeid(Comps).hash_code(), std::make_any<Comps>(comps)}...}
        );
    }

    template <typename Comp, typename... Comps> requires ((std::copy_constructible<Comp>) && (IsFinalConcept<Comp>))
    std::optional<std::tuple<Comp&, Comps&...>> add(const Ent ent, const Comp& comp, const Comps&... comps) noexcept {
        if (reg.exist(ent)) {
            lateUpgrade.add(
                ent,
                std::initializer_list<std::pair<const Type, std::any>>{
                    {typeid(Comp).hash_code(), std::make_any<Comp>(comp)},
                    {typeid(Comps).hash_code(), std::make_any<Comps>(comps)}...
                }
            );
        } else {
            printf("World::add(): Impossible d'ajouter sur une entitée qui n'existe pas [type: %s]\n", typeid(Comp).name());
            (printf("World::add(): Impossible d'ajouter sur une entitée qui n'existe pas [type: %s]\n", typeid(Comps).name()), ...);
            return std::nullopt;
        }

        return std::forward_as_tuple(internalGetThisFrame<Comp>(ent).value(), internalGetThisFrame<Comps>(ent).value()...);
    }

    template <typename T, typename... Ts>
    void remove(const Ent ent) noexcept {
        if (reg.has(ent, {typeid(T).hash_code()})) {
            lateUpgrade.remove(ent, typeid(T).hash_code());
        } else {
            printf("World::remove(): Impossible de supprimer un composant qui n'existe pas - %s\n", typeid(T).name());
        }

        if constexpr (sizeof...(Ts) > 0) {
            remove<Ts...>(ent);
        }
    }

    void destroy(const Ent ent) noexcept {
        if (reg.exist(ent)) {
            lateUpgrade.destroy(reg, ent);
        } else {
            printf("World::destroy(): Impossible de supprimer une entitée qui n'existe pas\n");
        }
    }

    void setActive(const Ent ent) noexcept {
        lateUpgrade.setActive(ent);
    }

    void setInactive(const Ent ent) noexcept {
        lateUpgrade.setInactive(ent);
    }

    [[nodiscard]] constexpr std::size_t getTotalEntities() const noexcept {
        return reg.entArch.size();
    }

    void addDontDestroyOnLoad(const Ent ent) noexcept {
        lateUpgrade.addDontDestroyOnLoad(ent);
    }

    void loadScene(void(*newScene)(SceneSystem, World&)) noexcept {
        lateUpgrade.loadScene(newScene);
    }

    void stopRun(bool val = true) noexcept {
        isRunning = !val;
    }

    void upgrade() noexcept {
        lateUpgrade.upgrade(*this, reg);
    }

private:
    TypeMap res;
    Registry reg;
    LateUpgrade lateUpgrade;
    Sys sys;
    bool isRunning;
};

///////////////////////////////////////////////////////////////////////////////////

class ZerEngine final {
public:
    ZerEngine() {
        world.res.emplace(typeid(Time).hash_code(), std::make_any<Time>(0.02f));
    }

    [[nodiscard]] constexpr ZerEngine& useMultithreading(bool newVal) noexcept {
        world.sys.useMultithreading(newVal);
        return *this;
    }

    [[nodiscard]] constexpr ZerEngine& setFixedTimeStep(float newFixedTimeStep) noexcept {
        auto [time] = world.resource<Time>();
        time.setFixedTimeStep(newFixedTimeStep);
        return *this;
    }

    template <typename T, typename... Args> requires ((std::copy_constructible<T>) && (IsFinalConcept<T>))
    [[nodiscard]] ZerEngine& addResource(Args&&... args) noexcept {
        world.res.emplace(typeid(T).hash_code(), std::make_any<T>(std::forward<Args>(args)...));
        return *this;
    }

    template <typename T, typename... Args>
    [[nodiscard]] ZerEngine& addPlugin(void(*pluginFunc)(ZerEngine&)) noexcept {
        pluginFunc(*this);
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(StartSystem, void(*const func)(StartSystem, World&)) noexcept {
        world.sys.addStartSys(func);
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(MainSystem, std::initializer_list<void(*)(MainSystem, World&)>&& funcs) noexcept {
        world.sys.addMainCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(MainSystem, bool(*const cond)(World&), std::initializer_list<void(*)(MainSystem, World&)>&& funcs) noexcept {
        world.sys.addMainCondSys(cond, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(MainFixedSystem, std::initializer_list<void(*)(MainFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addMainFixedCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(MainFixedSystem, bool(*const cond)(World&), std::initializer_list<void(*)(MainFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addMainFixedCondSys(cond, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(ThreadedSystem, std::initializer_list<void(*)(ThreadedSystem, World&)>&& funcs) noexcept {
        world.sys.addThreadedCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(ThreadedSystem, bool(*const cond)(World&), std::initializer_list<void(*)(ThreadedSystem, World&)>&& funcs) noexcept {
        world.sys.addThreadedCondSys(cond, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(ThreadedFixedSystem, std::initializer_list<void(*)(ThreadedFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addThreadedFixedCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(ThreadedFixedSystem, bool(*const cond)(World&), std::initializer_list<void(*)(ThreadedFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addThreadedFixedCondSys(cond, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(LateSystem, std::initializer_list<void(*)(LateSystem, World&)>&& funcs) noexcept {
        world.sys.addLateCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(LateSystem, bool(*const cond)(World&), std::initializer_list<void(*)(LateSystem, World&)>&& funcs) noexcept {
        world.sys.addLateCondSys(cond, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(LateFixedSystem, std::initializer_list<void(*)(LateFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addLateFixedCondSys(nullptr, std::move(funcs));
        return *this;
    }

    [[nodiscard]] ZerEngine& addSystems(LateFixedSystem, bool(*const cond)(World&), std::initializer_list<void(*)(LateFixedSystem, World&)>&& funcs) noexcept {
        world.sys.addLateFixedCondSys(cond, std::move(funcs));
        return *this;
    }

    void run() noexcept {
        world.isRunning = true;
        world.sys.start(world);
        while (world.isRunning) {
            world.upgrade();

            auto [time] = world.resource<Time>();
            time.update();

            world.sys.run(world);

            if (time.isTimeStep()) {
                for (unsigned int i = 0; i < time.getNbFixedSteps(); i++) {
                    world.upgrade();
                    world.sys.runFixed(world);
                }
            }

            world.sys.runLate(world);
        }
        world.upgrade();
    }

private:
    World world;
};

///////////////////////////////////////////////////////////////////////////////////
