#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

namespace al {

class WindowConfirmWait : public al::LayoutActor {
    public:
        WindowConfirmWait(char const*, char const*, al::LayoutInitInfo const&);
        
        void setTxtMessage(char16_t const*);
        void setTxtMessageConfirm(char16_t const*);

        void appear(void);
        bool tryEnd(void);
        bool tryEndForce(void);
        void playLoop(void);
        void endLoop(void);
        void tryPageIn(void);
        void tryPageOut(void);
        void showPaneConfirm(void);
        void tryConfirmDecide(void);
        void updateHardKey(void);

        void exeHide(void);
        void exeAppear(void);
        void exeKeepWait(void);
        void exeWait(void);
        void exeWaitEnd(void);
        void exeEnd(void);
        void exePageIn(void);
        void exePageOut(void);
        void exePageOutEnd(void);
        void exeConfirmDecide(void);

        al::LayoutActor *mPartsHardKey;

    };
}  // namespace al

namespace {
    NERVE_HEADER(WindowConfirmWait, Hide)
    NERVE_HEADER(WindowConfirmWait, Appear)
    NERVE_HEADER(WindowConfirmWait, KeepWait)
    NERVE_HEADER(WindowConfirmWait, Wait)
    NERVE_HEADER(WindowConfirmWait, WaitEnd)
    NERVE_HEADER(WindowConfirmWait, End)
    NERVE_HEADER(WindowConfirmWait, PageIn)
    NERVE_HEADER(WindowConfirmWait, PageOut)
    NERVE_HEADER(WindowConfirmWait, PageOutEnd)
    NERVE_HEADER(WindowConfirmWait, ConfirmDecide)
}  // namespace

static_assert(sizeof(al::WindowConfirmWait) == 0x138, "Size of WindowConfirmWait");