#pragma once

#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <container/seadSafeArray.h>
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeInfoBase.hpp"

class GameModeManager {
    SEAD_SINGLETON_DISPOSER(GameModeManager)
    GameModeManager();
    ~GameModeManager();

public:
    void setMode(GameMode mode);
    void initScene(const GameModeInitInfo& info);
    void begin();
    void end();
    void update();

    GameMode getGameMode() const { return mCurMode; }
    template<class T> T* getMode() const { return static_cast<T*>(mCurModeBase); }
    template<class T> T* getInfo() const { return static_cast<T*>(mModeInfo); }
    void setInfo(GameModeInfoBase* info) {
        mModeInfo = info;
    }

    template<class T>
    T* createModeInfo();

    sead::Heap* getHeap() { return mHeap; }
    void toggleActive();
    void setActive(bool active) { mActive = active; }
    void setPaused(bool paused);
    bool isMode(GameMode mode) const { return mCurMode == mode; }
    bool isActive() const { return mActive; }
    bool isModeAndActive(GameMode mode) const { return isMode(mode) && isActive(); }
    bool isPaused() const { return mPaused; }
private:
    sead::Heap* mHeap = nullptr;

    bool mActive = false;
    bool mPaused = false;
    bool mWasSceneTrans = false;
    bool mWasSetMode = false;
    GameMode mCurMode = GameMode::NONE;
    GameModeBase* mCurModeBase = nullptr;
    GameModeInfoBase *mModeInfo = nullptr;
    GameModeInitInfo *mLastInitInfo = nullptr;
};

template<class T>
T* GameModeManager::createModeInfo() {
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    T* info = new T();
    mModeInfo = info;
    return info;
}