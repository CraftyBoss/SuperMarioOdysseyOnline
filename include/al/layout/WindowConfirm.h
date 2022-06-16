#pragma once

#include "al/layout/LayoutActor.h"

namespace al {
class WindowConfirm : public al::LayoutActor {
public:
    
    WindowConfirm(al::LayoutInitInfo const&, char const*, char const*);
    
    void appear(void);
    void appearWithChoicingCancel(void);
    void exeAppear(void);
    void exeDecide(void);
    void exeDecideAfter(void);
    void exeEnd(void);
    void exeHide(void);
    void exeWait(void);
    void isEnableInput(void);
    void isNerveEnd(void);
    void setCancelIdx(int);
    void setCursorToPane(void);
    void setListNum(int);
    void setTxtList(int,char16_t const*);
    void setTxtMessage(char16_t const*);
    void tryCancel(void);
    void tryCancelWithoutEnd(void);
    void tryDecide(void);
    void tryDecideWithoutEnd(void);
    void tryDown(void);
    void tryEnd(void);
    void tryUp(void);

    char size[0x38];


};
}