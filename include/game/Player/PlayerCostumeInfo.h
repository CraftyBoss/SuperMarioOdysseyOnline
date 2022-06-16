#pragma once

struct PlayerBodyCostumeInfo {
    PlayerBodyCostumeInfo() = default;
    PlayerBodyCostumeInfo(const char *name) {
        costumeName = name;
    };
    const char *costumeName;
    int mWarmLevel = 0;
    bool mIsIgnoreTemperature = false;
    bool mIsUseHeadSuffix = false;
    bool mIsBigEar = false;
    bool mIsHideHeadHair = false;
    bool mIsUseBodyHair = false;
    bool mIsExistHairNoCap = false;
    bool mIsUseShortHead = false;
    bool mIsNoPairHead = false;
    bool mIsMario64 = false;
    bool mIsHidePainNose = false;
    bool mIsUseBeard = false;
    bool mIsUseEarringPeach = false;
    bool mIsUseEarringLink = false;
};

struct PlayerHeadCostumeInfo {
    
    PlayerHeadCostumeInfo() = default;
    PlayerHeadCostumeInfo(const char *name) {
        costumeName = name;
    };

    const char *costumeName;
    bool mIsFullFace = false;
    bool mIsShrinkNose = false;
    bool mIsPreventHead = false;
    bool mIsEnableBigEar = false;
    bool mIsEnableHairNoCap = false;
    bool mIsMario64 = false;
    bool mIsHaveShort = false;
    bool mIsHideBeard = false;
    bool mIsHideEarringPeach = false;
    bool mIsHideEarringLink = false;
    bool mIsUseStrap = false;
    bool mIsInvisibleHead = false;
};

class PlayerCostumeInfo {
    public:
        PlayerCostumeInfo(void) {
            mBodyInfo = {0};
            mHeadInfo = {0};
        };

        void init(PlayerBodyCostumeInfo const *body, PlayerHeadCostumeInfo const *head) {
            mBodyInfo = body;
            mHeadInfo = head;
        };

        bool isEnableBigEar(void) const;
        bool isEnableHairNoCap(void) const;
        bool isEnableCostume2D(void) const;
        bool isNeedShrinkNose(void) const;
        bool isNeedBodyHair(void) const;
        bool isNeedSyncBodyHair(void) const;
        bool isNeedFullFaceAnim(void) const;
        bool isHidePainNose(void) const;
        bool isEnableEarring(void) const;
        bool isSyncFaceBeard(void) const;
        bool isSyncStrap(void) const;
        bool isFollowJoeStrap(void) const;
        bool isPreventHeadPain(void) const;
        bool isInvisibleHead(void) const;

        int calcWarmLevel(int level);

        const PlayerBodyCostumeInfo *mBodyInfo;
        const PlayerHeadCostumeInfo *mHeadInfo;
};