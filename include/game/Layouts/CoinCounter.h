#pragma once

/* 
* VTable Loc: 1CC3170
*/

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

class CoinCounter : public al::LayoutActor {
    public:
        CoinCounter(char const*,al::LayoutInitInfo const&,bool);
        void kill(void);
        bool isWait(void) const;
        bool tryStart(void);
        void updateCountImmidiate(void);
        bool tryEnd(void);
        void startCountAnim(int);
        void getCountTotalFromData(void);
        void exeAppear(void);
        void exeWait(void);
        bool tryUpdateCount(void);
        void exeEnd(void);
        void exeAdd(void);
        void exeSub(void);
        void exeCountAnimAdd(void);
        void exeCountAnimSub(void);
        void getCountFromData(void);
};