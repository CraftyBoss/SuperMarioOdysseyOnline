#include "cameras/CameraPoserCustom.h"
#include <math.h>
#include "al/camera/CameraPoser.h"
#include "al/camera/alCameraPoserFunction.h"
#include "al/util.hpp"
#include "al/util/MathUtil.h"
#include "al/util/VectorUtil.h"
#include "logger.hpp"
#include "sead/gfx/seadCamera.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadVectorCalcCommon.h"

namespace cc {

CameraPoserCustom::CameraPoserCustom(const char* poserName) : CameraPoser(poserName) {

    this->initOrthoProjectionParam();
}

void CameraPoserCustom::init(void) {
    alCameraPoserFunction::initSnapShotCameraCtrlZoomRollMove(
        this);  // this makes the snapshot camera have the abilities of the normal snapshot cam, but
                // is locked rotationally
    alCameraPoserFunction::initCameraVerticalAbsorber(this);
    alCameraPoserFunction::initCameraAngleCtrl(this);
}

void CameraPoserCustom::loadParam(al::ByamlIter const& paramIter) {
    al::tryGetByamlF32(&mOffsetY, paramIter, "OffsetY");
    al::tryGetByamlF32(&mDist, paramIter, "Distance");
    al::tryGetByamlF32(&mSnapSpeed, paramIter, "GravitySnapSpeed");
    al::tryGetByamlBool(&mIsResetAngleIfSwitchTarget, paramIter, "IsResetAngleIfSwitchTarget");
}

void normalize2(sead::Vector3f &v, float inv) {
    float len = sead::Vector3CalcCommon<float>::length(v);

    if (len > 0)
    {
        float inv_len = inv / len;
        v.x *= inv_len;
        v.y *= inv_len;
        v.z *= inv_len;
    }
}

void CameraPoserCustom::start(al::CameraStartInfo const&) {

    sead::Vector3f faceDir;
    sead::Vector3f targetFront;

    if (alCameraPoserFunction::isSceneCameraFirstCalc(this)) {
        alCameraPoserFunction::calcTargetTrans(&mTargetTrans, this);
        mTargetTrans.y += mOffsetY;
        targetFront = sead::Vector3f(0, 0, 0);
        alCameraPoserFunction::calcTargetFront(&targetFront, this);

        faceDir = mTargetTrans - (mDist * targetFront);

    } else {
        sead::LookAtCamera* curLookCam = alCameraPoserFunction::getLookAtCamera(this);

        sead::Vector3f curPos = curLookCam->mPos;

        sead::Vector3f curAt = curLookCam->mAt;

        targetFront = sead::Vector3f(curPos.x - curAt.x, 0.0, curPos.z - curAt.z);

        al::tryNormalizeOrDirZ(&targetFront);

        faceDir = (mDist * targetFront) + mTargetTrans;
    }

    mPosition = faceDir;
}

void CameraPoserCustom::update(void) {
    sead::Vector3f targetDir;

    if (alCameraPoserFunction::isChangeSubTarget(this) && mIsResetAngleIfSwitchTarget) {
        alCameraPoserFunction::calcTargetTrans(&mTargetTrans, this);
        mTargetTrans.y += mOffsetY;
        targetDir = sead::Vector3f(0,0,0);
        alCameraPoserFunction::calcTargetFront(&targetDir, this);

        mPosition = mTargetTrans - (mDist * targetDir);
    }

    sead::Vector3f targetGrav = sead::Vector3f::ey;

    alCameraPoserFunction::calcTargetGravity(&targetGrav, this);
    
    al::lerpVec(&mCameraUp, mCameraUp, -targetGrav, mSnapSpeed);

    alCameraPoserFunction::calcTargetTrans(&mTargetTrans, this);
    mTargetTrans += mCameraUp * mOffsetY;

    targetDir = mPosition - mTargetTrans;
    
    al::tryNormalizeOrDirZ(&targetDir);

    sead::Vector2f playerInput(0, 0);
    alCameraPoserFunction::calcCameraRotateStick(&playerInput, this);

    sead::Vector3f rightAxis;
    rightAxis.setCross(targetDir, mCameraUp);

    float stickSpeed = alCameraPoserFunction::getStickSensitivityScale(this) *
                       alCameraPoserFunction::getStickSensitivityLevel(this);

    sead::Vector3f preLook;
    alCameraPoserFunction::calcPreLookDir(&preLook, this);
    
    sead::Vector3f rotatedVec = targetDir;


    // Horizontal Rotation
    al::rotateVectorDegree(&rotatedVec, rotatedVec, mCameraUp, playerInput.x * -stickSpeed);

    // Vertical Rotation
    al::rotateVectorDegree(&rotatedVec, rotatedVec, rightAxis, playerInput.y * -stickSpeed);

    mAngleH = al::calcAngleOnPlaneDegree(rotatedVec, mPrevTargetDir, mCameraUp);
    mAngleV = al::calcAngleOnPlaneDegree(rotatedVec, mPrevTargetDir, rightAxis);

    mPosition = mTargetTrans + (rotatedVec * mDist);

    mPrevTargetDir = rotatedVec;
}

void CameraPoserCustom::movement() {
    al::CameraPoser::movement();
}

}