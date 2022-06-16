#pragma once

namespace al
{
    
    class FunctorBase 
    {
        public:
            virtual void operator()(void) const {return;};
            virtual FunctorBase *clone(void) const {return {0};};
            virtual ~FunctorBase() {return;};
    };
} // namespace al
