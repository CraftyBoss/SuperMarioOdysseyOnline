#pragma once

#include "types.h"
#include "al/LiveActor/LiveActor.h"
#include "al/sensor/SensorHitGroup.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "HitSensor.h"

namespace al
{
    class HitSensorKeeper
    {
    public:
        HitSensorKeeper(int);
        bool addSensor(al::LiveActor *sensorHost, char const *sensorName, u32 typeEnum, float radius, ushort maxCount, const sead::Vector3f *position, const sead::Matrix34f *matrix, const sead::Vector3f &scale);
        void update(void);
        int getSensorNum(void) const;
        al::HitSensor *getSensor(int) const;
        void clear(void);
        void validate(void);
        void invalidate(void);
        void validateBySystem(void);
        void invalidateBySystem(void);
        al::HitSensor *getSensor(char const *sensorName) const;
    };
};