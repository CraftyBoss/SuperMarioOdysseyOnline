#include "server/DeltaTime.hpp"

sead::TickTime Time::prevTime;
sead::TickSpan Time::deltaSpan;
float Time::deltaTime;

void Time::calcTime() {
    Time::deltaSpan = Time::prevTime.diffToNow();
    Time::prevTime.setNow();
    Time::deltaTime = fabsf((double)Time::deltaSpan.toNanoSeconds() / 1000000000.0);
}