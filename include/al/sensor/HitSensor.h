#pragma once

#include "al/sensor/SensorHitGroup.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"

namespace al
{

    class LiveActor;

    class HitSensor
    {
    public:
        HitSensor(al::LiveActor *, const char *, unsigned int, float, unsigned short, const sead::Vector3<float> *, const sead::Matrix34<float> *, const sead::Vector3<float> &);

        bool trySensorSort();
        void setFollowPosPtr(const sead::Vector3<float> *);
        void setFollowMtxPtr(const sead::Matrix34<float> *);
        void validate();
        void invalidate();
        void validateBySystem();
        void invalidateBySystem();
        void update();
        void addHitSensor(al::HitSensor *);

        const char* mName; // _0
        int _8;
        float _unkC;
        float _10;
        float _14;
        float _18;
        unsigned short mMaxSensorCount; // _1C
        unsigned short mSensorCount; // _1E
        al::HitSensor** mSensors; // _20
        unsigned long _28;
        al::SensorHitGroup* mHitGroup; // _30
        bool mIsValidBySystem; // _38
        bool mIsValid; // _39
        al::LiveActor* mParentActor; // _40
        const sead::Vector3<float>* mFollowPos; // _48
        const sead::Matrix34<float>* mFollowMtx; // _50
    };
};