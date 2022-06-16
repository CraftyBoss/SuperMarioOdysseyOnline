#pragma once

#include "LayoutActor.h"
#include "TalkMessageVoicePlayer.h"

namespace al {

    struct BalloonMessageInitParam {
        const char *mActorName;  // 0x0
        const char *mLayoutName; // 0x8
        const char *mPaneName;   // 0x10
        const char *mMessage;    // 0x18
        float mStartDist;          // 0x20
        float mEndDist;          // 0x24
        const char *mGroupName;  // 0x28
        float mActorOffset;      // 0x30
        int mPlayerIndex;        // 0x34
        int mIsUseSub;           // 0x38
        bool mIsHideIfNotVis;    // 0x3C
    };

    class BalloonMessage : public LayoutActor {
    public:
        BalloonMessage(const al::LiveActor*, const al::LayoutInitInfo&,
                       const al::BalloonMessageInitParam&, bool isUseDistance);
        
        void appear(void) override;
        void control(void) override;
        void updateTrans(void);
        void hidePushA(void);
        void appearWithPushA(void);
        void showPushA(void);
        void update(void);
        void end(void);
        void setText(char const*);
        void setTextW(char16_t const*);
        
        bool isEnableAppear(void) const;
        bool isWait(void) const;
        bool isVoicePlayerPlaying(void) const;
        bool isShowPushA(void) const;
        bool isEnableEnd(void) const;
        bool isNearPlayerActor(float) const;
        
        void exeAppear(void);
        void exeWait(void);
        void exeEnd(void);
        void exeHide(void);

        const LiveActor *mTargetActor;                       // 0x130
        const char *mPaneName;                               // 0x138
        float mMinDist;                                      // 0x140
        float mMaxDist;                                      // 0x144
        sead::Vector3f mTargetOffset = sead::Vector3f::zero; // 0x148
        int mPlayerIndex;                                    // 0x154
        int mIsUseSub;                                       // 0x158
        bool mIsUseDistance;                                 // 0x15C
        bool mIsHideIfNotVis;                                // 0x15D
        bool mIsUseVoice;                                    // 0x15E
        TalkMessageVoicePlayer* mTalkVoicePlayer = nullptr;  // 0x160
        sead::FixedSafeString<0x40> mTalkMsgSe;              // 0x168
    };

    BalloonMessage *createBalloonMessage(al::LiveActor const*,al::ActorInitInfo const&);
    BalloonMessage *createBalloonMessage(al::LiveActor const*,al::ActorInitInfo const&, char const*);
    BalloonMessage *createBalloonMessage(al::LiveActor const*,al::ActorInitInfo const&,al::BalloonMessageInitParam const&);
    BalloonMessage *createBalloonMessageNoAutoUpdate(al::LiveActor const*,al::ActorInitInfo const&,al::BalloonMessageInitParam const&);
}