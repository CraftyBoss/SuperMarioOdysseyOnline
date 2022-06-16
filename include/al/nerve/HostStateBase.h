#pragma once

#include "NerveStateBase.h"

namespace al
{
    template <class T>
    class HostStateBase : public NerveStateBase {
        public:
            HostStateBase(const char* name, T *host) : NerveStateBase(name), mHost(host){};
            T *mHost;
    };
} // namespace al
