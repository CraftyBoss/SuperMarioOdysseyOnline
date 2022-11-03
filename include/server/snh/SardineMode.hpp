#pragma once

#include "al/camera/CameraTicket.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeConfigMenu.hpp"
#include "server/gamemode/GameModeInfoBase.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/snh/SardineConfigMenu.hpp"
#include "layouts/SardineIcon.h"
#include <math.h>

struct SardineInfo : GameModeInfoBase {
    SardineInfo() { mMode = GameMode::SARDINE; }
    bool mIsIt = false;
    bool mIsUseGravity = false;
    bool mIsUseGravityCam = false;

    bool mIsTether = false;
    bool mIsTetherSnap = false;

    GameTime mHidingTime;
};

class SardineMode : public GameModeBase {
public:
    SardineMode(const char* name);

    void init(GameModeInitInfo const& info) override;

    virtual void begin() override;
    virtual void update() override;
    virtual void end() override;

    bool isPlayerIt() const { return mInfo->mIsIt; };

    void setPlayerTagState(bool state) { mInfo->mIsIt = state; }

    void enableGravityMode() { mInfo->mIsUseGravity = true; }
    void disableGravityMode() { mInfo->mIsUseGravity = false; }
    bool isUseGravity() const { return mInfo->mIsUseGravity; }

    void setCameraTicket(al::CameraTicket* ticket) { mTicket = ticket; }

private:
    GameModeTimer* mModeTimer = nullptr;
    SardineIcon* mModeLayout = nullptr;
    SardineInfo* mInfo = nullptr;
    al::CameraTicket* mTicket = nullptr;

    float pullDistanceMax = 2250.f;
    float pullDistanceMin = 1000.f;
    float pullPowerRate = 75.f;
};