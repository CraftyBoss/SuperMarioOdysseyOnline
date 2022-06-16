#pragma once

#include <sead/math/seadQuat.h>
#include <sead/math/seadVector.h>
#include "al/LiveActor/LiveActor.h"

namespace al {

class KeyPoseKeeper;

bool isNearZero(const sead::Vector2f&, float);
void verticalizeVec(sead::Vector3f*, const sead::Vector3f&, const sead::Vector3f&);
bool tryNormalizeOrZero(sead::Vector3f*);
void normalize(sead::Vector3f*);
void turnVecToVecDegree(sead::Vector3f*, const sead::Vector3f&, const sead::Vector3f&, float);
void turnVecToVecRate(sead::Vector3f*, const sead::Vector3f&, const sead::Vector3f&, float);

void calcQuatFront(sead::Vector3f*, const sead::Quatf&);
void makeQuatFrontUp(sead::Quatf *, const sead::Vector3f &,
                     const sead::Vector3f &);

float calcAngleToTargetH(al::LiveActor const*,sead::Vector3f const&);
float calcAngleToTargetV(al::LiveActor const*,sead::Vector3f const&);
float calcAngleRadian(sead::Vector3f const&,sead::Vector3f const&);
float calcAngleDegree(sead::Vector3f const&,sead::Vector3f const&);
float calcAngleDegree(sead::Vector2f const&,sead::Vector2f const&);
bool tryCalcAngleDegree(float *,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleOnPlaneRadian(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleOnPlaneDegree(sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);
float calcAngleOnPlaneDegreeOrZero(sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
bool tryCalcAngleOnPlaneDegree(float *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
float calcAngleSignOnPlane(sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);

void calcDir(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&);
void calcDirBetweenSensors(sead::Vector3f *,al::HitSensor const*,al::HitSensor const*);
void calcDirBetweenSensorsH(sead::Vector3f *,al::HitSensor const*,al::HitSensor const*);
void calcDirBetweenSensorsNormal(sead::Vector3f *,al::HitSensor const*,al::HitSensor const*,sead::Vector3f);
void calcDirClockwiseToDir(sead::Vector3f *,al::LiveActor const*,sead::Vector3f const&);
void calcDirClockwiseToPlayer(sead::Vector3f *,al::LiveActor const*);
void calcDirClockwiseToPos(sead::Vector3f *,al::LiveActor const*,sead::Vector3f const&);
void calcDirFromLongitudeLatitude(sead::Vector3f *,float,float);
void calcDirH(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&);
void calcDirIndexNearXY(sead::Vector3<int> const&,sead::Vector3<int> const&);
void calcDirIndexNearYZ(sead::Vector3<int> const&,sead::Vector3<int> const&);
void calcDirIndexNearZX(sead::Vector3<int> const&,sead::Vector3<int> const&);
void calcDirOnPlane(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&);
void calcDirSlide(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&);
void calcDirToActor(sead::Vector3f *,al::LiveActor const*,al::LiveActor const*);
void calcDirToActorH(sead::Vector3f *,al::LiveActor const*,al::LiveActor const*);
void calcDirToActorH(sead::Vector3f *,al::LiveActor const*,sead::Vector3f const&);
void calcDirToNextKey(sead::Vector3f *,al::KeyPoseKeeper const*);
void calcDirVerticalAny(sead::Vector3f *,sead::Vector3f const&);
void calcDirViewInput(sead::Vector3f *,sead::Vector2f const&,sead::Vector3f const&,sead::Matrix34f const*);
void calcDirViewInput2D(sead::Vector3f *,sead::Vector2f const&,sead::Vector3f const&,sead::Matrix34f const*);

void rotateVectorCenterDegree(sead::Vector3f *output, sead::Vector3f const &dir,sead::Vector3f const &axis, sead::Vector3f const &center, float angle);

void rotateVectorDegree(sead::Vector3f* output, const sead::Vector3f& dir,
                        const sead::Vector3f& axis, float angle);

void rotateVectorDegreeX(sead::Vector3f*, float);

void rotateVectorDegreeY(sead::Vector3f*, float);

void rotateVectorDegreeZ(sead::Vector3f*, float);

void rotateVectorQuat(sead::Vector3f *,sead::Quatf const&);

}  // namespace al
