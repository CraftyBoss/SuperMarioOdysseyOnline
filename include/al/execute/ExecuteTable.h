#pragma once

#include "ExecuteOrder.h"

namespace al {
    struct ExecuteTable
    {
        const char *mName;
        const al::ExecuteOrder* mExecuteOrders;
        int mExecuteOrderCount;
    };
}