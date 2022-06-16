#pragma once

#include "sead/math/seadVector.h"

namespace al {
    bool isPadTriggerUp(int port);
    bool isPadTriggerDown(int port);
    bool isPadTriggerLeft(int port);
    bool isPadTriggerRight(int port);

    bool isPadTriggerA(int port);
    bool isPadTriggerB(int port);
    bool isPadTriggerX(int port);
    bool isPadTriggerY(int port);

    bool isPadTriggerZL(int port);
    bool isPadTriggerZR(int port);

    bool isPadTriggerL(int port);
    bool isPadTriggerR(int port);

    bool isPadHoldUp(int port);
    bool isPadHoldDown(int port);
    bool isPadHoldLeft(int port);
    bool isPadHoldRight(int port);

    bool isPadHoldA(int port);
    bool isPadHoldB(int port);
    bool isPadHoldX(int port);
    bool isPadHoldY(int port);

    bool isPadHoldL(int port);
    bool isPadHoldR(int port);

    bool isPadHoldZL(int port);
    bool isPadHoldZR(int port);

    sead::Vector2f *getLeftStick(int);
    sead::Vector2f *getRightStick(int);
}