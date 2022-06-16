#pragma once

#include "FunctorBase.h"
#include "sead/basis/seadNew.h"
#include "types.h"
#include "nn.h"

namespace sead
{
    namespace system
    {
        void DeleteImpl(void* ptr);
    }  // namespace system
}  // namespace sead

namespace al
{
    template <class T, class F>
    class FunctorV0M : public al::FunctorBase {
        
    public:
        inline FunctorV0M(T objPointer, F functPointer) : mFunctor(functPointer), mObjPointer(objPointer) { };

        void operator()(void) const override {
            (mObjPointer->*mFunctor)();
        };

        FunctorV0M<T,F> *clone(void) const override {
            return new FunctorV0M<T,F>(mObjPointer, mFunctor);
        };
        
        ~FunctorV0M() override {
            sead::system::DeleteImpl(this);
        };

    protected:
        // 0x0 = vtable
        T mObjPointer; // 0x8 = object pointer
        F mFunctor; // 0x10 = member function pointer
    };
} // namespace al
