#pragma once

#include "al/area/AreaObjDirector.h"
#include "al/camera/CameraDirector.h"
#include "al/collision/CollisionDirector.h"
#include "al/scene/SceneObjHolder.h"
#include "al/layout/LayoutInitInfo.h"
#include "game/GameData/GameDataHolderBase.h"

namespace al {

    struct ClippingDirector;
    struct DemoDirector;
    struct GravityHolder;
    struct ItemDirectorBase;
    struct NatureDirector;
    struct SceneMsgCtrl;
    struct SceneStopCtrl;
    struct ScreenCoverCtrl;
    struct ShadowDirector;
    struct ModelGroup;
    struct GraphicsSystemInfo;
    struct PlayerHolder;
    struct ModelDrawBufferCounter;

    class ActorSceneInfo
    {
    public:
        ActorSceneInfo() = default;
        AreaObjDirector *mAreaObjDirector;      // 0x0
        CameraDirector *mCameraDirector;        // 0x8
        ClippingDirector *mClippingDirector;    // 0x10
        CollisionDirector *mCollisionDirector;  // 0x18
        DemoDirector *mDemoDirector;            // 0x20
        GameDataHolderBase *mGameDataHolder;    // 0x28
        GravityHolder *mGravityHolder;          // 0x30
        ItemDirectorBase *mItemDirector;        // 0x38
        NatureDirector *mNatureDirector;        // 0x40
        GamePadSystem *mGamePadSys;             // 0x48
        PadRumbleDirector *mPadRumbleDirector;  // 0x50
        PlayerHolder *mPlayerHolder;            // 0x58
        SceneObjHolder *mSceneObjHolder;        // 0x60
        SceneStopCtrl *mSceneStopCtrl;          // 0x68
        SceneMsgCtrl *mSceneMsgCtrl;            // 0x70
        ScreenCoverCtrl *mScreenCoverCtrl;      // 0x78
        ShadowDirector *mShadowDirector;        // 0x80
        ModelGroup *mModelGroup;                // 0x88
        GraphicsSystemInfo *mGfxSysInfo;        // 0x90
        ModelDrawBufferCounter *mDrawBuffCount; // 0x98
    };
} // namespace al

static_assert(sizeof(al::ActorSceneInfo) == 0xA0, "Actor Scene Info Size");