#pragma once

#include "GameSystemInfo.h"
#include "al/nerve/NerveExecutor.h"

class GameSystem : public al::NerveExecutor {
    public:
        void init();
        void *gap;
        al::GameSystemInfo* mSystemInfo;  // 0x18
        // 0x78 GameConfigData
};