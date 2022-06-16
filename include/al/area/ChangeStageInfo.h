#pragma once

#include "al/actor/Placement.h"

#include "game/GameData/GameDataHolder.h"

#include <sead/math/seadVector.h>
#include <sead/math/seadMatrix.h>

class ChangeStageInfo {
    public:
        enum SubScenarioType : unsigned int {
            UNK,
            UNK1,
            UNK2,
            UNK3,
            UNK4
        };

        ChangeStageInfo(const GameDataHolder *mHolder, const al::PlacementInfo &placementInfo);
        ChangeStageInfo(const GameDataHolder *mHolder, const al::PlacementInfo &placementInfo, const char *unk1, const char *unk2, bool unk3, int unk4, SubScenarioType type);
        ChangeStageInfo(const GameDataHolder *mHolder, const char *changeId, const char *stageName, bool isReturn, int scenarioNo, SubScenarioType type);
        void init(const al::PlacementInfo &placement, const GameDataHolder *mHolder);
        void init(void);
        void copy(const ChangeStageInfo &other);
        inline void findScenarioNoByList(const GameDataHolder *holder);
        bool isSubScenarioTypeLifeRecover(void) const;
        bool isSubScenarioTypeResetMiniGame(void) const;
        void setWipeType(const char *type);
        void calcTrans(sead::Vector3f *result, const al::PlacementInfo &info);

        sead::FixedSafeString<0x80> changeStageId; // 0x0 (Size: 0x98)
        sead::FixedSafeString<0x80> changeStageName; // 0xA0
        sead::FixedSafeString<0x80> placementString; // 0x138
        bool isReturn; // 0x1C8
        int scenarioNo; // 0x1CC or 0x134
        SubScenarioType subType; // 0x1D0
        sead::FixedSafeString<0x80> wipeType; // 0x1D8
        int hintPriority; // 0x270
        
};