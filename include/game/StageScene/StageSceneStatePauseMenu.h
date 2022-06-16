#pragma once

#include "al/nerve/HostStateBase.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/layout/SimpleLayoutAppearWaitEnd.h"
#include "al/scene/Scene.h"
#include "al/LiveActor/LiveActor.h"
#include "StageSceneLayout.h"
#include "StageSceneStateOption.h"

#include "al/util.hpp"
#include "al/util/NerveUtil.h"

#include "game/UI/MenuSelectParts.h"
#include "logger.hpp"

class FooterParts;
class StageSceneStateStartSeparatePlay;
class StageSceneStateEndSeparatePlay;
class SceneAudioSystemPauseController;

namespace al
{
    class WindowConfirm;
    class KeyRepeatCtrl;
    class WipeSimple;
} // namespace al

class StageSceneStatePauseMenu : public al::HostStateBase<al::Scene> {
    public:
        StageSceneStatePauseMenu(char const*,al::Scene *,al::SimpleLayoutAppearWaitEnd *,GameDataHolder *,al::SceneInitInfo const&,al::ActorInitInfo const&,al::LayoutInitInfo const&,al::WindowConfirm *,StageSceneLayout *,bool,SceneAudioSystemPauseController *);
        ~StageSceneStatePauseMenu();

        void appear(void);
        void kill(void);
        void killPauseMenu(void);
        void killMarioModel(void);
        void isNeedKillHost(void);
        void startNormal(void);
        void startAfterTitle(void);
        void killAllOptionLayout(void);
        void isEndToCancel(void);
        void isEndToHelp(void);
        void isLoadData(void);
        void getSelectedFileId(void);
        void isChangeLanguage(void);
        void getLanguage(void);
        void isNewGame(void);
        void isModeSelectEnd(void);
        void checkNeedKillByHostAndEnd(void);
        void startActionMario(char const*);
        void getMarioActor(void);
        void isDrawLayout(void);
        void isDrawLayoutMain(void);
        void isDrawViewRenderer(void);
        void isDrawChromakey(void);
        void setNormal(void);
        void appearMarioModel(void);
        void updatePlayerPose(void);
        void changeNerveAndReturn(al::Nerve const*);
        void startPauseCamera(void);
        void setAfterTitle(void);

        void exeAppear(void);
        void exeWait(void);
        void exeFadeBeforeHelp(void);
        void exeStartHelp(void);
        void exeWaitDraw(void);
        void exeEnd(void);
        void exeStartSeparatePlay(void);
        void exeEndSeparatePlay(void);
        void exeOption(void);
        void exeSave(void);
        void exeConfirmNewGame(void);
        void exeNotExistEmptyFile(void);

        void exeServerConfig(void);
    
        al::SimpleLayoutAppearWaitEnd *field_0x20; // 0x20
        al::SimpleLayoutAppearWaitEnd *mMenuGuide; // 0x28
        al::SimpleLayoutAppearWaitEnd *mMenuRight; // 0x30
        FooterParts *mFooterParts; // 0x38
        MenuSelectParts *mSelectParts; // 0x40
        al::WipeSimple *mWipeSimple; // 0x48
        void *field_0x50; // 0x50
        int field_0x58;
        int field_0x5c;
        StageSceneStateStartSeparatePlay *mStateStartSeperatePlay;
        StageSceneStateEndSeparatePlay *mStateEndSeperatePlay;
        StageSceneStateOption *mStateOption;
        al::LiveActor *mMarioHigh;
        unsigned char field_0x80[39];
        GameDataHolder *mDataHolder;
        void *field_0xb0;
        al::WindowConfirm *field_0xb8;
        void *field_0xc0;
        al::KeyRepeatCtrl *field_0xc8;
        StageSceneLayout *mStageSceneLyt;
        int field_0xd8;
        int field_0xdc;
        ulong field_0xe0;
        void *field_0xe8;
};

namespace {
    NERVE_HEADER(StageSceneStatePauseMenu, Appear)
    NERVE_HEADER(StageSceneStatePauseMenu, Wait)
    NERVE_HEADER(StageSceneStatePauseMenu, FadeBeforeHelp)
    NERVE_HEADER(StageSceneStatePauseMenu, StartHelp)
    NERVE_HEADER(StageSceneStatePauseMenu, WaitDraw)
    NERVE_HEADER(StageSceneStatePauseMenu, End)
    NERVE_HEADER(StageSceneStatePauseMenu, StartSeparatePlay)
    NERVE_HEADER(StageSceneStatePauseMenu, EndSeparatePlay)
    NERVE_HEADER(StageSceneStatePauseMenu, Option)
    NERVE_HEADER(StageSceneStatePauseMenu, Save)
    NERVE_HEADER(StageSceneStatePauseMenu, ConfirmNewGame)
    NERVE_HEADER(StageSceneStatePauseMenu, NotExistEmptyFile)
    // custom nerves
    NERVE_HEADER(StageSceneStatePauseMenu, ServerConfig)
}

namespace {
    NERVE_IMPL(StageSceneStatePauseMenu, Appear)
    NERVE_IMPL(StageSceneStatePauseMenu, Wait)
    NERVE_IMPL(StageSceneStatePauseMenu, FadeBeforeHelp)
    NERVE_IMPL(StageSceneStatePauseMenu, StartHelp)
    NERVE_IMPL(StageSceneStatePauseMenu, WaitDraw)
    NERVE_IMPL(StageSceneStatePauseMenu, End)
    NERVE_IMPL(StageSceneStatePauseMenu, StartSeparatePlay)
    NERVE_IMPL(StageSceneStatePauseMenu, EndSeparatePlay)
    NERVE_IMPL(StageSceneStatePauseMenu, Option)
    NERVE_IMPL(StageSceneStatePauseMenu, Save)
    NERVE_IMPL(StageSceneStatePauseMenu, ConfirmNewGame)
    NERVE_IMPL(StageSceneStatePauseMenu, NotExistEmptyFile)
    // custom nerves
    NERVE_IMPL(StageSceneStatePauseMenu, ServerConfig)
}

