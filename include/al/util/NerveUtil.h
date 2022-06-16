#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveStateBase.h"

#define NERVE_HEADER(Class, Action) \
    class Class##Nrv##Action : public al::Nerve { \
    public: \
        void execute(al::NerveKeeper*) override; \
    }; \
    Class##Nrv##Action nrv##Class##Action;

#define NERVE_IMPL_(Class, Action, ActionFunc)                                                     \
    void Class##Nrv##Action::execute(al::NerveKeeper* keeper) {                                    \
        static_cast<Class*>(keeper->mParent)->exe##ActionFunc();                                   \
    }
#define NERVE_IMPL(Class, Action) NERVE_IMPL_(Class, Action, Action)

// Fruity Nerve Implmentation
#define NERVE_DEF(CLASS, ACTION)                                                                   \
    struct CLASS##Nrv##ACTION : public al::Nerve {                                                 \
        inline void execute(al::NerveKeeper* keeper) override                                      \
        {                                                                                          \
            static_cast<CLASS*>(keeper->mParent)->exe##ACTION();                                   \
        };                                                                                         \
        const CLASS##Nrv##ACTION nrv##CLASS##ACTION;                                               \
    }

namespace al
{
    void setNerve(al::IUseNerve *, const al::Nerve *);
    void setNerveAtStep(al::IUseNerve *, const al::Nerve *, int);
    bool isStep(const al::IUseNerve *, int);
    void setNerveAtGreaterEqualStep(al::IUseNerve *, const al::Nerve *, int);
    bool isGreaterEqualStep(const al::IUseNerve *, int);
    bool isNerve(const al::IUseNerve *, const al::Nerve *);
    int getNerveStep(const al::IUseNerve *);
    const al::Nerve* getCurrentNerve(const al::IUseNerve *);
    bool isFirstStep(const al::IUseNerve *);
    bool isLessStep(const al::IUseNerve *, int);
    bool isGreaterStep(const al::IUseNerve *, int);
    bool isInRangeStep(const al::IUseNerve *, int, int);
    bool isIntervalStep(const al::IUseNerve *, int, int);
    bool isIntervalOnOffStep(const al::IUseNerve *, int, int);
    bool isNewNerve(const al::IUseNerve *);
    int calcNerveInterval(const al::IUseNerve *, int, int);
    float calcNerveRate(const al::IUseNerve *, int);
    float calcNerveRate(const al::IUseNerve *, int, int);
    float calcNerveEaseInRate(const al::IUseNerve *, int);
    float calcNerveEaseInRate(const al::IUseNerve *, int, int);

    void initNerveState(al::IUseNerve *, al::NerveStateBase *, const al::Nerve *, const char *);
    void initNerve(LiveActor *, const al::Nerve *, int);
    void addNerveState(al::IUseNerve *, al::NerveStateBase *, const al::Nerve *, const char *);
    bool updateNerveState(al::IUseNerve *);
    bool updateNerveStateAndNextNerve(al::IUseNerve *, const al::Nerve *);
    bool isStateEnd(const al::IUseNerve *);
};