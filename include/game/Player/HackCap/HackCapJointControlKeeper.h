#pragma once

#include "al/LiveActor/LiveActor.h"
#include "sead/math/seadQuat.h"

class HackCapJointControlKeeper {
    public:
        HackCapJointControlKeeper(void);
        void initCapJointControl(al::LiveActor *);
        void initDisplayCapJointControl(al::LiveActor *);
        void updateRotateThrowZ(float,float);
        void updateRotateStayZ(float);
        void updateRotateY(float);

        sead::Vector3f mJointRot = sead::Vector3f();
        float mSkew = 0;
};
