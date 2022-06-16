#pragma once

#include "al/LiveActor/LiveActor.h"
#include "sead/container/seadPtrArray.h"

class PlayerModelHolder {
public:
    struct Entry {
        sead::FixedSafeString<0x80> mName;
        al::LiveActor* mLiveActor;
    };

    PlayerModelHolder(unsigned int);
    void registerModel(al::LiveActor*, char const*);
    void changeModel(char const*);
    al::LiveActor* findModelActor(char const*) const;
    al::LiveActor* tryFindModelActor(char const*) const;
    bool isCurrentModelLabel(char const*) const;
    bool isCurrentModelLabelSubString(char const*) const;

    sead::PtrArray<Entry> mBuffer;
    Entry* currentModel;
    sead::FixedSafeString<0x80> _10;

};