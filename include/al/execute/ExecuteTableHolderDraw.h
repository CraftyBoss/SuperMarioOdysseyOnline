#pragma once

#include <cstring>
#include <string_view>
#include "ExecuteOrder.h"
#include "al/async/FunctorBase.h"
#include "al/execute/ExecuteTable.h"
#include "al/execute/ExecutorListBase.h"
#include "al/execute/IUseExecutor.h"

#include "container/seadPtrArray.h"
#include "types.h"

namespace al {
    struct ExecuteSystemInitInfo;
    struct ExecutorListActorModelDrawBase;
    struct ExecutorListActorDraw;
    struct ExecutorListLayoutDrawBase;
    struct ExecutorListIUseExecutorDraw;
    struct ExecutorListFunctor;
    struct ExecutorListBase;
    struct LiveActor;
    struct LayoutActor;
}

namespace al {
class ExecuteTableHolderDraw {
    public:
        ExecuteTableHolderDraw();
        virtual ~ExecuteTableHolderDraw();
        void init(char const*, al::ExecuteSystemInitInfo const&, al::ExecuteOrder const*, int);
        void registerExecutorListActorModel(al::ExecutorListActorModelDrawBase*);
        void registerExecutorListActor(al::ExecutorListActorDraw*);
        void registerExecutorListLayout(al::ExecutorListLayoutDrawBase*);
        void registerExecutorListUser(al::ExecutorListIUseExecutorDraw*);
        void registerExecutorListFunctor(al::ExecutorListFunctor*);
        void registerExecutorListAll(al::ExecutorListBase*);
        void tryRegisterActor(al::LiveActor*, char const*);
        void tryRegisterActorModel(al::LiveActor*, char const*);
        void tryRegisterLayout(al::LayoutActor*, char const*);
        void tryRegisterUser(al::IUseExecutor*, char const*);
        void tryRegisterFunctor(al::FunctorBase const&, char const*);
        void createExecutorListTable();
        void execute() const;
        void executeList(char const*) const;
        bool isActive() const;

        const char* mName;

        sead::PtrArray<al::ExecutorListBase> mActiveExecutors;
        sead::PtrArray<al::ExecutorListBase> mExecutorsAll;
        sead::PtrArray<al::ExecutorListActorDraw> mExecutorsActor;
        sead::PtrArray<al::ExecutorListActorModelDrawBase> mExecutorsActorModel;
        sead::PtrArray<al::ExecutorListLayoutDrawBase> mExecutorsLayout;
        sead::PtrArray<al::ExecutorListIUseExecutorDraw> mExecutorsUser;
        sead::PtrArray<al::ExecutorListFunctor> mExecutorsFunctor;

   };
}

extern "C" al::ExecuteTable gameDrawTable[]; // pointer to original draw table found in the exefs

extern const al::ExecuteTable drawTable[];

extern int drawTableSize;