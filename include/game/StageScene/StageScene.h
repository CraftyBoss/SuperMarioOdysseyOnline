#pragma once

#include "al/scene/Scene.h"
#include "game/StageScene/StageSceneLayout.h"
#include "game/StageScene/StageSceneStatePauseMenu.h"

#define INHERITSIZE sizeof(al::Scene)

class StageScene : public al::Scene
{
    public:
        bool isPause() const;
        // 0x88 StageResourceKeeper *
        // 0x90 LiveActorKit *
        // 0x98 LayoutKit *
        // 0xA0 SceneObjHolder *
        // 0xA8 SceneStopCtrl *

        unsigned char padding_180[0x180 - INHERITSIZE];
        StageSceneStatePauseMenu *mStatePauseMenu; // 0x180
        unsigned char padding_2D0[0x148];
        GameDataHolderAccessor mHolder; // 0x2D0
        unsigned char padding_2F8[0x20];
        StageSceneLayout *stageSceneLayout; // 0x2F8
};
