#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/layout/LayoutActor.h"
#include "al/nerve/NerveExecutor.h"
#include "al/layout/KeyRepeatCtrl.h"
#include "sead/container/seadPtrArray.h"

#include "types.h"

class MenuSelectParts : public al::NerveExecutor {
    public:
        MenuSelectParts(char const*,al::LayoutActor *,al::LiveActor *,al::LayoutInitInfo const&,int);
        void update(void);
        void appear(int);
        void startActionPartsIllustSelectIndex(void);
        void appearWait(void);
        void setSelectMessage(int,char16_t const*);
        bool isDecideContinue(void) const;
        bool isDecideEnd(void) const;
        bool isSelectContinue(void) const;
        bool isDecideSetting(void) const;
        bool isSelectSetting(void) const;
        bool isDecideSave(void) const;
        bool isSelectSave(void) const;
        bool isDecideSeparatePlay(void) const;
        bool isSelectSeparatePlay(void) const;
        bool isDecideHelp(void) const;
        bool isSelectHelp(void) const;
        bool isDecideNewGame(void) const;
        bool isSelectNewGame(void) const;
        void calcPartsIndex(int);
        void exeHide(void);
        void exeAppear(void);
        void startActionMarioSelectIndex(void);
        void exeSelect(void);
        void startActionMario(al::LiveActor *,char const*);
        void exeDecideParts(void);
        bool isInvalidSelect(void) const;
        void exeDecideInterval(void);
        void exeDecideEnd(void);
        ~MenuSelectParts();

        // void *vtable;
        // void *unk1; // 0x08
        al::LayoutActor *mRootLayout;                 // 0x10
        int mMaxSelectParts;                          // 0x18
        int mCursorItemIdx;                           // 0x1C
        sead::PtrArray<al::LayoutActor> mSelectParts; // 0x20-0x28
        al::LayoutActor *mCursorActor;                // 0x30
        void *unk3;                                   // 0x38
        al::LiveActor *mMarioHigh;                    // 0x40
        al::LiveActor *mCapEyes;                      // 0x48
        al::KeyRepeatCtrl *mKeyRepeatCtrl;            // 0x50
        bool isMenuMain;                              // 0x58
};

// static_assert(sizeof(MenuSelectParts) == 0x60);