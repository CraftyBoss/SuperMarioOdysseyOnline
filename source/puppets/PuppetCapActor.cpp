#include "actors/PuppetCapActor.h"
#include "al/util/MathUtil.h"

PuppetCapActor::PuppetCapActor(const char *name) : al::LiveActor(name) {}

void PuppetCapActor::init(al::ActorInitInfo const &initInfo) {

    sead::FixedSafeString<0x20> capModelName;

    PlayerFunction::createCapModelName(&capModelName, tryGetPuppetCapName(mInfo));

    PlayerFunction::initCapModelActorDemo(this, initInfo, capModelName.cstr());

    al::hideSilhouetteModelIfShow(this);

    al::initExecutorModelUpdate(this, initInfo);

    mJointKeeper = new HackCapJointControlKeeper();

    mJointKeeper->initCapJointControl(this);

    makeActorDead();
}

void PuppetCapActor::initAfterPlacement() {
    al::LiveActor::initAfterPlacement();
}

void PuppetCapActor::initOnline(PuppetInfo *pupInfo) {
    mInfo = pupInfo;
}

void PuppetCapActor::movement() {
    al::LiveActor::movement();
}

void PuppetCapActor::control() {
    if(mInfo->capAnim) {
        startAction(mInfo->capAnim);
    }

    sead::Vector3f *cPos = al::getTransPtr(this);

    if(*cPos != mInfo->capPos) 
    {
        al::lerpVec(cPos, *cPos, mInfo->capPos, 0.45);
    }

    mJointKeeper->mJointRot.x = al::lerpValue(mJointKeeper->mJointRot.x, mInfo->capRot.x, 0.85);
    mJointKeeper->mJointRot.y = al::lerpValue(mJointKeeper->mJointRot.y, mInfo->capRot.y, 0.85);
    mJointKeeper->mJointRot.z = al::lerpValue(mJointKeeper->mJointRot.z, mInfo->capRot.z, 0.85);
    mJointKeeper->mSkew = al::lerpValue(mJointKeeper->mSkew, mInfo->capRot.w, 0.85);
}

void PuppetCapActor::update() {
    al::LiveActor::calcAnim();
    al::LiveActor::movement();
}

void PuppetCapActor::startAction(const char *actName) {
    if(al::tryStartActionIfNotPlaying(this, actName)) {
        const char *curActName = al::getActionName(this);
        if(curActName) {
            if(al::isSklAnimExist(this, curActName)) {
                al::clearSklAnimInterpole(this);
            }
        }
    }
}