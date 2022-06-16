/**
 * @file DisplayList.h
 * @brief Defines a display list for the GPU.
 */

#pragma once

#include "types.h"
#include "agl/gpu.h"
#include "sead/heap/seadHeap.h"

namespace agl
{
    class DisplayList
    {
    public:
        DisplayList();

        virtual ~DisplayList();

        void setControlMemeory(void *, s32);
        void clear();
        void setBuffer(agl::GPUMemAddr<u8>, u64);
        void setValidSize(u64 size);
        void copyTo(agl::DisplayList *) const;
        void beginDisplayList();
        void endDisplayList();
        bool beginDisplayListBuffer(agl::GPUMemAddr<u8>, u64, bool);
        void endDisplayListBuffer(sead::Heap *);
        void adjustValueSize();
        void invalidateCPUCache() const;
        void dump() const;
        bool suspend(void **);
        void resume(void *, u64);
        u64 calcRemainingSize();

        u64 _8;
        u64 _10;
        u64 _18;
        u32 mUsedSize; // _20
        u32 _24;
        u32 mSize; // _28
        u32 _2C;
        u64 _30;
        u64 _38;
        u8 _40[0x248-0x40]; // todo; what is here?
        u32 _248; // init'd to 0x200
        u32 _24C;
        u64 _250;
        char* mDisplayName; // _258
    };
};