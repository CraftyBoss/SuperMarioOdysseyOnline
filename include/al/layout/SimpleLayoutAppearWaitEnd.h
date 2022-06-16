#pragma once

#include "al/layout/LayoutActor.h"
namespace al {
class SimpleLayoutAppearWaitEnd : public al::LayoutActor {
public:
    SimpleLayoutAppearWaitEnd(char const*, char const*, al::LayoutInitInfo const&, char const*,
                              bool);
    
    SimpleLayoutAppearWaitEnd(al::LayoutActor*, char const*, char const*, al::LayoutInitInfo const&,
                              char const*);
    
    void appear(void);
    void end(void);
    void startWait(void);
    
    void exeAppear(void);
    void exeWait(void);
    void exeEnd(void);
    bool isWait(void) const;
    bool isAppearOrWait(void) const;

};
}