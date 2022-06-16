#pragma once

namespace al
{
    class ExecutorActorExecuteBase;

    class ActorExecuteInfo
    {
    public:
        void addUpdater(al::ExecutorActorExecuteBase *);
    };
};