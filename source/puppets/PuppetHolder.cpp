#include "puppets/PuppetHolder.hpp"
#include <math.h>
#include "actors/PuppetActor.h"
#include "al/util.hpp"
#include "al/util/LiveActorUtil.h"
#include "container/seadPtrArray.h"
#include "heap/seadHeap.h"
#include "heap/seadHeapMgr.h"
#include "logger.hpp"

PuppetHolder::PuppetHolder(int size) {
    if(!mPuppetArr.tryAllocBuffer(size, nullptr)) {
        Logger::log("Buffer Alloc Failed on Puppet Holder!\n");
    }
}
/**
 * @brief resizes puppet ptr array by creating a new ptr array and storing previous ptrs in it, before freeing the previous array
 * 
 * @param size the size of the new ptr array
 * @return returns true if resizing was sucessful
 */
bool PuppetHolder::resizeHolder(int size) {

    if (mPuppetArr.capacity() == size)
        return true;  // no need to resize if we're already at the same capacity

    sead::Heap *seqHeap = sead::HeapMgr::instance()->findHeapByName("SequenceHeap", 0);

    if (!mPuppetArr.isBufferReady())
        return mPuppetArr.tryAllocBuffer(size, seqHeap);
        
    sead::PtrArray<PuppetActor> newPuppets = sead::PtrArray<PuppetActor>();

    if (newPuppets.tryAllocBuffer(size, seqHeap)) {
        
        int curPupCount = mPuppetArr.size();

        for (int i = 0; i < curPupCount > size ? size : curPupCount; i++) {
            newPuppets.pushBack(mPuppetArr[i]);
        }

        mPuppetArr.freeBuffer();

        mPuppetArr = newPuppets;

        return true;
    } else {
        return false;
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

        if(curInfo->isInSameStage && al::isDead(curPuppet)) {
            curPuppet->makeActorAlive();

            curPuppet->emitJoinEffect();
        }else if(!curInfo->isInSameStage && !al::isDead(curPuppet)) {
            curPuppet->makeActorDead();
            
            curPuppet->emitJoinEffect();
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