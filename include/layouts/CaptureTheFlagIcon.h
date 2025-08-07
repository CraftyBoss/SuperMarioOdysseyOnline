#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

struct CaptureTheFlagInfo;

class CaptureTheFlagIcon : public al::LayoutActor {
public:
    CaptureTheFlagIcon(const char* name, const al::LayoutInitInfo& initInfo);
    
    void appear() override;
    bool tryEnd();
    bool tryStart();
    
    void showTeamRed();
    void showTeamBlue();
    void showSpectator();
    void updateScore(u8 redScore, u8 blueScore);
    void showFlagCarrier(bool hasFlag, u8 flagTeam);
    
    void exeAppear();
    void exeWait();
    void exeEnd();
    
private:
    CaptureTheFlagInfo* mInfo = nullptr;
};

namespace {
    NERVE_HEADER(CaptureTheFlagIcon, Appear)
    NERVE_HEADER(CaptureTheFlagIcon, Wait)
    NERVE_HEADER(CaptureTheFlagIcon, End)
}