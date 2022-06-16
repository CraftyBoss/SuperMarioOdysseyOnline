#pragma once

#include "nn/util/util_AccessorBase.h"

namespace nn
{
    namespace g3d
    {
        struct ResFileData
        {
            // empty for now
        };

        class ResFile : public nn::util::AccessorBase<ResFileData>
        {
        public:

            static ResFile* ResCast(void *);

            void ReleaseTexture();
            void Reset();
        };
    };
};