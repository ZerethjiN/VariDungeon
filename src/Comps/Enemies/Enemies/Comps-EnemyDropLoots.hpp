#pragma once

#include <Zerengine.hpp>

class EnemyDropLoots final: public IComponent {
public:
    EnemyDropLoots(const std::initializer_list<size_t>& newLoots, float newTotalDuration, std::size_t newNbDropPerSubDrop):
        loots(newLoots),
        subDropDuration(newTotalDuration / std::ceilf(static_cast<float>(newLoots.size()) / static_cast<float>(newNbDropPerSubDrop))),
        curSubDropDuration(0),
        nbDropPerSubDrop(newNbDropPerSubDrop),
        curNbDropPerSubDrop(0) {
    }

    EnemyDropLoots(const std::vector<size_t>& newLoots, float newTotalDuration, std::size_t newNbDropPerSubDrop):
        loots(newLoots),
        subDropDuration(newTotalDuration / std::ceilf(static_cast<float>(newLoots.size()) / static_cast<float>(newNbDropPerSubDrop))),
        curSubDropDuration(0),
        nbDropPerSubDrop(newNbDropPerSubDrop),
        curNbDropPerSubDrop(0) {
    }

    bool canSubDrop(float delta) {
        curSubDropDuration += delta;
        if (curSubDropDuration >= subDropDuration) {
            curSubDropDuration -= subDropDuration;
            return true;
        }
        return false;
    }

    bool IsEverythingDrop() const {
        return curNbDropPerSubDrop >= loots.size();
    }

    std::size_t getNextMaxRange() {
        std::size_t max = getCurNbDropPerSubDrop() + getNbDropPerSubDrop();
        if (max > loots.size()) {
            return loots.size();
        }
        return max;
    }

    void nextSubLoot() {
        curNbDropPerSubDrop += nbDropPerSubDrop;
    }

    std::size_t getNbDropPerSubDrop() const {
        return nbDropPerSubDrop;
    }

    std::size_t getCurNbDropPerSubDrop() const {
        return curNbDropPerSubDrop;
    }

    size_t operator[](size_t index) const {
        return loots[index];
    }

private:
    const std::vector<size_t> loots;
    
    const float subDropDuration;
    float curSubDropDuration;
    const std::size_t nbDropPerSubDrop;
    std::size_t curNbDropPerSubDrop;
};