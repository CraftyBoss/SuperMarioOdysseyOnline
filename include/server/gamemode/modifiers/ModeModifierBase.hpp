#pragma once

#include <cmath>
#include "game/StageScene/StageScene.h"

class GameModeBase;

class ModeModifierBase {
public:
    ModeModifierBase(GameModeBase* mode) : mMode(mode) {}

    bool isActive() const { return mIsEnabled; }

    virtual void init(StageScene *scene) { mScene = scene; }

    virtual void enable() { mIsEnabled = true; }
    virtual void disable()  { mIsEnabled = false; }
    virtual void update() {}

protected:
    GameModeBase* mMode = nullptr;
    StageScene *mScene = nullptr;
    bool mIsEnabled = false;
};