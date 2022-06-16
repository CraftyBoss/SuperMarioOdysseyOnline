#pragma once

#include "sead/time/seadTickTime.h"
#include "sead/time/seadDateTime.h"
#include "sead/math/seadQuatCalcCommon.hpp"

struct Time {

    static void calcTime();

    static sead::TickTime prevTime;
    static sead::TickSpan deltaSpan;
    static float deltaTime;
};