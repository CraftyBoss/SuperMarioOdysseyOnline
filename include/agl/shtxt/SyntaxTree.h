/**
 * @file SyntaxTree.h
 * @brief Defines a syntax tree for shader compilation.
 */

#pragma once

#include "sead/delegate.h"
#include "types.h"

namespace agl
{
    namespace shtxt
    {
        class Clause;

        class SyntaxTree
        {
        public:
            SyntaxTree(agl::shtxt::Clause *);
            ~SyntaxTree();

            void removeClauseRecursive(sead::AnyDelegate1Const<agl::shtxt::Clause *> const *);
            f64 checkAndGetValue();
            void checkAndEvaluate(agl::shtxt::SyntaxTree const *) const;
            f64 evaluate();
            void constructRecursive(sead::Heap *,sead::Heap *);
            u64* construct(sead::Heap *, sead::Heap *) const;

            agl::shtxt::SyntaxTree* _0;
            agl::shtxt::SyntaxTree* _8;
            agl::shtxt::SyntaxTree* _10;
            u64 _18;
            agl::shtxt::Clause* _20;
            u64 _28;
            u32 _30;
        };
    };
};