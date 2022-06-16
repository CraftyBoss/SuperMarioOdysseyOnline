#pragma once

#include "al/camera/CameraDirector.h"
#include "al/message/IUseMessageSystem.h"
#include "al/rumble/PadRumbleDirector.h"
#include "al/scene/SceneObjHolder.h"
#include "game/System/GameSystemInfo.h"

namespace al {
class LayoutSceneInfo {
    public:
        void* gap;
        al::CameraDirector *mCameraDirector;
        al::PadRumbleDirector *mPadRumbleDirector;
        al::SceneObjHolder *mSceneObjHolder;
        al::MessageSystem* mMessageSystem;
        al::GamePadSystem *mGamepadSystem;
    };
}
