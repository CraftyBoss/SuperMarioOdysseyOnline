#pragma once

#include "al/scene/SceneObjHolder.h"

class InputSeparator {
public:
    InputSeparator(al::IUseSceneObjHolder const*,bool isNoSnapshot);
    void checkDominant(bool);
    void reset(void);
    void update(void);
    void updateForSnapShotMode(void);

    bool isHoldUiDown(void);
    bool isHoldUiLeft(void);
    bool isHoldUiRight(void);
    bool isHoldUiUp(void);
    bool isRepeatUiDown(void);
    bool isRepeatUiLeft(void);
    bool isRepeatUiRight(void);
    bool isRepeatUiUp(void);
    bool isTriggerDecrementPostProcessingFilterPreset(void);
    bool isTriggerIncrementPostProcessingFilterPreset(void);
    bool isTriggerSnapShotMode(void);
    bool isTriggerUiDown(void);
    bool isTriggerUiLeft(void);
    bool isTriggerUiRight(void);
    bool isTriggerUiUp(void);

    al::IUseSceneObjHolder* mSceneObjHolder; // 0x0
    bool unkBool; // 0x8
    bool unkBool2;  // 0x9
    int unkInt; // 0xC
    int unkInt2; // 0x10

};

static_assert(sizeof(InputSeparator) == 0x18, "InputSeparator size");