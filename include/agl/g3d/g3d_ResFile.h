#pragma once

#include <nn/g3d.h>

namespace agl
{
    namespace g3d
    {
        class ResFile
        {
        public:
            static void BindTexture(nn::g3d::ResFile *, nn::g3d::ResFile *);
            static void Cleanup(nn::g3d::ResFile *);
        };
    };
};