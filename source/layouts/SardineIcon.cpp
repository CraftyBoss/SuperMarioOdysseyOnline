#include "layouts/SardineIcon.h"
#include "al/string/StringTmp.h"
#include "al/util.hpp"
#include "logger.hpp"
#include "main.hpp"
#include "prim/seadSafeString.h"
#include "puppets/PuppetInfo.h"
#include "rs/util.hpp"
#include "server/Client.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/snh/SardineMode.hpp"
#include <cstdio>
#include <cstring>

SardineIcon::SardineIcon(const char* name, const al::LayoutInitInfo& initInfo)
    : al::LayoutActor(name)
{

    al::initLayoutActor(this, initInfo, "SardineIcon", 0);

    mInfo = GameModeManager::instance()->getInfo<SardineInfo>();

    initNerve(&nrvSardineIconEnd, 0);

    al::hidePane(this, "SoloIcon");
    al::hidePane(this, "PackIcon");

    kill();
}

void SardineIcon::appear()
{

    al::startAction(this, "Appear", 0);

    al::setNerve(this, &nrvSardineIconAppear);

    al::LayoutActor::appear();
}

bool SardineIcon::tryEnd()
{
    if (!al::isNerve(this, &nrvSardineIconEnd)) {
        al::setNerve(this, &nrvSardineIconEnd);
        return true;
    }
    return false;
}

bool SardineIcon::tryStart()
{

    if (!al::isNerve(this, &nrvSardineIconWait) && !al::isNerve(this, &nrvSardineIconAppear)) {

        appear();

        return true;
    }

    return false;
}

void SardineIcon::exeAppear()
{
    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvSardineIconWait);
    }
}

void SardineIcon::exeWait()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }

    GameTime& curTime = mInfo->mHidingTime;

    if (curTime.mHours > 0) {
        al::setPaneStringFormat(this, "TxtCounter", "%01d:%02d:%02d", curTime.mHours, curTime.mMinutes,
            curTime.mSeconds);
    } else {
        al::setPaneStringFormat(this, "TxtCounter", "%02d:%02d", curTime.mMinutes,
            curTime.mSeconds);
    }

    int playerCount = Client::getMaxPlayerCount();

    if (playerCount > 0) {

        char playerNameBuf[0x100] = { 0 }; // max of 16 player names if player name size is 0x10

        sead::BufferedSafeStringBase<char> playerList = sead::BufferedSafeStringBase<char>(playerNameBuf, 0x200);

        if (mInfo->mIsIt)
            playerList.appendWithFormat("%s\n", Client::instance()->getClientName());

        for (size_t i = 0; i < playerCount; i++) {
            PuppetInfo* curPuppet = Client::getPuppetInfo(i);
            if (curPuppet && curPuppet->isConnected && curPuppet->isIt) {
                playerList.appendWithFormat("%s\n", curPuppet->puppetName);
            }
        }

        al::setPaneStringFormat(this, "TxtPlayerList", playerList.cstr());
    }
}

void SardineIcon::exeEnd()
{

    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

void SardineIcon::showSolo()
{
    al::hidePane(this, "PackIcon");
    al::showPane(this, "SoloIcon");
}

void SardineIcon::showPack()
{
    al::hidePane(this, "SoloIcon");
    al::showPane(this, "PackIcon");
}

namespace {
NERVE_IMPL(SardineIcon, Appear)
NERVE_IMPL(SardineIcon, Wait)
NERVE_IMPL(SardineIcon, End)
}