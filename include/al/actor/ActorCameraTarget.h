#pragma once

#include "sead/math/seadVector.h"
#include "al/LiveActor/LiveActor.h"
#include "al/camera/CameraTargetBase.h"

namespace al
{
    class ActorCameraTarget : public al::CameraTargetBase
    {
        public:
            ActorCameraTarget(al::LiveActor const *, float, sead::Vector3f const *);

            void calcTrans(sead::Vector3f *) const;
            void calcSide(sead::Vector3f *) const;
            void calcUp(sead::Vector3f *) const;
            void calcFront(sead::Vector3f *) const;
            void calcGravity(sead::Vector3f *) const;
            void calcVelocity(sead::Vector3f *) const;

            al::LiveActor *actor; // 0x10
            sead::Vector3f *pos; // 0x18
            float distance; // 0x20
    };
};