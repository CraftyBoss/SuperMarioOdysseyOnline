#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logger.hpp"
#include "server/gamemode/GameModeTimer.hpp"

// TODO: kill layout if going through loading zone or paused

class SardineIcon : public al::LayoutActor {
public:
    SardineIcon(const char* name, const al::LayoutInitInfo& initInfo);

    void appear() override;

    bool tryStart();
    bool tryEnd();

    void showSolo();
    void showPack();

    void exeAppear();
    void exeWait();
    void exeEnd();

private:
    struct SardineInfo* mInfo;
};

namespace {
NERVE_HEADER(SardineIcon, Appear)
NERVE_HEADER(SardineIcon, Wait)
NERVE_HEADER(SardineIcon, End)
}