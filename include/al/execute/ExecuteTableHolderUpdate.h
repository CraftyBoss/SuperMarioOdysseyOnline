#pragma once

#include "ExecuteOrder.h"
#include "al/async/FunctorBase.h"
#include "al/execute/ExecuteTable.h"
#include "al/execute/ExecutorListBase.h"
#include "al/execute/IUseExecutor.h"
#include "ExecuteSystemInitInfo.h"

#include "container/seadPtrArray.h"
#include "types.h"

namespace al {
    struct ExecutorListActorExecuteBase;
    struct ExecutorListLayoutUpdate;
    struct ExecutorListIUseExecutorUpdate;
    struct ExecutorListFunctor;
    struct ExecutorListBase;
    struct LiveActor;
    struct LayoutActor;
}

namespace al {
class ExecuteTableHolderUpdate {
    public:
        ExecuteTableHolderUpdate();
        virtual ~ExecuteTableHolderUpdate();
        void init(char const*, al::ExecuteSystemInitInfo const&, al::ExecuteOrder const*, int);
        void registerExecutorListActor(al::ExecutorListActorExecuteBase*);
        void registerExecutorListLayout(al::ExecutorListLayoutUpdate*);
        void registerExecutorListUser(al::ExecutorListIUseExecutorUpdate*);
        void registerExecutorListFunctor(al::ExecutorListFunctor*);
        void registerExecutorListAll(al::ExecutorListBase*);
        void tryRegisterActor(al::LiveActor*, char const*);
        void tryRegisterLayout(al::LayoutActor*, char const*);
        void tryRegisterUser(al::IUseExecutor*, char const*);
        void tryRegisterFunctor(al::FunctorBase const&, char const*);
        void createExecutorListTable();
        void execute() const;
        void executeList(char const*) const;

        const char *mName;
        sead::PtrArray<al::ExecutorListBase> mActiveExecutors;
        sead::PtrArray<al::ExecutorListBase> mExecutorsAll;
        sead::PtrArray<al::ExecutorListActorExecuteBase> mExecutorsActor;
        sead::PtrArray<al::ExecutorListLayoutUpdate> mExecutorsLayout;
        sead::PtrArray<al::ExecutorListIUseExecutorUpdate> mExecutorsUser;
        sead::PtrArray<al::ExecutorListFunctor> mExecutorsFunctor;

   };
}  // namespace al

extern "C" al::ExecuteTable gameUpdateTable[]; // pointer to original update table found in the exefs

extern const al::ExecuteTable updateTable[];

extern int updateTableSize;

