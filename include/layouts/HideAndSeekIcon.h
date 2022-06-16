#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logger.hpp"
#include "server/gamemode/GameModeTimer.hpp"

// TODO: kill layout if going through loading zone or paused

class HideAndSeekIcon : public al::LayoutActor {
    public:
        HideAndSeekIcon(const char* name, const al::LayoutInitInfo& initInfo);

        void appear() override;

        bool tryStart();
        bool tryEnd();

        void showHiding();
        void showSeeking();
        
        void exeAppear();
        void exeWait();
        void exeEnd();

    private:
        struct HideAndSeekInfo *mInfo;
};

namespace {
    NERVE_HEADER(HideAndSeekIcon, Appear)
    NERVE_HEADER(HideAndSeekIcon, Wait)
    NERVE_HEADER(HideAndSeekIcon, End)
}