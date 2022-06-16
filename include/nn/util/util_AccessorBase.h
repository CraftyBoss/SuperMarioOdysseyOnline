#pragma once

namespace nn
{
    namespace util
    {
        template<typename T>
        class AccessorBase : protected T
        {
        protected:
            AccessorBase();

        public:
            typedef T value_type;
        };
    };
};