#pragma once

// #include "sead/heap/seadHeap.h"
#include "seadFontBase.h"
#include "types.h"

namespace sead {

    struct Heap;
    struct DrawContext;

    class DebugFontMgrNvn : public FontBase {
        public:
            DebugFontMgrNvn(void);

            static DebugFontMgrNvn *sInstance;

            void initialize(sead::Heap *, const char *, const char*, unsigned int);
            void initializeFromBinary(sead::Heap *, void *, unsigned long, void *, unsigned long, unsigned int);
            static sead::DebugFontMgrNvn *createInstance(sead::Heap *);
            void swapUniformBlockBuffer(void);
            void begin(sead::DrawContext *) const;
            void end(sead::DrawContext *) const;

            float getHeight(void) const {
                return 16.f;
            };
            float getWidth(void) const {
                return 8.f;
            };
            float getCharWidth(char16_t) const {
                return 8.f;
            };
            int getMaxDrawNum(void) const {
                return 0x80;
            };
            int getEncoding(void) const {
                return 2;
            };
            
    };

    class DebugFontMgrJis1Nvn : public FontBase {
        public:
            DebugFontMgrJis1Nvn(void);

            static DebugFontMgrJis1Nvn *sInstance;

            void initialize(sead::Heap *, const char *, const char *, const char *, unsigned int);
            void initializeFromBinary(sead::Heap *,void *, ulong,void *, ulong,void const*, uint);
            static sead::DebugFontMgrJis1Nvn *createInstance(sead::Heap *);
            void swapUniformBlockBuffer(void);
            void begin(sead::DrawContext *) const;
            void end(sead::DrawContext *) const;

            float getHeight(void) const {
                return 16.f;
            };
            float getWidth(void) const {
                return 8.f;
            };

            float getCharWidth(char16_t) const;

            int getMaxDrawNum(void) const {
                return 0x80;
            };
            int getEncoding(void) const {
                return 2;
            };
            
    };
}