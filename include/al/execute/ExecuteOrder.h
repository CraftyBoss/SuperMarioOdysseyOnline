#pragma once

namespace al {
    struct ExecuteOrder
    {
        const char *mListName;
        const char *mExecuteGroup;
        int mListMaxSize;
        const char *mGroupType;
    };
}