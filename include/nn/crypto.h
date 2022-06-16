/**
 * @file crypto.h
 * @brief Crypto service implementation.
 */

#pragma once

#include "types.h"

namespace nn
{
    namespace crypto
    {
        class Sha256Context;

        void DecryptAes128Cbc(void *, u64, void const *, u64, void const *, u64, void const *, u64);
        void EncryptAes128Cbc(void *, u64, void const *, u64, void const *, u64, void const *, u64);
        void DecryptAes128Ccm(void *, u64, void *, u64, void const *, u64, void const *, u64, void const *, u64, void const *, u64, u64);

        namespace detail
        {
            class Md5Impl
            {
            public:
                void Initialize();
                void Update(void const *, u64 dataSize);
                void ProcessBlock();
                void GetHash(void *, u64 hashSize);
                void ProcessLastBlock();

                u32 _0;
                u32 _4;
                u32 _8;
                u32 _C;
                u8 _10[0x50-0x10];
                u64 _50;
                u32 _58;
            };

            class Sha1Impl
            {
            public:
                void Initialize();
                void Update(void const *, u64);
                void ProcessBlock(void const *);
                void GetHash(void *destHash, u64);
                void ProcessLastBlock();

                u64 _0;
                u64 _8;
                u32 _10;
                u128 _14;
                u128 _24;
                u128 _34;
                u32 _44;
                u64 _48;
                u64 _50;
                u64 _58;
                u64 _60;
            };

            class Sha256Impl
            {
            public:
                void Initialize();
                void Update(void const *, u64);
                void ProcessBlocks(u8 const *, u64);
                void GetHash(void *destHash, u64);
                void ProcessLastBlock();
                void InitializeWithContext(nn::crypto::Sha256Context const *);
                void GetContext(nn::crypto::Sha256Context *) const;

                u64 _0;
                u64 _8;
                u32 _10;
                u128 _14;
                u128 _24;
                u128 _34;
                u32 _44;
                u64 _48;
                u64 _50;
                u64 _58;
                u64 _60;
                u64 _68;
                u32 _70;
            };
        };
    };
};