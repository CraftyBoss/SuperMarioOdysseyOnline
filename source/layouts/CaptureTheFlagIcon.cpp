#include "layouts/CaptureTheFlagIcon.h"
#include <cstdio>
#include "server/ctf/CaptureTheFlagMode.hpp"
#include "server/Client.hpp"
#include "al/util.hpp"
#include "logger.hpp"

CaptureTheFlagIcon::CaptureTheFlagIcon(const char* name, const al::LayoutInitInfo& initInfo) 
    : al::LayoutActor(name) {
    
    al::initLayoutActor(this, initInfo, "CaptureTheFlagIcon", 0);
    
    
    
    initNerve(&nrvCaptureTheFlagIconEnd, 0);
    
    al::hidePane(this, "TeamRed");
    al::hidePane(this, "TeamBlue");
    al::hidePane(this, "FlagIndicator");
    
    kill();
}

void CaptureTheFlagIcon::appear() {
    al::startAction(this, "Appear", 0);
    al::setNerve(this, &nrvCaptureTheFlagIconAppear);
    al::LayoutActor::appear();
}

bool CaptureTheFlagIcon::tryEnd() {
    if (!al::isNerve(this, &nrvCaptureTheFlagIconEnd)) {
        al::setNerve(this, &nrvCaptureTheFlagIconEnd);
        return true;
    }
    return false;
}

bool CaptureTheFlagIcon::tryStart() {
    if (!al::isNerve(this, &nrvCaptureTheFlagIconWait) && 
        !al::isNerve(this, &nrvCaptureTheFlagIconAppear)) {
        appear();
        return true;
    }
    return false;
}

void CaptureTheFlagIcon::showTeamRed() {
    al::showPane(this, "TeamRed");
    al::hidePane(this, "TeamBlue");
    al::setPaneStringFormat(this, "TxtTeam", "RED TEAM");
}

void CaptureTheFlagIcon::showTeamBlue() {
    al::hidePane(this, "TeamRed");
    al::showPane(this, "TeamBlue");
    al::setPaneStringFormat(this, "TxtTeam", "BLUE TEAM");
}

void CaptureTheFlagIcon::showSpectator() {
    al::hidePane(this, "TeamRed");
    al::hidePane(this, "TeamBlue");
    al::setPaneStringFormat(this, "TxtTeam", "SPECTATOR");
}

void CaptureTheFlagIcon::updateScore(u8 redScore, u8 blueScore) {
    al::setPaneStringFormat(this, "TxtRedScore", "%d", redScore);
    al::setPaneStringFormat(this, "TxtBlueScore", "%d", blueScore);
}

void CaptureTheFlagIcon::showFlagCarrier(bool hasFlag, u8 flagTeam) {
    if (hasFlag) {
        al::showPane(this, "FlagIndicator");
        if (flagTeam == CTFTeam::RED_TEAM) {
            al::setPaneStringFormat(this, "TxtFlagStatus", "Carrying RED Flag");
        } else {
            al::setPaneStringFormat(this, "TxtFlagStatus", "Carrying BLUE Flag");
        }
    } else {
        al::hidePane(this, "FlagIndicator");
    }
}

void CaptureTheFlagIcon::exeAppear() {
    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvCaptureTheFlagIconWait);
    }
}

void CaptureTheFlagIcon::exeWait() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }
    
    if (mInfo) {
        updateScore(mInfo->mRedScore, mInfo->mBlueScore);
        showFlagCarrier(mInfo->mHasFlag, mInfo->mFlagTeam);
        
        // Update timer display
        GameTime& curTime = mInfo->mRoundTime;
        if (curTime.mHours > 0) {
            al::setPaneStringFormat(this, "TxtTimer", "%01d:%02d:%02d", 
                                   curTime.mHours, curTime.mMinutes, curTime.mSeconds);
        } else {
            al::setPaneStringFormat(this, "TxtTimer", "%02d:%02d", 
                                   curTime.mMinutes, curTime.mSeconds);
        }
    }
}

void CaptureTheFlagIcon::exeEnd() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }
    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

namespace {
    NERVE_IMPL(CaptureTheFlagIcon, Appear)
    NERVE_IMPL(CaptureTheFlagIcon, Wait)
    NERVE_IMPL(CaptureTheFlagIcon, End)
}