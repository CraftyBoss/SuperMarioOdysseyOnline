#pragma once

#include "al/layout/LayoutActor.h"

class SimpleLayoutMenu : public al::LayoutActor {
public:
    SimpleLayoutMenu(al::LayoutActor *,char const*,char const*,al::LayoutInitInfo const&,char const*);
    SimpleLayoutMenu(char const*,char const*,al::LayoutInitInfo const&,char const*,bool);
    
    void exeAppear(void);
    void exeEnd(void);
    void exeEndWait(void);
    void exeWait(void);
    void isAppearOrWait(void);
    void isEndWait(void);
    void isWait(void);
    void startAppear(char const*);
    void startEnd(char const*);

};
