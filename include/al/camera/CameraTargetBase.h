#pragma once

#include "sead/math/seadVector.h"

namespace al {

    struct CameraSubTargetBase;

    class CameraTargetBase {
        public:
            CameraTargetBase();

            virtual void calcSide(sead::Vector3f *) const {return;};
            virtual void calcUp(sead::Vector3f *) const {return;};
            virtual void calcFront(sead::Vector3f *) const {return;};
            virtual void calcGravity(sead::Vector3f *input) const {input->x = -1.f; input->y = 0.f; input->z = 0.f; return;};
            virtual void calcVelocity(sead::Vector3f *) const {return;};
            virtual bool isCollideGround(void) const {return false;};
            virtual bool isInWater(void) const {return false;};
            virtual bool isInMooonGravity(void) const {return false;};
            virtual bool isClimbPole(void) const {return false;};
            virtual bool isGrabCeil(void) const {return false;};
            virtual bool isWallWatch(void) const {return false;};
            virtual bool isInvalidMoveByInput(void) const {return false;};
            virtual bool isEnableEndAfterInterpole(void) const {return false;};
            virtual void update(void) const {return;};
            virtual float getRequestDistance(void) const {return -1.f;};

            bool isActiveTarget; // 0x8
    };
}