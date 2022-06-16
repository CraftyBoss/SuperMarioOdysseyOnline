#pragma once

#include "al/layout/LayoutActor.h"
class MapMini : public al::LayoutActor {
public:
    MapMini(al::LayoutInitInfo const&,al::PlayerHolder const*);
    void appearSlideIn(void);
    void end(void);
    void calcNearHintTrans(void);
    
    bool isEnd(void) const;

    void exeAppear(void);
    void exeWait(void);
    void exeEnd(void);
};