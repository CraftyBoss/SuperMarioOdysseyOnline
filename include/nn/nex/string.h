/**
 * @file string.h
 * @brief NEX String Implementation.
 */

#pragma once

#include "RootObject.h"

namespace nn
{
    namespace nex
    {
        class String : public nn::nex::RootObject 
        { 
        public:
            bool operator<(nn::nex::String const &);

            void Truncate(u64) const;
            u64 GetLength() const;
            void Reserve(u64);
            void SetBufferChar(char *);
            void SetStringToPreReservedBuffer(char const *);
            s32 GetWideCharLength() const;
            void CopyString(char *, u64) const;
            void CreateCopy(wchar_t **) const;
            void ReleaseCopy(wchar_t *);
            void ToUpper();
            void ToLower();
            void DeleteContent();

            template<typename T>
            void Assign(T const *);
        };
    };
};