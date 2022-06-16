#pragma once

#include <sead/math/seadVector.h>

namespace al {

class LiveActor;

void normalize(sead::Vector3f*);
float normalize(float, float, float);
float normalize(signed int, signed int, signed int);

float easeIn(float);
float easeOut(float);
float easeInOut(float);

float modf(float, float);
int modi(int, int);

float sign(float);
int sign(int);

float squareIn(float);
float squareOut(float);

float powerIn(float, float);
float powerOut(float, float);

float lerpValue(float, float, float);

bool isNearZero(float, float);

bool isNearZero(sead::Vector3f const &, float);

template <typename T>
inline T clamp(T value, T min, T max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

float calcSpringDumperForce(float unk1, float unk2, float unk3, float unk4);

void separateVectorHV(sead::Vector3f*, sead::Vector3f*, const sead::Vector3f &,
                      const sead::Vector3f &);

bool tryNormalizeOrDirZ(sead::Vector3f *);
bool tryNormalizeOrDirZ(sead::Vector3f *, sead::Vector3f const&);
bool tryNormalizeOrZero(sead::Vector3f*, sead::Vector3f const&);

float calcAngleToTargetH(LiveActor const*,sead::Vector3f const&);
float calcAngleToTargetV(LiveActor const*,sead::Vector3f const&);
float calcAngleRadian(sead::Vector3f const&,sead::Vector3f const&);
float calcAngleDegree(sead::Vector3f const&,sead::Vector3f const&);
float calcAngleDegree(sead::Vector2f const&,sead::Vector2f const&);
float calcAngleOnPlaneRadian(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleOnPlaneDegree(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleOnPlaneDegreeOrZero(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleSignOnPlane(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
bool tryCalcAngleDegree(float *,sead::Vector3f const&,sead::Vector3f const&);
bool tryCalcAngleOnPlaneDegree(float *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);

};  // namespace al