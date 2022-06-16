#pragma once

#include "al/actor/IUseName.h"

namespace al
{
    class StageSwitchKeeper;
    
    class IUseStageSwitch : virtual public al::IUseName
    {
    public:
        virtual al::StageSwitchKeeper* getStageSwitchKeeper() const = 0;
        virtual void initStageSwitchKeeper() = 0;
    };

    class StageSwitchKeeper
    {
    public:
        StageSwitchKeeper();
    };
};