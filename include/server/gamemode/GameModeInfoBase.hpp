#pragma once

#include "server/gamemode/GameModeBase.hpp"

// base struct containing info about the current gamemode
struct GameModeInfoBase {
    GameMode mMode;
};

template<class T>
T *createModeInfo() {
    // using sequence heap to create mode info should allow for mode info to persist between scenes
    sead::Heap* seqHeap = sead::HeapMgr::instance()->findHeapByName("SequenceHeap", 0);

    if (seqHeap) {
        return new (seqHeap) T();
    } else {
        // if failed to get sequence heap, fall back to current heap (will return null if current heap is also null)
        return new T();
    }
}