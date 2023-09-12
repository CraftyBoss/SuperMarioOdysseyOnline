#pragma once

#include "al/async/AsyncFunctorThread.h"
#include "al/hio/HioNode.h"
#include "game/GameData/GameDataHolder.h"
#include "heap/seadHeap.h"


class WorldResourceLoader : public al::HioNode {
public:
    WorldResourceLoader(GameDataHolder *);
    virtual ~WorldResourceLoader();

    void loadResource(void);
    void cancelLoadWorldResource(void);
    void tryDestroyWorldResource(void);
    bool requestLoadWorldHomeStageResource(int worldIndex, int scenario);
    bool isEndLoadWorldResource(void) const; // { return mResourceLoadThread->isDone(); };
    void requestLoadWorldResourceCommon(int);
    void requestLoadWorldResource(int);
    void createResourcePlayer(void);
    void tryDestroyWorldResourceOnlyCap(void);
    void calcLoadPercent(void);
    void getLoadWorldId(void);
    bool tryLoadResource(char const*,char const*,char const*);
    void loadWorldResource(int,int,bool,char const*);
    void calcWorldResourceHeapSize(void);

    al::AsyncFunctorThread* mResourceLoadThread; // 0x8
    sead::Heap* mWorldResHeap = nullptr;         // 0x10
    sead::Heap* mCapHeap = nullptr;              // 0x18
    sead::Heap* mWaterfallHeap = nullptr;        // 0x20
    int mCurWorld = -1;                          // 0x28 
    int mCurScenario = -1;                       // 0x2C
    bool unkBool = true;                         // 0x30
    bool mIsCancelLoad = true;                   // 0x31
    void *unkPtr4 = nullptr;                     // 0x38
    void* unkPtr5 = nullptr;                     // 0x40
    int unkInt3 = 0;                             // 0x48
    bool unkBool3 = true;                        // 0x4C
    int unkInt4 = 0;                             // 0x50
    int unkInt5 = 1;                             // 0x5C
    GameDataHolder* mDataHolder;                 // 0x58
    bool mIsDoneLoadingArcs = false;             // 0x60
    int mArcCount = 0;                           // 0x64
};

static_assert(sizeof(WorldResourceLoader) == 0x68, "WorldResourceLoader size");