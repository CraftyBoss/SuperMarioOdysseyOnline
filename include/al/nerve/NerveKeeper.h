#pragma once

#include "Nerve.h"

namespace al
{
    class NerveStateCtrl;

    class NerveKeeper
    {
    public:
        NerveKeeper(al::IUseNerve *, const al::Nerve *, int);

        void update();

        void tryChangeNerve();
        void setNerve(const al::Nerve *);
        const al::Nerve* getCurrentNerve() const;

        al::IUseNerve* mParent; // _0
        const al::Nerve* _8;
        const al::Nerve* mNerve; // _10
        int mStep; // _18
        int _1C;
        al::NerveStateCtrl* mStateCtrl; // _20
        unsigned long _28;
    };
};