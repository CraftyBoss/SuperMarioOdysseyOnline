/**
 * @file Lexer.h
 * @brief Defines a lexer for parsing shader clauses.
 */

#pragma once

#include "sead/heap.h"

namespace agl
{
    namespace shtxt
    {
        class Clause;

        class Lexer
        {
        public:
            Lexer();
            ~Lexer();

            void initialize(sead::Heap *, char const *, agl::shtxt::Clause *);
            void setupCurrentRange(u64 range);
            u32 findNumberBlock() const;
            agl::shtxt::Clause* createClause(u32) const;
            bool execute(bool);

            sead::Heap* _0;
            agl::shtxt::Clause* _8;
            char* mRefName; // _10
            u64 _18;
            u64 _20;
            u64 _28;
        };
    };
};