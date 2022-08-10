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

namespace al
{
    class WipeHolder;
    class ScreenCaptureExecutor;
    class BootLayout;
} // namespace al

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
        al::Scene *getCurrentScene(void) const; // {return this->curScene}

        void* qword20;
        void* qword28;
        void* qword30;
        void* qword38;
        void* qword40;
        void* qword48;
        void* qword50;
        void* qword58;
        void* qword60;
        void* qword68;
        void* qword70;
        void* qword78;
        void* qword80;
        void* qword88;
        al::AudioDirector *mAudioDirector; // 0x90
        void *qword98;
        void *qwordA0;
        void *qwordA8;
        al::Scene *curScene; // 0xB0
        GameDataHolderAccessor mGameDataHolder; // 0xB8
        al::GamePadSystem *mGamepadSys; // 0xC0
        HakoniwaStateDemoOpening *mDemoOpening; // 0xC8
        HakoniwaStateDemoEnding *mDemoEnding; // 0xD0
        HakoniwaStateDemoWorldWarp *mDemoWorldWarp; // 0xD8
        HakoniwaStateSimpleDemo *mSimpleDemo; // 0xE0
        HakoniwaStateBootLoadData *mBootLoadData; // 0xE8
        HakoniwaStateDeleteScene *mDeleteScene; // 0xF0
        al::LayoutKit* mLytKit;                 // 0xF8
        unsigned char padding_168[0x108];
        WorldResourceLoader* mResourceLoader;  // 0x208
};