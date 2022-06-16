/**
 * @file DefineLinker.h
 * @brief Defines a linker for shader source compilation.
 */

#pragma once

#include "sead/heap.h"
#include "types.h"

namespace agl
{
    namespace shtxt
    {
        class Clause;

        class DefineLinker
        {
        public:
            DefineLinker();
            ~DefineLinker();

            void clear();
            bool set(sead::Heap *, agl::shtxt::Clause const *, agl::shtxt::Clause const *);
            bool setImpl(sead::Heap *, agl::shtxt::Clause const *, agl::shtxt::Clause const *, bool);
            void setDirect(agl::shtxt::Clause *, u32, bool);
            void updateHash();
            void replace(sead::Heap *, agl::shtxt::Clause const *, agl::shtxt::Clause const *, bool);
            agl::shtxt::DefineLinker* clone(sead::Heap *, sead::Heap *) const;
            agl::shtxt::DefineLinker* cloneAll(sead::Heap *, sead::Heap *) const;

            agl::shtxt::DefineLinker* _0; // seems to copy itself twice
            agl::shtxt::DefineLinker* _8;
            agl::shtxt::Clause* _10;
            agl::shtxt::Clause* _18; // hash clause?
            u64 _20;
            agl::shtxt::Clause* _28;
            u64 _30;
            u64 _38;
            s32 mHash; // _40
            s16 _44; // -1
            u16 _46; // 0x101
        };
    };
};