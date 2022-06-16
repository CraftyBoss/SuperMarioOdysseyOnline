#include "puppets/HackModelHolder.hpp"

PuppetHackActor *HackModelHolder::getCapture(const char *hackName) { 
    for (size_t i = 0; i < mCaptureCount; i++)
    {
        if(al::isEqualString(mOnlineCaptures[i].className, hackName)) {
            return mOnlineCaptures[i].actor;
        }
    }
    return nullptr; 
};

PuppetHackActor *HackModelHolder::getCapture(int index) { 
    return index <= mCaptureCount ? mOnlineCaptures[index].actor : nullptr; 
};

const char *HackModelHolder::getCaptureClass(int index) {
    return index <= mCaptureCount ? mOnlineCaptures[index].className : "Unknown";
}

bool HackModelHolder::addCapture(PuppetHackActor *capture, const char *hackName) { 
    if(mCaptureCount < ACNT(mOnlineCaptures)) {
        mOnlineCaptures[mCaptureCount].actor = capture;
        strcpy(mOnlineCaptures[mCaptureCount].className, hackName);
        mCaptureCount++;
        return true;
    }
    return false;
};

bool HackModelHolder::removeCapture(const char *hackName) { 
    for (size_t i = 0; i < mCaptureCount; i++)
    {
        if(al::isEqualString(mOnlineCaptures[i].className, hackName)) {
            mOnlineCaptures[i].actor = nullptr;
            strcpy(mOnlineCaptures[i].className, "");
            return true;
        }
    }
    return false;
};

void HackModelHolder::resetList() { 
    
    for (size_t i = 0; i < mCaptureCount; i++)
    {
        mOnlineCaptures[i].actor = nullptr;
        strcpy(mOnlineCaptures[i].className, "");
    }

    mCaptureCount = 0;
};

bool HackModelHolder::setCurrent(const char* hackName) {
    for (size_t i = 0; i < mCaptureCount; i++)
    {
        if(al::isEqualString(mOnlineCaptures[i].className, hackName)) {
            mCurCapture = &mOnlineCaptures[i];
            return true;
        }
    }
    mCurCapture = nullptr; // if we cant find the name of the current capture, assume its not in the list and set the current reference to null.
    return false;
}

PuppetHackActor* HackModelHolder::getCurrentActor() {
    if (mCurCapture) {
        return mCurCapture->actor;
    } else {
        return nullptr;
    }
}
const char* HackModelHolder::getCurrentActorName() {
    if (mCurCapture) {
        return mCurCapture->className;
    } else {
        return nullptr;
    }
}