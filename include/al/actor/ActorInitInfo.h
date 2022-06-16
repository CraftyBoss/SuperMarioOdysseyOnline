#pragma once

#include "al/actor/Placement.h"
#include "al/actor/ActorSceneInfo.h"
#include "al/LiveActor/LiveActorGroup.h"
#include "al/execute/ExecuteDirector.h"
#include "al/audio/AudioDirector.h"
#include "al/effect/EffectSystemInfo.h"
#include "al/gamepad/util.h"
#include "al/rumble/PadRumbleDirector.h"
#include "al/scene/SceneObjHolder.h"
#include "game/GameData/GameDataHolderBase.h"

namespace al
{

    class ModelDrawBufferCounter;
    class ActorResourceHolder;
    class HitSensorDirector;
    class ScreenPointDirector;
    class StageSwitchDirector;
    class ViewIdHolder;
    class ActorFactory;
    class ClippingDirector;
    class DemoDirector;
    class GravityHolder;
    class ItemDirectorBase;
    class NatureDirector;
    class SceneMsgCtrl;
    class SceneStopCtrl;
    class ScreenCoverCtrl;
    class ShadowDirector;
    class ModelGroup;
    class GraphicsSystemInfo;
    class PlayerHolder;
    
    class ActorInitInfo
    {
    public:
        ActorInitInfo();
        void initViewIdSelf(al::PlacementInfo const*,al::ActorInitInfo const&);
        void initNew(al::PlacementInfo const* placementInfo, al::LayoutInitInfo const* lytInfo,
                     al::LiveActorGroup* actorGroup, al::ActorFactory const* factory,
                     al::ActorResourceHolder* resourceHolder, al::AreaObjDirector* areaDir,
                     al::AudioDirector* audioDir, al::CameraDirector* camDir,
                     al::ClippingDirector* clippingDir, al::CollisionDirector* collDir,
                     al::DemoDirector* demoDir, al::EffectSystemInfo* effectSys,
                     al::ExecuteDirector* executeDir, al::GameDataHolderBase* dataHolder,
                     al::GravityHolder* gravityHolder, al::HitSensorDirector* hitSensorDir,
                     al::ItemDirectorBase* itemDir, al::NatureDirector* natureDir,
                     al::GamePadSystem const* gamepad, al::PadRumbleDirector* padRumbleDir,
                     al::PlayerHolder* playerHolder, al::SceneObjHolder* sceneObjHolder,
                     al::SceneMsgCtrl* sceneMsgCtrl, al::SceneStopCtrl* sceneStopCtrl,
                     al::ScreenCoverCtrl* screenCoverCtrl, al::ScreenPointDirector* screenPointDir,
                     al::ShadowDirector* shadowDir, al::StageSwitchDirector* stageSwitchDir,
                     al::ModelGroup* modelGroup, al::GraphicsSystemInfo* gfxSysInfo,
                     al::ModelDrawBufferCounter* mdlDrawBuffCtr,
                     al::LiveActorGroup *otherActorGroup);
        LiveActorGroup *mLiveActorGroup; // 0x0
        const al::PlacementInfo& mPlacementInfo;  // 0x8
        LayoutInitInfo *mLayoutInitInfo;        // 0x10
        ActorSceneInfo mActorSceneInfo;    // 0x18-0xB0
        LiveActorGroup *mLiveActorGroup2; // 0xB8
        ActorFactory *mActorFactory; // 0xC0
        ActorResourceHolder *mResourceHolder; // 0xC8
        AudioDirector *mAudioDirector; // 0xD0
        EffectSystemInfo *mEffectSysInfo; // 0xD8
        ExecuteDirector *mExecuteDirector; // 0xE0
        HitSensorDirector *mHitSensorDirector; // 0xE8
        ScreenPointDirector *mScreenPointDirector; // 0xF0
        StageSwitchDirector *mStageSwitchDirector; // 0xF8
        ViewIdHolder *mViewIdHolder; // 0x100
    };
};

// size not entirely known, guessing based off of ActorInitInfo::initNew
static_assert(sizeof(al::ActorInitInfo) == 0x108);