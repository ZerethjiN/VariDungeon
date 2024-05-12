#pragma once

#include <Zerengine.hpp>

enum LootType: size_t {
    LOOT_TYPE_XP
};

class EnemyDropLoots {
public:
    EnemyDropLoots(const std::initializer_list<size_t>& newLoots, float newTotalDuration, int newNbDropPerSubDrop):
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

    int getNextMaxRange() {
        int max = getCurNbDropPerSubDrop() + getNbDropPerSubDrop();
        if (max > loots.size()) {
            return loots.size();
        }
        return max;
    }

    void nextSubLoot() {
        curNbDropPerSubDrop += nbDropPerSubDrop;
    }

    int getNbDropPerSubDrop() const {
        return nbDropPerSubDrop;
    }

    int getCurNbDropPerSubDrop() const {
        return curNbDropPerSubDrop;
    }

    size_t operator[](size_t index) const {
        return loots[index];
    }

private:
    const std::vector<size_t> loots;
    
    const float subDropDuration;
    float curSubDropDuration;
    const int nbDropPerSubDrop;
    int curNbDropPerSubDrop;
};