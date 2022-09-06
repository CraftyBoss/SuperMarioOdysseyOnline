#pragma once

#include "types.h"

#include "al/scene/Scene.h"
#include "al/audio/AudioDirector.h"
#include "al/layout/LayoutKit.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/sequence/Sequence.h"
#include "al/sequence/SequenceInitInfo.h"
#include "al/gamepad/util.h"

#include "game/StageScene/StageScene.h"
#include "game/WorldList/WorldResourceLoader.h"
#include "game/GameData/GameDataHolderAccessor.h"

#include "HakoniwaStateDeleteScene.h"
#include "HakoniwaStateDemoOpening.h"
#include "HakoniwaStateDemoEnding.h"
#include "HakoniwaStateDemoWorldWarp.h"
#include "HakoniwaStateSimpleDemo.h"
#include "HakoniwaStateBootLoadData.h"

namespace al {
    class WipeHolder;
    class ScreenCaptureExecutor;
    class SeadAudioPlayer;
    class AudioBusSendFader;
    class SimpleAudioUser;
}  // namespace al
    
class BootLayout;
class TimeBalloonSequenceInfo;
class CollectBgmPlayer;
class LoadLayoutCtrl;

class HakoniwaSequence : public al::Sequence {
    public:

        HakoniwaSequence(const char *);
        bool isDisposable(void);
        void updatePadSystem(void);
        void destroySceneHeap(bool);
        void init(al::SequenceInitInfo const &);
        void initSystem(void);
        void update(void);
        bool isEnableSave(void);
        void drawMain(void);
        al::Scene* getCurrentScene(void) const;  // {return this->curScene}

        void exeBootLoadData();
        void exeDemoOpening();
        void exeLoadWorldResource();
        void exeLoadWorldResourceWithBoot();
        void exeLoadStage();
        void exePlayStage();
        void exeDemoWorldWarp();
        void exeDemoEnding();
        void exeDestroy();
        void exeMiss();
        void exeMissCoinSub();
        void exeMissEnd();
        void exeDemoLava();
        void exeFadeToNewGame();

        al::Scene *curScene;                        // 0xB0
        GameDataHolderAccessor mGameDataHolder;     // 0xB8
        al::GamePadSystem *mGamepadSys;             // 0xC0
        HakoniwaStateDemoOpening *mDemoOpening;     // 0xC8
        HakoniwaStateDemoEnding *mDemoEnding;       // 0xD0
        HakoniwaStateDemoWorldWarp *mDemoWorldWarp; // 0xD8
        HakoniwaStateSimpleDemo *mSimpleDemo;       // 0xE0
        HakoniwaStateBootLoadData *mBootLoadData;   // 0xE8
        HakoniwaStateDeleteScene *mDeleteScene;     // 0xF0
        al::LayoutKit* mLytKit;                     // 0xF8
        bool mYBalls;                                   
        sead::FixedSafeString<0x80> stageName;  
        int scenarioNum;    
        al::ScreenCaptureExecutor* mScreenCapExecutor;
        al::WipeHolder* mWipeHolder;
        bool mMissEnd;
        al::SimpleLayoutAppearWaitEnd* mCounterMiss;
        int mCurCoins;
        int mFinalCoins;
        BootLayout* mBootLayout;
        al::EffectSystem* mEffectSystem;
        al::AsyncFunctorThread* mInitThread;
        bool mInitialized;
        al::SeadAudioPlayer* mSeAudioPlayer;
        al::SeadAudioPlayer* mBgmAudioPlayer;
        al::AudioBusSendFader* mBusSendFader;
        WorldResourceLoader* mResourceLoader;
        sead::Heap* mPlayerResHeap;
        sead::FixedSafeString<0x80> mCapName;
        sead::FixedSafeString<0x80> mCostumeName;
        al::SimpleAudioUser* mPlayerAudioUser;
        bool mHackEnd;
        TimeBalloonSequenceInfo* mBalloonSeqInfo;
        CollectBgmPlayer* mCollectBgmPlayer;
        sead::FixedSafeString<0x80> mLanguage;
        int mFileId;
        LoadLayoutCtrl* mLoadLayoutCtrl;
        bool mKidsMode;
};