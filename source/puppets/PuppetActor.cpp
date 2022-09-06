#include <cmath>
#include <cstddef>
#include "al/model/PartsModel.h"
#include "al/util/SensorUtil.h"
#include "game/Player/PlayerCostumeFunction.h"
#include "game/Player/PlayerCostumeInfo.h"
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
#include "server/gamemode/GameModeManager.hpp"
#include "server/gamemode/GameModeBase.hpp"
#include "server/hns/HideAndSeekMode.hpp"

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

    mCostumeInfo = initMarioModelPuppet(normalModel, initInfo, bodyName, capName, 0, nullptr);

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

void PuppetActor::calcAnim() {
    al::LiveActor::calcAnim();
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
            if (GameModeManager::instance()->isModeAndActive(GameMode::HIDEANDSEEK)) {
                mNameTag->mIsAlive =
                    GameModeManager::instance()->getMode<HideAndSeekMode>()->isPlayerIt() && mInfo->isIt;
                
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

const char *executorName = "ＮＰＣ";

PlayerCostumeInfo* initMarioModelPuppet(al::LiveActor* player,
                                                        const al::ActorInitInfo& initInfo,
                                                        const char* bodyName, const char* capName,
                                                        int subActorNum,
                                                        al::AudioKeeper* audioKeeper) {

    // Logger::log("Loading Resources for Mario Puppet Model.\n");


    al::ActorResource* modelRes = al::findOrCreateActorResourceWithAnimResource(
        initInfo.mResourceHolder, al::StringTmp<0x100>("ObjectData/%s", bodyName).cstr(),
        al::StringTmp<0x100>("ObjectData/%s", "PlayerAnimation").cstr(), 0, false);

    // Logger::log("Creating Body Costume Info.\n");

    PlayerBodyCostumeInfo* bodyInfo =
        PlayerCostumeFunction::createBodyCostumeInfo(modelRes->mResourceModel, bodyName);

    // Logger::log("Initializing Basic Actor Data.\n");

    al::initActorSceneInfo(player, initInfo);
    al::initActorPoseTQGSV(player);
    al::initActorSRT(player, initInfo);

    al::initActorModelKeeper(player, initInfo,
                             al::StringTmp<0x100>("ObjectData/%s", bodyName).cstr(), 6,
                             al::StringTmp<0x100>("ObjectData/%s", "PlayerAnimation").cstr());

    // Logger::log("Creating Material Category for Player Type\n");
    
    al::ModelMaterialCategory::tryCreate(
        player->mModelKeeper->mModelCtrl, "Player",
        initInfo.mActorSceneInfo.mGfxSysInfo->mMaterialCategoryKeeper);

    // Logger::log("Initing Skeleton.\n");
    
    al::initPartialSklAnim(player, 1, 1, 32);
    al::addPartialSklAnimPartsListRecursive(player, "Spine1", 0);

    // Logger::log("Setting Up Executor Info.\n");

    al::initExecutorUpdate(player, initInfo, executorName);
    al::initExecutorDraw(player, initInfo, executorName);
    al::initExecutorModelUpdate(player, initInfo);

    // Logger::log("Getting InitEffect Byml from resource.\n");

    al::ByamlIter iter;
    if (al::tryGetActorInitFileIter(&iter, modelRes->mResourceModel, "InitEffect", 0)) {
        const char *effectKeeperName;
        if (iter.tryGetStringByKey(&effectKeeperName, "Name")) {

            // Logger::log("Initializing Effect Keeper.\n");

            al::initActorEffectKeeper(player, initInfo, effectKeeperName);
        }
    }

    // Logger::log("Initing Player Audio.\n");

    PlayerFunction::initMarioAudio(player, initInfo, modelRes->mResourceModel, false, audioKeeper);
    al::initActorActionKeeper(player, modelRes, bodyName, 0);
    al::setMaterialProgrammable(player);

    // Logger::log("Creating Sub-Actor Keeper.\n");

    al::SubActorKeeper* actorKeeper = al::SubActorKeeper::tryCreate(player, 0, subActorNum);

    if (actorKeeper) {
        player->initSubActorKeeper(actorKeeper);
    }

    actorKeeper->init(initInfo, 0, subActorNum);

    // Logger::log("Initializing Sub-Actors.\n");

    int subModelNum = al::getSubActorNum(player);

    if (subModelNum >= 1) {
        for (int i = 0; i < subModelNum; i++) {
            al::LiveActor* subActor = al::getSubActor(player, i);
            const char* actorName = subActor->getName();

            if (!al::isEqualString(actorName, "シルエットモデル")) {
                al::initExecutorUpdate(subActor, initInfo, executorName);
                al::initExecutorDraw(subActor, initInfo, executorName);
                al::setMaterialProgrammable(subActor);
            }
        }
    }

    // Logger::log("Creating Clipping.\n");

    al::initActorClipping(player, initInfo);
    al::invalidateClipping(player);

    // Logger::log("Getting Cap Model/Head Model Name.\n");
    
    const char *capModelName;

    if (bodyInfo->mIsUseHeadSuffix) {
        if (al::isEqualString(bodyInfo->costumeName, capName)) {
            capModelName = "";
        } else {
            capModelName = capName;
        }
    } else {
        capModelName = "";
    }

    const char *headType;

    if (!al::isEqualSubString(capName, "Mario64")) {
        if (bodyInfo->mIsUseShortHead && al::isEqualString(capName, "MarioPeach")) {
            headType = "Short";
        } else {
            headType = "";
        }
    } else if (al::isEqualString(bodyInfo->costumeName, "Mario64")) {
        headType = "";
    } else if (al::isEqualString(bodyInfo->costumeName, "Mario64Metal")) {
        headType = "Metal";
    } else {
        headType = "Other";
    }

    // Logger::log("Creating Head Costume Info. Cap Model: %s. Head Type: %s. Cap Name: %s.\n", capModelName, headType, capName);

    PlayerHeadCostumeInfo* headInfo = initMarioHeadCostumeInfo(
        player, initInfo, "頭", capName, headType, capModelName);

    // Logger::log("Creating Costume Info.\n");

    PlayerCostumeInfo* costumeInfo = new PlayerCostumeInfo();
    costumeInfo->init(bodyInfo, headInfo);

    if (costumeInfo->isNeedBodyHair()) {

        Logger::log("Creating Body Hair Parts Model.\n");

        al::PartsModel* partsModel = new al::PartsModel("髪");

        partsModel->initPartsFixFile(
            player, initInfo,
            al::StringTmp<0x100>("%sHair%s", bodyName,
                                 costumeInfo->isEnableHairNoCap() ? "NoCap" : "")
                .cstr(),
            0, "Hair");

        al::initExecutorUpdate(partsModel, initInfo, executorName);
        al::initExecutorDraw(partsModel, initInfo, executorName);
        al::setMaterialProgrammable(partsModel);
        partsModel->makeActorDead();
        al::onSyncAppearSubActor(player, partsModel);
        al::onSyncClippingSubActor(player, partsModel);
        al::onSyncAlphaMaskSubActor(player, partsModel);
        al::onSyncHideSubActor(player, partsModel);
    }

    // Logger::log("Initing Depth Model.\n");

    PlayerFunction::initMarioDepthModel(player, false, false);

    // Logger::log("Creating Retarget Info.\n");

    rs::createPlayerSklRetargettingInfo(player, sead::Vector3f::ones);

    // Logger::log("Making Player Model Dead.\n");

    player->makeActorDead();
    return costumeInfo;
}

PlayerHeadCostumeInfo* initMarioHeadCostumeInfo(al::LiveActor* player,
                                                const al::ActorInitInfo &initInfo,
                                                const char* headModelName, const char* capModelName,
                                                const char* headType, const char* headSuffix) {

    al::PartsModel* headModel = new al::PartsModel(headModelName);

    al::StringTmp<0x80> headArcName("%sHead%s", capModelName, headType);
    al::StringTmp<0x100> arcSuffix("Head");
    if (headSuffix) arcSuffix.format("Head%s", headSuffix);

    headModel->initPartsFixFile(player, initInfo, headArcName.cstr(), 0, arcSuffix.cstr());
    al::setMaterialProgrammable(headModel);

    al::initExecutorUpdate(headModel, initInfo, executorName);
    al::initExecutorDraw(headModel, initInfo, executorName);

    headModel->makeActorDead();

    al::onSyncAppearSubActor(player, headModel);
    al::onSyncClippingSubActor(player, headModel);
    al::onSyncAlphaMaskSubActor(player, headModel);
    al::onSyncHideSubActor(player, headModel);

    al::PartsModel* capEyesModel = new al::PartsModel("キャップの目");
    capEyesModel->initPartsFixFile(headModel, initInfo, "CapManHeroEyes", "", 0);

    al::onSyncClippingSubActor(headModel, capEyesModel);
    al::onSyncAlphaMaskSubActor(headModel, capEyesModel);
    al::onSyncHideSubActor(headModel, capEyesModel);

    al::setMaterialProgrammable(headModel);
    headModel->makeActorDead();

    return PlayerCostumeFunction::createHeadCostumeInfo(al::getModelResource(headModel), capModelName, false);
    
}