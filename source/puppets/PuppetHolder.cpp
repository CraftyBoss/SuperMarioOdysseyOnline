#include "puppets/PuppetHolder.hpp"
#include "al/util.hpp"
#include "logger.hpp"

PuppetHolder::PuppetHolder(int size) {
    mPuppetArr = sead::PtrArray<PuppetActor>();
    if(!mPuppetArr.tryAllocBuffer(size, nullptr)) {
        Logger::log("Buffer Alloc Failed on Puppet Holder!\n");
    }
}

bool PuppetHolder::tryRegisterPuppet(PuppetActor *puppet) {
    if(!mPuppetArr.isFull()) {
        mPuppetArr.pushBack(puppet);
        return true;
    }else {
        return false;
    }
}

bool PuppetHolder::tryRegisterDebugPuppet(PuppetActor *puppet) {
    mDebugPuppet = puppet;
    return true;
}

PuppetActor *PuppetHolder::getDebugPuppet() {
    if(mDebugPuppet) {
        return mDebugPuppet;
    }
    return nullptr;
}

void PuppetHolder::update() {

    for (size_t i = 0; i < mPuppetArr.size(); i++)
    {
        PuppetActor *curPuppet = mPuppetArr[i];
        PuppetInfo *curInfo = curPuppet->getInfo();

        curInfo->isInSameStage = checkInfoIsInStage(curInfo);

        if(curInfo->isInSameStage) {
            curPuppet->makeActorAlive();
        }else if(!curInfo->isInSameStage) {
            curPuppet->makeActorDead();
        }
    }
}

bool PuppetHolder::checkInfoIsInStage(PuppetInfo *info) {
    if (info->isConnected) {
        if (info->scenarioNo < 15) {
            return al::isEqualString(mStageName.cstr(), info->stageName);
        } else {
            return al::isEqualString(mStageName.cstr(), info->stageName) && info->scenarioNo == mScenarioNo;
        }
    }
    
    return false;
}

void PuppetHolder::setStageInfo(const char *stageName, u8 scenarioNo) {
    mStageName = stageName;
    mScenarioNo = scenarioNo;
}