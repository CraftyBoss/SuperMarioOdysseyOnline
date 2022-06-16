#pragma once

#include "game/Layouts/CoinCounter.h"
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/layout/SimpleLayoutAppearWaitEnd.h"
#include "al/nerve/NerveStateBase.h"
#include "game/Layouts/MapMini.h"

namespace al {
    class SubCameraRenderer;
    class PlayerHolder;
}

class StageSceneLayout : public al::NerveStateBase {
    public:

        StageSceneLayout(char const *, al::LayoutInitInfo const&, al::PlayerHolder const*, al::SubCameraRenderer const*);
        
        void control(void);
        void updatePlayGuideMenuText(void);
        void setDirtyFlagForPlayGuideMenu(void);
        void tryAppearCoinCollectCounter(void);
        void endWithoutCoin(bool);
        void end(void);
        void appearCoinCounterForDemo(void);
        void endShineChipCompleteAnim(void);
        void killShineCount(void);
        void appearShineCountWait(void);
        void endCloset(void);
        void missEnd(void);
        void appearPlayGuideCamera(void);

        void updateCounterParts(void);
        void updateLifeCounter(void);
        void updateKidsModeLayout(void);

        void start(void);
        void startActionAll(char const*);
        void startOnlyCoin(bool);
        void tryStartLifeDemo(void);
        void startCoinCountAnim(int);
        void startCoinCollectCountAnim(int);
        void startShineChipCompleteAnim(void);
        void tryStartDemoGetLifeMaxUpItem(bool);
        void startCloset(void);
        void startShineCountAnim(bool);

        void exeAppear(void);
        void exeWait(void);
        void exeEnd(void);
        void exeEndWithoutCoin(void);
        void exeCoinCountAnim(void);
        void exeShineChipComplete(void);
        void exeShineCountAppear(void);

        bool isEnd(void) const;
        bool isWait(void) const;
        bool isActive(void) const;
        bool isEndLifeDemo(void) const;
        bool isEndCoinCountAnim(void) const;
        bool isEndShineChipCompleteAnim(void) const;
        bool isEndDemoGetLifeMaxUpItem(void) const;
        bool isEndShineCountAnim(void) const;
        bool isActionEndAll(void) const;

        CoinCounter *mCoinCountLyt; // 0x18
        struct CounterLifeCtrl * mHealthLyt; // 0x20
        struct ShineCounter * mShineCountLyt; // 0x28
        CoinCounter * mCoinCollectLyt; // 0x30
        struct ShineChipLayoutParts * mShineChipPartsLyt; // 0x38
        struct PlayGuideCamera * mPlayGuideCamLyt; // 0x40
        struct PlayGuideBgm * mPlayGuideBgmLyt; // 0x48
        MapMini * mMapMiniLyt; // 0x50
        al::PlayerHolder *mPlayerHolder; // 0x58
        void * unkPtr; // 0x60
        al::SimpleLayoutAppearWaitEnd * mPlayGuideMenuLyt; // 0x68
        void * voidPtr; // 0x70
        al::LayoutActor * mKidsModeLyt; // 0x78
};

static_assert(sizeof(StageSceneLayout) == 0x80, "StageSceneLayout size");