#pragma once

#include "al/layout/LayoutActor.h"
#include "al/util/NerveUtil.h"
#include "al/util/LayoutUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/MathUtil.h"

class PuppetActor;

class NameTag : public al::LayoutActor {
public:
    NameTag(PuppetActor*, const al::LayoutInitInfo&, float startDist, float endDist, const char *playerName);

    void appear(void) override;
    void control(void) override;
    void updateTrans(void);
    void update(void);
    void end(void);
    void setText(char const*);

    bool isNearPlayerActor(float) const;
    bool isVisible() const;

    const char *getCurrentState();
    
    void exeAppear(void);
    void exeWait(void);
    void exeEnd(void);
    void exeHide(void);

    PuppetActor *mPuppet;              // 0x130
    const char *mPaneName;             // 0x138
    float mStartDist;                  // 0x140
    float mEndDist;                    // 0x144
    float mNormalizedDist;             // 0x148

};

namespace {
NERVE_HEADER(NameTag, Appear)
NERVE_HEADER(NameTag, Wait)
NERVE_HEADER(NameTag, End)
NERVE_HEADER(NameTag, Hide)
}  // namespace