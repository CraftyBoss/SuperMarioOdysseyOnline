#pragma once

#include "NerveExecutor.h"

namespace al
{
    class NerveStateBase : public NerveExecutor
    {
    public:
        NerveStateBase(const char *);

        virtual ~NerveStateBase();
        virtual void init();
        virtual void appear();
        virtual void kill();
        virtual bool update();
        virtual void control();

        bool mIsDead; // _10
    };
};