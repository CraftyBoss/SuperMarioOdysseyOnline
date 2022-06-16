#pragma once

#include "Nerve.h"
#include "NerveStateBase.h"

namespace al
{
    struct State
    {
        al::NerveStateBase* mStateBase; // _0
        const al::Nerve* mNerve; // _8
        const char* mName; // _10
    };

    class NerveStateCtrl
    {
    public:
        NerveStateCtrl(int);

        void addState(al::NerveStateBase *, const al::Nerve *, const char *);
        bool updateCurrentState();
        void startState(const al::Nerve *);
        void update();

        State* findStateInfo(const al::Nerve *);
        bool isCurrentStateEnd() const;
        void tryEndCurrentState();

        int _0;
        int mStateCount; // _4
        State* mStates; // _8
        State* mCurrentState; // _10
    };
};