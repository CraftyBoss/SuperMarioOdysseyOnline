#pragma once

#include "al/async/FunctorBase.h"

#include "IUseExecutor.h"
#include "ExecuteSystemInitInfo.h"
#include "ExecuteRequestKeeper.h"
#include "ExecuteTableHolderDraw.h"
#include "ExecuteTableHolderUpdate.h"
#include "container/seadPtrArray.h"
#include "container/seadBuffer.h"

namespace al
{

    class LiveActor;
    class LayoutActor;
    
    class ExecuteDirector {
    public:
        ExecuteDirector(int);
        virtual ~ExecuteDirector();
        void init(al::ExecuteSystemInitInfo const&);
        void registerActorUpdate(al::LiveActor*, char const*);
        void registerActorDraw(al::LiveActor*, char const*);
        void registerActorModelDraw(al::LiveActor*, char const*);
        void registerLayoutUpdate(al::LayoutActor*, char const*);
        void registerLayoutDraw(al::LayoutActor*, char const*);
        void registerUser(al::IUseExecutor*, char const*);
        void registerFunctor(al::FunctorBase const&, char const*);
        void registerFunctorDraw(al::FunctorBase const&, char const*);
        void createExecutorListTable();
        void execute(char const*) const;
        void executeList(char const*, char const*) const;
        void draw(char const*) const;
        void drawList(char const*, char const*) const;
        void isActiveDraw(char const*) const;

        int mRequestMax;  // 0x8

        int mUpdateTableCount;
        al::ExecuteTableHolderUpdate **mUpdateTables;
        int mDrawTableCount;
        al::ExecuteTableHolderDraw **mDrawTables;

        al::ExecuteRequestKeeper *mRequestKeeper;
    };
} // namespace al
