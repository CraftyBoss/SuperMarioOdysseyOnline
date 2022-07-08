#include <cmath>
#include <cstddef>
#include "al/util/SensorUtil.h"
#include "rs/util/SensorUtil.h"
#include "server/Client.hpp"
#include "al/LiveActor/LiveActor.h"
#include "al/layout/BalloonMessage.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/string/StringTmp.h"
#include "al/util.hpp"
#include "al/util/LiveActorUtil.h"
#include "algorithms/CaptureTypes.h"
#include "logger.hpp"
#include "actors/PuppetActor.h"
#include "math/seadQuat.h"
#include "math/seadVector.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/HideAndSeekMode.hpp"

static const char *subActorNames[] = {
    "顔", // Face
    "目", // Eye
    "頭", // Head
    "左手", // Left Hand
    "右手" // Right Hand
};

PuppetActor::PuppetActor(const char *name) : al::LiveActor(name) {
    mPuppetCap = new PuppetCapActor(name);
    mCaptures = new HackModelHolder();
    mModelHolder = new PlayerModelHolder(3); // Regular Model, 2D Model, 2D Mini Model
}

void PuppetActor::init(al::ActorInitInfo const &initInfo) {

    mPuppetCap->init(initInfo);

    al::initActorWithArchiveName(this, initInfo, "PuppetActor", nullptr);

    const char *bodyName = "Mario";
    const char *capName = "Mario";

    if(mInfo) {
        bodyName = tryGetPuppetBodyName(mInfo);
        capName = tryGetPuppetCapName(mInfo);

        mNameTag = new NameTag(this, *al::getLayoutInitInfo(initInfo), 4900.0f, 5000.0f,
                               mInfo->puppetName);

    }

    al::LiveActor *normalModel = new al::LiveActor("Normal");

    mCostumeInfo = PlayerFunction::initMarioModelCommon(normalModel, initInfo, bodyName, capName, 0, false, nullptr, false, false);

    normalModel->mActorActionKeeper->mPadAndCamCtrl->mRumbleCount = 0; // set rumble count to zero so that no rumble actions will run

    mModelHolder->registerModel(normalModel, "Normal");

    al::LiveActor *normal2DModel = new al::LiveActor("Normal2D");

    PlayerFunction::initMarioModelActor2D(normal2DModel, initInfo, al::StringTmp<0x40>("%s2D", mCostumeInfo->mBodyInfo->costumeName).cstr(), PlayerFunction::isInvisibleCap(mCostumeInfo));

    mModelHolder->registerModel(normal2DModel, "Normal2D");

    al::setClippingInfo(normalModel, 50000.0f, 0);
    al::setClippingNearDistance(normalModel, 50000.0f);

    al::hideSilhouetteModelIfShow(normalModel);

    // "頭" = Head
    // "髪" = Hair
    // "キャップの目" = Cap Eyes
    // "[デモ用]キャップの目" = [Demo] Cap Eyes

    al::LiveActor* headModel = al::getSubActor(normalModel, "頭");
    al::getSubActor(headModel, "キャップの目")->kill();
    al::startVisAnimForAction(headModel, "CapOn");

    mModelHolder->changeModel("Normal");

    startAction("Wait");

    al::validateClipping(normalModel);
    al::validateClipping(normal2DModel);

}

void PuppetActor::initAfterPlacement() { al::LiveActor::initAfterPlacement(); }

void PuppetActor::initOnline(PuppetInfo *pupInfo) {

    mInfo = pupInfo;

    mPuppetCap->initOnline(pupInfo);
}

void PuppetActor::movement() {
    al::LiveActor::movement();
}

void PuppetActor::control() { 
    if(mInfo) {

        al::LiveActor* curModel = getCurrentModel();

        // Animation Updating

        if(!al::isActionPlaying(curModel, mInfo->curSubAnimStr)) {
            startAction(mInfo->curAnimStr);
        }else if(al::isActionEnd(curModel)) {
            startAction(mInfo->curAnimStr);
        }

        if(isNeedBlending()) {
            for (size_t i = 0; i < 6; i++)
            {
                setBlendWeight(i, mInfo->blendWeights[i]);
            }
        }

        // Position & Rotation Handling

        sead::Vector3f* pPos = al::getTransPtr(this);

        sead::Quatf *pQuat = al::getQuatPtr(this);

        if (!mIs2DModel) {
            mClosingSpeed = VisualUtils::SmoothMove({pPos, pQuat}, {&mInfo->playerPos, &mInfo->playerRot}, Time::deltaTime, mClosingSpeed, 1440.0f);
        } else {

            // do not linearly interpolate rotation if model is 2D, and use basic lerp instead of visual util's smooth move

            if(*pPos != mInfo->playerPos) 
            {
                al::lerpVec(pPos, *pPos, mInfo->playerPos, 0.25);
            }

            al::setQuat(this, mInfo->playerRot);
        }

        // Model Updating

        if (!mIs2DModel && mInfo->is2D) {
            changeModel("Normal2D");
            mIs2DModel = true;

        } else if (mIs2DModel && !mInfo->is2D) {
            changeModel("Normal");
            mIs2DModel = false;
        }

        // Capture Updating

        if (mInfo->isCaptured && !mIsCaptureModel) {

            getCurrentModel()->makeActorDead();  // sets previous model to dead so we can try to
                                                 // switch to capture model
            setCapture(mInfo->curHack);
            mIsCaptureModel =  true;
            getCurrentModel()->makeActorAlive(); // make new model alive

        } else if (!mInfo->isCaptured && mIsCaptureModel) {

            getCurrentModel()->makeActorDead(); // make capture model dead
            mModelHolder->changeModel("Normal"); // set player model to normal
            mIsCaptureModel = false;
            getCurrentModel()->makeActorAlive(); // make player model alive

        }

        // Visibility Updating

        if(mInfo->isCapThrow) {
            if(al::isDead(mPuppetCap)) {                
                mPuppetCap->makeActorAlive();
                al::setTrans(mPuppetCap, mInfo->capPos);
            }
        }else {
            if(al::isAlive(mPuppetCap)) {

                mPuppetCap->makeActorDead();

                startAction(mInfo->curSubAnimStr);

                al::LiveActor* headModel = al::getSubActor(curModel, "頭");
                if (headModel) { al::startVisAnimForAction(headModel, "CapOn"); }
            }
        }

        if (mNameTag) {
            if (Client::isSelectedMode(GameMode::HIDEANDSEEK) && Client::isModeActive()) {
                mNameTag->mIsAlive =
                    Client::getMode<HideAndSeekMode>()->isPlayerIt() && mInfo->isIt;
                
            } else {
                if(!mNameTag->mIsAlive)
                    mNameTag->appear();
            }
        }

        // Sub-Actor Updating

        mPuppetCap->update();

        // Syncing

        syncPose();

    }
}

void PuppetActor::makeActorAlive() {
    
    al::LiveActor *curModel = getCurrentModel();

    if (al::isDead(curModel)) {
        curModel->makeActorAlive();
    }

    // update name tag when puppet becomes active again
    if (mInfo) {
        if (mNameTag) {
            mNameTag->setText(mInfo->puppetName);
        }
    }

    al::LiveActor::makeActorAlive();

}

void PuppetActor::makeActorDead() {

    al::LiveActor *curModel = getCurrentModel();
    
    if (!al::isDead(curModel)) {
        curModel->makeActorDead();
    }

    mPuppetCap->makeActorDead();
    
    al::LiveActor::makeActorDead();
}

void PuppetActor::attackSensor(al::HitSensor* source, al::HitSensor* target) {
    
    if (!al::sendMsgPush(target, source)) {
        rs::sendMsgPushToPlayer(target, source);
    }

}

bool PuppetActor::receiveMsg(const al::SensorMsg* msg, al::HitSensor* source,
                             al::HitSensor* target) {

    if ((al::isMsgPlayerTrampleReflect(msg) || rs::isMsgPlayerAndCapObjHipDropReflectAll(msg)) && al::isSensorName(target, "Body"))
    {
        rs::requestHitReactionToAttacker(msg, target, source);
        return true;
    }

    return false;
}

// this is more or less how nintendo does it with marios demo puppet
void PuppetActor::startAction(const char *actName) {

    al::LiveActor* curModel = getCurrentModel();

    if(!actName) return;

    if(al::tryStartActionIfNotPlaying(curModel, actName)) {
        const char *curActName = al::getActionName(curModel);
        if(curActName) {
            if(al::isSklAnimExist(curModel, curActName)) {
                al::clearSklAnimInterpole(curModel);
            }
        }
    }

    for (size_t i = 0; i < 5; i++)
    {
        al::LiveActor* subActor = al::getSubActor(curModel, subActorNames[i]);
        const char *curActName = al::getActionName(curModel);
        if(subActor && curActName) {
            if (al::tryStartActionIfNotPlaying(subActor, curActName)) {
                if(al::isSklAnimExist(curModel, curActName)) {
                    al::clearSklAnimInterpole(curModel);
                }
            }
        }
    }

    al::LiveActor* faceActor = al::tryGetSubActor(curModel, "顔");

    if (faceActor) {
        al::StringTmp<0x80> faceAnim("%sFullFace", actName);
        if (al::tryStartActionIfNotPlaying(faceActor, faceAnim.cstr())) {
            if(al::isSklAnimExist(faceActor, faceAnim.cstr())) {
                al::clearSklAnimInterpole(faceActor);
            }
        }
    }
}

void PuppetActor::hairControl() {

    al::LiveActor *curModel = getCurrentModel();

    if (mCostumeInfo->isNeedSyncBodyHair())
    {
        PlayerFunction::syncBodyHairVisibility(al::getSubActor(curModel, "髪"), al::getSubActor(curModel, "頭"));
    }
    if (mCostumeInfo->isSyncFaceBeard())
    {
        PlayerFunction::syncMarioFaceBeardVisibility(al::getSubActor(curModel, "顔"), al::getSubActor(curModel, "頭"));
    }
    if (mCostumeInfo->isSyncStrap())
    {
        PlayerFunction::syncMarioHeadStrapVisibility(al::getSubActor(curModel, "頭"));
    }
    if (PlayerFunction::isNeedHairControl(mCostumeInfo->mBodyInfo, mCostumeInfo->mHeadInfo->costumeName))
    {
        PlayerFunction::hideHairVisibility(al::getSubActor(curModel, "頭"));
    }
}

bool PuppetActor::isNeedBlending() {
    const char *curActName = al::getActionName(getCurrentModel());
    if(curActName) {
        return al::isEqualSubString(curActName, "Move") || al::isEqualSubString(curActName, "Sand") || al::isEqualSubString(curActName, "MotorcycleRide");
    }else {
        return false;
    }
}

bool PuppetActor::isInCaptureList(const char *hackName) {
    return mCaptures->getCapture(hackName) != nullptr;
}

bool PuppetActor::addCapture(PuppetHackActor* capture, const char* hackType) {

    if (mCaptures->addCapture(capture, hackType)) {
        return true;
    }
    
    return false;
}

void PuppetActor::changeModel(const char* newModel) {
    getCurrentModel()->makeActorDead();
    mModelHolder->changeModel(newModel);
    getCurrentModel()->makeActorAlive();
}

al::LiveActor* PuppetActor::getCurrentModel() {
    if (mIsCaptureModel) {
        al::LiveActor* curCapture = mCaptures->getCurrentActor();
        if (curCapture) {
            return curCapture;
        }
    }
    return mModelHolder->currentModel->mLiveActor;
}

void PuppetActor::debugTeleportCaptures(const sead::Vector3f& pos) {
    for (int i = 0; i < mCaptures->getEntryCount(); i++) {
        al::LiveActor* capture = mCaptures->getCapture(i);
        if (capture) {
            al::setTrans(capture, al::getTrans(getCurrentModel()));
        }
    }
}

void PuppetActor::debugTeleportCapture(const sead::Vector3f& pos, int index) {
    al::LiveActor* capture = mCaptures->getCapture(index);
    if (capture) {
        al::setTrans(capture, al::getTrans(getCurrentModel()));
    }
}

bool PuppetActor::setCapture(const char* captureName) {
    if (captureName && mCaptures->setCurrent(captureName)) {
        mCurCapture = CaptureTypes::FindType(captureName);
        return true;
    } else {
        mCurCapture = CaptureTypes::Type::Unknown;
        return false;
    }
}

void PuppetActor::syncPose() {

    al::LiveActor* curModel = getCurrentModel();

    curModel->mPoseKeeper->updatePoseQuat(al::getQuat(this)); // update pose using a quaternion instead of setting quaternion rotation
    
    al::setTrans(curModel, al::getTrans(this));

}

void PuppetActor::emitJoinEffect() {

    al::tryDeleteEffect(this, "Disappear"); // remove previous effect (if played previously)

    al::tryEmitEffect(this, "Disappear", nullptr);
}