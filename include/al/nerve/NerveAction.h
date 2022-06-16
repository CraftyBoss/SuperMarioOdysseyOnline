#pragma once

#include "Nerve.h"

namespace al
{
    class NerveAction : public al::Nerve
    {
    public:
        NerveAction();

        virtual const char* getActionName() const = 0;

        al::NerveAction* _8;
    };
};

namespace alNerveFunction
{
    class NerveActionCollector
    {
    public:
        NerveActionCollector();

        void addNerve(al::NerveAction *);

        int mActionCount; // _0
        int _4;
        al::NerveAction* _8;
        al::NerveAction* _10;

        static alNerveFunction::NerveActionCollector* sCurrentCollector;
    };
};