#pragma once

#include "al/camera/CameraPoser.h"
#include "al/nerve/NerveExecutor.h"
#include "math/seadVector.h"

namespace al {
class CameraVerticalAbsorber2DGalaxy : public al::NerveExecutor {
public:
    CameraVerticalAbsorber2DGalaxy(void);
    
    void start(al::CameraPoser const*);
    void update(al::CameraPoser const*);
    void applyLimit(sead::Vector3f* output);

    void exeNone(void);
    void exeGround(void);
    void exeLimit(void);
    void exeLimitOver(void);
    void exeLimitAfter(void);

    sead::Vector3f mTargetTrans;
    sead::Vector3f mTargetGravity;
    sead::Vector3f mTargetUp;
    bool mIsTargetCollideGround;
    sead::Vector3f mPrevTargetTrans;
    sead::Vector3f mPrevTargetGravity;
    float unkFloat;
    sead::Vector3f mLimit;
    sead::Vector3f unkVec;
    float unkFloat2;

};

static_assert(sizeof(CameraVerticalAbsorber2DGalaxy) == 0x70, "");


}