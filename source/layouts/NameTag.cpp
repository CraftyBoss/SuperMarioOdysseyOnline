#include "layouts/NameTag.h"

#include "actors/PuppetActor.h"
#include "al/layout/LayoutActor.h"
#include "al/util.hpp"
#include "al/util/NerveUtil.h"
#include "logger.hpp"
#include "sead/math/seadVector.h"

NameTag::NameTag(PuppetActor* pupActor, const al::LayoutInitInfo& initInfo, float startDist,
                 float endDist, const char *playerName)
    : al::LayoutActor("PNameTag"), mPuppet(pupActor), mStartDist(startDist), mEndDist(endDist) {

    al::initLayoutActor(this, initInfo, "BalloonSpeak", 0);

    mPaneName = "TxtMessage";

    al::setPaneStringFormat(this, mPaneName, playerName);

    initNerve(&nrvNameTagWait, 0);

    end();
}

void NameTag::appear() {
    if (!al::isNerve(this, &nrvNameTagEnd) && !al::isNerve(this, &nrvNameTagHide) && mIsAlive) {
        LayoutActor::appear();
        al::startFreezeActionEnd(this, "End", 0);
        al::setNerve(this, &nrvNameTagHide);
        return;
    }

    if (!isNearPlayerActor(mStartDist)) {
        LayoutActor::appear();
        al::startFreezeActionEnd(this, "End", 0);
        al::setNerve(this, &nrvNameTagHide);
        return;
    }

    setText(mPuppet->getName());
    
    al::startAction(this, "Appear", 0);
    LayoutActor::appear();
    al::setActionFrameRate(this, 1.0, 0);
    al::setNerve(this, &nrvNameTagAppear);
}

void NameTag::control() {

    update();

    al::LiveActor *puppetModel = mPuppet->getCurrentModel();

    if (!al::isNerve(this, &nrvNameTagEnd) &&
       !al::isNerve(this, &nrvNameTagHide) &&
       (al::isClipped(puppetModel) || al::isDead(puppetModel))) {
       al::setNerve(this, &nrvNameTagEnd);
    } else {
        updateTrans();
    }
}

void NameTag::updateTrans() {
    sead::Vector2f newTrans = sead::Vector2f::zero;

    sead::Vector3f targetOffset(0, 130, 0);

    al::LiveActor *puppetModel = mPuppet->getCurrentModel();

    al::calcLayoutPosFromWorldPos(&newTrans, puppetModel, al::getTrans(puppetModel) + targetOffset);

    al::setLocalTrans(this, newTrans);

    mNormalizedDist =
        1 - al::normalize(al::calcDistance(puppetModel, al::getPlayerActor(puppetModel, 0)), 200.0f,
                          mEndDist);

    al::setLocalScale(this, mNormalizedDist);
    
}

void NameTag::update() {

    if (al::isNerve(this, &nrvNameTagEnd) || al::isNerve(this, &nrvNameTagHide) || !mIsAlive) {
        if (isNearPlayerActor(mStartDist)) {
            appear();
        }
    }

    if (!al::isNerve(this, &nrvNameTagEnd) && !al::isNerve(this, &nrvNameTagHide) &&
        mIsAlive) {
        if (!isNearPlayerActor(mEndDist)) {
            al::setNerve(this, &nrvNameTagEnd);
        }
    }
}

void NameTag::end() {
    if (!al::isNerve(this, &nrvNameTagEnd) && !al::isNerve(this, &nrvNameTagHide)) {
        al::setNerve(this, &nrvNameTagEnd);
    }
}

void NameTag::setText(const char* text) {
    al::setPaneStringFormat(this, mPaneName, text);
}

bool NameTag::isNearPlayerActor(float dist) const {
    return al::isNearPlayer(mPuppet->getCurrentModel(), dist);
}

bool NameTag::isVisible() const {
    return isNearPlayerActor(mStartDist);
}

const char* NameTag::getCurrentState() {
    if (al::isNerve(this, &nrvNameTagAppear)) {
        return "Appear";
    }
    if (al::isNerve(this, &nrvNameTagWait)) {
        return "Wait";
    }
    if (al::isNerve(this, &nrvNameTagEnd)) {
        return "End";
    }
    if (al::isNerve(this, &nrvNameTagHide)) {
        return "Hide";
    }
    return "Unknown";
}

void NameTag::exeAppear(void) {
    if (al::isActionEnd(this, 0))
        al::setNerve(this, &nrvNameTagWait);
}
void NameTag::exeWait(void) {
    if (al::isFirstStep(this))
        al::startAction(this, "Wait", 0);
}
void NameTag::exeEnd(void) {
    if (al::isFirstStep(this))
        al::startAction(this, "End", 0);

    if (al::isActionEnd(this, 0))
        al::setNerve(this, &nrvNameTagHide);
}

void NameTag::exeHide(void) { }


namespace {
NERVE_IMPL(NameTag, Appear)
NERVE_IMPL(NameTag, Wait)
NERVE_IMPL(NameTag, End)
NERVE_IMPL(NameTag, Hide)
}