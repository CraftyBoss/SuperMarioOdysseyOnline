/**
 * @file Preprocessor.h
 * @brief Defines a preprocessor for a collection of clauses and macros in a shader program.
 */

#pragma once

#include "sead/heap.h"
#include "sead/string.h"

namespace agl
{
    namespace shtxt
    {
        class Clause;
        class DefineLinker;
        class MacroDeployInfo;
        class MacroReplaceInfo;

        class Preprocessor
        {
        public:
            Preprocessor(sead::Heap *, sead::Heap *);
            ~Preprocessor();

            void finalize();
            void initialize(char const *);
            void removeClause(agl::shtxt::Clause *) const;
            void removeClause(agl::shtxt::Clause *, agl::shtxt::Clause *, bool) const;
            void removeClauseAll();
            void removeDefineLinkerAll();
            void setReplacedMacro(char const **, char const **, u32);
            void setDeployMacro(char const**, u32);
            void appendMacro(agl::shtxt::DefineLinker const *);
            bool preprocess(u32, u64, u64);
            void removeComment();
            void forceLF();
            void reduceSpace();
            void reduceLF();
            void format(bool);
            bool construct(sead::BufferedSafeStringBase<char> *dest) const;
            u64 calcConstructLength() const;
            

            u64 _0;
            u64 _8; // some sort of size
            u64 _10;
            sead::ExpHeap* _18;
            u64 _20;
            agl::shtxt::Clause* _28;
            agl::shtxt::DefineLinker* _30;
            char* mRefName; // _38
            agl::shtxt::MacroReplaceInfo* _40;
            u32 _48; // related to replace info
            u32 _4C;
            agl::shtxt::MacroDeployInfo* _50;
            u32 _58; // related to deploy info
            u32 _5C;
            agl::shtxt::DefineLinker* _60;
            u64 _68;
        };
    };
};