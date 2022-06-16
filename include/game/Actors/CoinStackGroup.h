#pragma once

#include "al/LiveActor/LiveActor.h"

struct CoinStack; // stub class 

class CoinStackGroup : public al::LiveActor 
{
    public:
        void setStackAsCollected(CoinStack *stack);
        void generateCoinStackGroup(al::ActorInitInfo const &, int count);
};