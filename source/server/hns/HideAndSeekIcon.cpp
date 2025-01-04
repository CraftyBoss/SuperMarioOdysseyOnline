#include "server/hns/HideAndSeekIcon.h"

#include "server/gamemode/GameModeManager.hpp"
#include "al/util.hpp"

HideAndSeekIcon::HideAndSeekIcon(const char* name, const al::LayoutInitInfo& initInfo) : al::LayoutActor(name) {
    al::initLayoutActor(this, initInfo, "HideAndSeekIcon", 0);

    mInfo = GameModeManager::instance()->getInfo<HideAndSeekInfo>();

    initNerve(&nrvHideAndSeekIconEnd, 0);

    al::hidePane(this, "SeekingIcon");
    al::hidePane(this, "HidingIcon");

    kill();
}

void HideAndSeekIcon::appear() {
    al::startAction(this, "Appear", 0);

    al::setNerve(this, &nrvHideAndSeekIconAppear);

    al::LayoutActor::appear();
}

bool HideAndSeekIcon::tryEnd() {
    if (!al::isNerve(this, &nrvHideAndSeekIconEnd)) {
        al::setNerve(this, &nrvHideAndSeekIconEnd);
        return true;
    }
    return false;
}

bool HideAndSeekIcon::tryStart() {
    if (!al::isNerve(this, &nrvHideAndSeekIconWait) && !al::isNerve(this, &nrvHideAndSeekIconAppear)) {
        appear();
        return true;
    }
    return false;
}

void HideAndSeekIcon::exeAppear() {
    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvHideAndSeekIconWait);
    }
}

const char* HideAndSeekIcon::getRoleIcon(bool isIt) {
    return isIt ? "\uE002" : "\uE001";
}

GameMode HideAndSeekIcon::getGameMode() {
    return GameMode::HIDEANDSEEK;
}

bool HideAndSeekIcon::isMeIt() {
    return mInfo->mIsPlayerIt;
}

void HideAndSeekIcon::exeWait() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }

    al::setPaneStringFormat(this, "TxtCounter", mInfo->mHidingTime.to_string().cstr());

    auto playerList = getPlayerList();
    if (!playerList.isEmpty()) {
        al::setPaneStringFormat(this, "TxtPlayerList", playerList.cstr());
    }
}

void HideAndSeekIcon::exeEnd() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

void HideAndSeekIcon::showHiding() {
    al::hidePane(this, "SeekingIcon");
    al::showPane(this, "HidingIcon");
}

void HideAndSeekIcon::showSeeking() {
    al::hidePane(this, "HidingIcon");
    al::showPane(this, "SeekingIcon");
}

namespace {
    NERVE_IMPL(HideAndSeekIcon, Appear)
    NERVE_IMPL(HideAndSeekIcon, Wait)
    NERVE_IMPL(HideAndSeekIcon, End)
}
