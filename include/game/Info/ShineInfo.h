#pragma once

#include "sead/prim/seadSafeString.hpp"

#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"

struct ShineData; // unused class identical to this one (maybe)
struct QuestInfo;
struct UniqObjInfo;

namespace al {
    class IUseMessageSystem;
}

class ShineInfo {
    public:
        ShineInfo(void);

        void clear(void);
        void init(const char *, const char *, const char *, QuestInfo const *info, int shineId);
        void initForHintPhoto(const al::LiveActor *, const al::IUseMessageSystem *, const al::ActorInitInfo &);
        bool isEmpty(void) const;
        bool isEqual(const ShineInfo *) const;
        bool isEqual(const ShineData *) const;
        void writeShineData(ShineData *) const;
        void readShineData(ShineData *);
        void readShineData(const UniqObjInfo *);
        void copyShineInfo(const ShineInfo *);

        sead::FixedSafeString<0x80> stageName = sead::FixedSafeString<0x80>(); // 0x0 (Size: 0x98)
        sead::FixedSafeString<0x80> objectId = sead::FixedSafeString<0x80>(); // 0xA0
        sead::FixedSafeString<0x80> scenObjId = sead::FixedSafeString<0x80>(); // 0x138

        int shineId; // 1C8
        const QuestInfo *curQuest; // 1D0
        bool unkA; // 0x1D8
        unsigned long timeDay; // 0x1E0
};