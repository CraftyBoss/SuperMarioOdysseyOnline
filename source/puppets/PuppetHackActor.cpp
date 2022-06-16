#include "actors/PuppetHackActor.h"
#include "al/util.hpp"
#include "logger.hpp"

PuppetHackActor::PuppetHackActor(const char *name) : al::LiveActor(name) {}

void PuppetHackActor::init(al::ActorInitInfo const &initInfo) {

    // Logger::log("Creating Hack Puppet: %s\n", mHackType.cstr());

    al::initActorWithArchiveName(this, initInfo, mHackType, nullptr);

    al::hideSilhouetteModelIfShow(this);

    if(al::isExistDitherAnimator(this)) {
        // Logger::log("Disabling Dither Animator.\n");
        al::invalidateDitherAnim(this);
    }

    if (al::isExistCollisionParts(this)) {
        // Logger::log(("Disabling Collision.\n"));
        al::invalidateCollisionParts(this);
    }

    al::invalidateHitSensors(this);

    al::invalidateClipping(this);

    al::offCollide(this);

    makeActorDead();

    startHackAnim(true); // this hack puppet will always be captured so its Hack visibility should be true

    startAction("Wait");
}

void PuppetHackActor::initAfterPlacement() {
    al::LiveActor::initAfterPlacement();
}

void PuppetHackActor::initOnline(PuppetInfo *pupInfo, const char *hackType) {
    mInfo = pupInfo;
    mHackType = hackType;
}

void PuppetHackActor::movement() {
    al::LiveActor::movement();
}

void PuppetHackActor::control() {

}

void PuppetHackActor::startAction(const char *actName) {
    if(al::tryStartActionIfNotPlaying(this, actName)) {
        const char *curActName = al::getActionName(this);
        if(curActName) {
            if(al::isSklAnimExist(this, curActName)) {
                al::clearSklAnimInterpole(this);
            }
        }
    }
}

void PuppetHackActor::startHackAnim(bool isOn) {

    const char *animName = isOn ? "HackOn" : "HackOff";
    const char *capOffName = isOn ? "HackOnCapOff" : "HackOffCapOff";

    if (al::isVisAnimExist(this, animName)) {
        al::startVisAnim(this, animName);
    } else if (al::isVisAnimExist(this, capOffName)) {
        al::startVisAnim(this, capOffName);
    }

    if (al::isMtpAnimExist(this, animName)) {
        al::startMtpAnim(this, animName);
    } else if (al::isMtpAnimExist(this, capOffName)) {
        al::startMtpAnim(this, capOffName);
    }

    if (al::isMclAnimExist(this, animName)) {
        al::startMclAnim(this, animName);
    } else if (al::isMclAnimExist(this, capOffName)) {
        al::startMclAnim(this, capOffName);
    }

    // note: we will need to handle special names for hack start anims 

}