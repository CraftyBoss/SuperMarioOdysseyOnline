#pragma once

#include "al/scene/SceneObjHolder.h"

namespace rs {
    bool isTriggerUiAnyABXY(al::IUseSceneObjHolder const*);
    bool isTriggerUiCancel(al::IUseSceneObjHolder const*);
    bool isTriggerUiDecide(class GameDataHolder const*);
    bool isTriggerUiDecide(al::IUseSceneObjHolder const*);
    bool isTriggerUiDown(al::IUseSceneObjHolder const*);
    bool isTriggerUiL(al::IUseSceneObjHolder const*);
    bool isTriggerUiLeft(al::IUseSceneObjHolder const*);
    bool isTriggerUiPause(al::IUseSceneObjHolder const*);
    bool isTriggerUiR(al::IUseSceneObjHolder const*);
    bool isTriggerUiRacePause(al::IUseSceneObjHolder const*);
    bool isTriggerUiRight(al::IUseSceneObjHolder const*);
    bool isTriggerUiSelect(al::IUseSceneObjHolder const*);
    bool isTriggerUiUp(al::IUseSceneObjHolder const*);
    bool isTriggerUiX(al::IUseSceneObjHolder const*);
    bool isTriggerUiY(al::IUseSceneObjHolder const*);
    bool isTriggerUiZL(al::IUseSceneObjHolder const*);
    bool isTriggerUiZR(al::IUseSceneObjHolder const*);
}