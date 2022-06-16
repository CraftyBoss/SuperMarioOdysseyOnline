#pragma once

#include "game/System/GameSystemInfo.h"

namespace al {
    class SequenceInitInfo {
        public:
            SequenceInitInfo(al::GameSystemInfo const *sysInf) : mSystemInfo(sysInf) {}
            const GameSystemInfo *mSystemInfo;
    };
}