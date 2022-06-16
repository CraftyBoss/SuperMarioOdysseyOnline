#include "helpers.hpp"
#include "al/LiveActor/LiveActor.h"
#include "logger.hpp"
#include "sead/math/seadMathCalcCommon.h"
#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"
#include "sead/time/seadTickSpan.h"
#include "sead/time/seadTickTime.h"

bool isPartOf(const char* w1, const char* w2) {

    int i=0;
    int j=0;

    if(strlen(w1) <= 0) {
        return false;
    }

    while(w1[i]!='\0'){
        if(w1[i] == w2[j])
        {
            int init = i;
            while (w1[i] == w2[j] && w2[j]!='\0')
            {
                j++;
                i++;
            }
            if(w2[j]=='\0'){
                return true;
            }
            j=0;
        }
        i++;
    }
    return false;
}

int indexOf(char *w1, char c1) {

    for (int i = 0; i < strlen(w1); i++)
    {
        if(w1[i] == c1) {
            return i;
        }
    }
    return -1;
}

sead::Vector3f QuatToEuler(sead::Quatf *quat) {

    f32 x = quat->z;
    f32 y = quat->y;
    f32 z = quat->x;
    f32 w = quat->w;

    f32 t0 = 2.0 * (w * x + y * z);
    f32 t1 = 1.0 - 2.0 * (x * x + y * y);
    f32 roll = atan2f(t0, t1);

    f32 t2 = 2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    f32 pitch = asinf(t2);

    f32 t3 = 2.0 * (w * z + x * y);
    f32 t4 = 1.0 - 2.0 * (y * y + z * z);
    f32 yaw = atan2f(t3, t4);

    return sead::Vector3f(yaw, pitch, roll);
}

void logVector(const char *vectorName, sead::Vector3f vector) {
    Logger::log("%s: \nX: %f\nY: %f\nZ: %f\n", vectorName, vector.x, vector.y, vector.z);
}

void logQuat(const char *quatName, sead::Quatf &quat) {
    Logger::log("%s: \nX: %f\nY: %f\nZ: %f\nW: %f\n", quatName, quat.x, quat.y, quat.z, quat.w);
}

float vecMagnitude(sead::Vector3f const &input) {
    return (input.x * input.x + input.y * input.y + input.z * input.z);
}

float quatAngle(sead::Quatf const &q1, sead::Quatf &q2) {
    float dot = (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
    float dotAngle = sead::Mathf::min(abs(dot), 1.0f);

    return dotAngle > 1.0f - 0.000001f ? 0.0f : DEG(sead::Mathf::acos(dotAngle) * 2.0f);
}

bool isInCostumeList(const char *costumeName) {
    for (size_t i = 0; i < sizeof(costumeNames)/sizeof(costumeNames[0]); i++)
    {
        if(al::isEqualString(costumeNames[i], costumeName)) {
            return true;
        }
    }
    return false;
}

const char *tryGetPuppetCapName(PuppetInfo *info) {
    if(info->costumeHead && isInCostumeList(info->costumeHead)) {
        return info->costumeHead;
    }else {
        return "Mario";
    }
}

const char *tryGetPuppetBodyName(PuppetInfo *info) {
    if(info->costumeBody && isInCostumeList(info->costumeBody)) {
        return info->costumeBody;
    }else {
        return "Mario";
    }
}

const char *tryConvertName(const char *className) {
    for (size_t i = 0; i < ACNT(classHackNames); i++)
    {
        if(al::isEqualString(classHackNames[i].className, className)) {
            return classHackNames[i].hackName;
        }
    }
    return className;
}

// Unity Classes

float VisualUtils::SmoothMove(Transform moveTransform, Transform targetTransform, float timeDelta, float closingSpeed, float maxAngularSpeed)
{

    // Position
    
    sead::Vector3f posDiff = *targetTransform.position - *moveTransform.position;
    
    float posDiffMag = posDiff.dot(posDiff);

    if (posDiffMag > 0) {

        float diffSpeed = sead::Mathf::max(k_MinSmoothSpeed, posDiffMag / k_TargetCatchupTime);

        closingSpeed = sead::Mathf::max(closingSpeed, diffSpeed);

        float maxMove = timeDelta * closingSpeed;
        float moveDist = sead::Mathf::min(maxMove, posDiffMag);
        posDiff *= (moveDist / posDiffMag);

        moveTransform.position->x += posDiff.x;
        moveTransform.position->y += posDiff.y;
        moveTransform.position->z += posDiff.z;

        if( moveDist == posDiffMag )
        {
            //we capped the move, meaning we exactly reached our target transform. Time to reset our velocity.
            closingSpeed = 0;
        }
    }
    else
    {
        closingSpeed = 0;
    }

    // Rotation

    if (moveTransform.rotation) {
        float angleDiff = quatAngle(*targetTransform.rotation, *moveTransform.rotation);

        // if rotation is over 150 degrees, snap to new rotation instead of interpolating to it
        if (angleDiff > 0)
        {
            float maxAngleMove = timeDelta * maxAngularSpeed;
            float angleMove = sead::Mathf::min(maxAngleMove, angleDiff);
            float t = angleMove / angleDiff;
            sead::QuatCalcCommon<float>::slerpTo(*moveTransform.rotation, *moveTransform.rotation, *targetTransform.rotation, t);
        }
    }

    return closingSpeed;
}

void killMainPlayer(al::LiveActor* actor) {
    PlayerActorHakoniwa *mainPlayer = (PlayerActorHakoniwa*)al::getPlayerActor(actor, 0);
    
    GameDataFunction::killPlayer(GameDataHolderAccessor(actor));
    mainPlayer->startDemoPuppetable();
    al::setVelocityZero(mainPlayer);
    mainPlayer->mPlayerAnimator->endSubAnim();
    mainPlayer->mPlayerAnimator->startAnimDead();
}

void killMainPlayer(PlayerActorHakoniwa* mainPlayer) {
    GameDataFunction::killPlayer(GameDataHolderAccessor(mainPlayer));
    mainPlayer->startDemoPuppetable();
    al::setVelocityZero(mainPlayer);
    mainPlayer->mPlayerAnimator->endSubAnim();
    mainPlayer->mPlayerAnimator->startAnimDead();
}