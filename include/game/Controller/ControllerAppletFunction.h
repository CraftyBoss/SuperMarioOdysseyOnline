#pragma once

#include "al/gamepad/util.h"

class ControllerAppletFunction {
    public:
        void connectControllerSinglePlay(al::GamePadSystem *);
        void connectControllerSeparatePlay(al::GamePadSystem *);
};