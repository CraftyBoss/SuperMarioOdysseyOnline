#include "server/sardines/SardineIcon.h"

#include "al/util.hpp"
#include "server/gamemode/GameModeManager.hpp"

SardineIcon::SardineIcon(const char* name, const al::LayoutInitInfo& initInfo) : al::LayoutActor(name) {
    al::initLayoutActor(this, initInfo, "SardineIcon", 0);

    mInfo = GameModeManager::instance()->getInfo<SardineInfo>();

    initNerve(&nrvSardineIconEnd, 0);

    al::hidePane(this, "SoloIcon");
    al::hidePane(this, "PackIcon");

    kill();
}

void SardineIcon::appear() {
    al::startAction(this, "Appear", 0);

    al::setNerve(this, &nrvSardineIconAppear);

    al::LayoutActor::appear();
}

bool SardineIcon::tryEnd() {
    if (!al::isNerve(this, &nrvSardineIconEnd)) {
        al::setNerve(this, &nrvSardineIconEnd);
        return true;
    }
    return false;
}

bool SardineIcon::tryStart() {
    if (!al::isNerve(this, &nrvSardineIconWait) && !al::isNerve(this, &nrvSardineIconAppear)) {
        appear();
        return true;
    }
    return false;
}

void SardineIcon::exeAppear() {
    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvSardineIconWait);
    }
}

const char* SardineIcon::getRoleIcon(bool isIt) {
    return isIt ? "\uE004" : "\uE003";
}

GameMode SardineIcon::getGameMode() {
    return GameMode::SARDINE;
}

bool SardineIcon::isMeIt() {
    return mInfo->mIsIt;
}

void SardineIcon::exeWait() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }

    al::setPaneStringFormat(this, "TxtCounter", mInfo->mHidingTime.to_string().cstr());

    auto playerList = getPlayerList();
    if (!playerList.isEmpty()) {
        al::setPaneStringFormat(this, "TxtPlayerList", playerList.cstr());
    }
}

void SardineIcon::exeEnd() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

void SardineIcon::showSolo() {
    al::hidePane(this, "PackIcon");
    al::showPane(this, "SoloIcon");
}

void SardineIcon::showPack() {
    al::hidePane(this, "SoloIcon");
    al::showPane(this, "PackIcon");
}

namespace {
    NERVE_IMPL(SardineIcon, Appear)
    NERVE_IMPL(SardineIcon, Wait)
    NERVE_IMPL(SardineIcon, End)
}
