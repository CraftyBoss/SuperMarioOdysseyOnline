#pragma once

#include "game/GameData/GameDataHolderAccessor.h"
#include "game/System/GameSystemInfo.h"
#include "types.h"

namespace al {
    struct SceneInitInfo {
        al::GameSystemInfo * gameSysInfo;
        GameDataHolderAccessor gameDataHolder;
        undefined field_0x10[8];
        char *initStageName;
        u32 scenarioNo;
    };
}
