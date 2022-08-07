#include "server/gamemode/GameModeManager.hpp"
#include <cstring>
#include <heap/seadFrameHeap.h>
#include "al/util.hpp"
#include "basis/seadNew.h"
#include "heap/seadHeapMgr.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeFactory.hpp"

SEAD_SINGLETON_DISPOSER_IMPL(GameModeManager)

GameModeManager::GameModeManager() {
    mHeap = sead::FrameHeap::create(0x100000, "GameModeHeap", al::getSequenceHeap(), 8,
                                    sead::Heap::HeapDirection::cHeapDirection_Reverse, false);
    setMode(GameMode::HIDEANDSEEK);
}

void GameModeManager::begin() {
    if (mCurModeBase) {
        sead::ScopedCurrentHeapSetter heapSetter(mHeap);
        mCurModeBase->begin();
    }
}

void GameModeManager::end() {
    if (mCurModeBase) {
        sead::ScopedCurrentHeapSetter heapSetter(mHeap);
        mCurModeBase->end();
    }
}

void GameModeManager::toggleActive() {
    mActive = !mActive;
}

void GameModeManager::setPaused(bool paused) {
    mPaused = paused;
}

void GameModeManager::setMode(GameMode mode) {
    mCurMode = mode;

    mWasSetMode = true; // recreate in initScene
}

void GameModeManager::update() {
    if (!mCurModeBase) return;
    bool inScene = al::getSceneHeap() != nullptr;
    if ((mActive && inScene && !mPaused && !mCurModeBase->isModeActive()) || mWasSceneTrans) begin();
    if ((!mActive || mPaused || !inScene) && mCurModeBase->isModeActive()) end();
    mWasSceneTrans = false;
    if (mCurModeBase && mCurModeBase->isModeActive()) {
        sead::ScopedCurrentHeapSetter heapSetter(mHeap);
        mCurModeBase->update();
    }
}

void GameModeManager::initScene(const GameModeInitInfo& info) {
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    if (mCurModeBase != nullptr) {
        delete mCurModeBase;
    }

    if (mLastInitInfo != nullptr) {
        delete mLastInitInfo;
    }

    if (mCurMode == GameMode::NONE) {
        mCurModeBase = nullptr;
        mModeInfo = nullptr;
        return;
    }

    mLastInitInfo = new GameModeInitInfo(info);

    if (!mCurModeBase && mWasSetMode) {
        GameModeFactory factory("GameModeFactory");
        const char* name = factory.getModeString(mCurMode);
        mCurModeBase = factory.getCreator(name)(name);
        if (mLastInitInfo) {  // check if there's a previously used init info
            mCurModeBase->init(*mLastInitInfo);
        }
        mWasSetMode = false;
    }

    if (mCurModeBase) {
        mCurModeBase->init(*mLastInitInfo);
        if (mCurModeBase->isModeActive())
            mWasSceneTrans = true;
    }
}