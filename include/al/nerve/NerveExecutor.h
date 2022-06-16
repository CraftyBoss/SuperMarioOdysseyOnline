#pragma once

#include "Nerve.h"
#include "NerveKeeper.h"

namespace al
{
    class NerveExecutor : public IUseNerve
    {
    public:
        NerveExecutor(const char *);

        virtual NerveKeeper* getNerveKeeper() const;
        virtual ~NerveExecutor();

        void initNerve(const al::Nerve *, int stateCount);
        void updateNerve();

        al::NerveKeeper* mKeeper; // _8
    };
};