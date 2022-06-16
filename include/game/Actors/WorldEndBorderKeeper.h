#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/nerve/NerveExecutor.h"
#include "math/seadVector.h"

class WorldEndBorderKeeper : public al::NerveExecutor {
public:
    WorldEndBorderKeeper(al::LiveActor const*);
    void exeInside(void);
    void exeOutside(void);
    void exePullBack(void);
    void exeWaitBorder(void);
    void reset(void);
    void update(sead::Vector3f const&,sead::Vector3f const&,bool);
    ~WorldEndBorderKeeper();

    al::LiveActor* mActor;
    sead::Vector3f unkVec1; // = sead::Vector3f::ex;
    sead::Vector3f unkVec2; // = sead::Vector3f::ex;
};