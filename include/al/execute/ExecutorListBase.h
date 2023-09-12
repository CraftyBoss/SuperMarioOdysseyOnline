#pragma once

#include "types.h"

namespace al {
    class ExecutorListBase {
    public:
        ExecutorListBase(char const*);
        virtual ~ExecutorListBase();
        virtual void executeList() const;
        virtual bool isActive() const;

        const char *mName;
    };
}