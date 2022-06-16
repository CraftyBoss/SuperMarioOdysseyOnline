/**
 * @file ExpressionEvaluator.h
 * @brief Defines an evaluator for shader expressions.
 */

#pragma once

#include "sead/array.h"
#include "sead/delegate.h"
#include "sead/heap.h"

namespace agl
{
    namespace shtxt
    {
        class Clause;
        class SyntaxLeash;

        class ExpressionEvaluator
        {
        public:
            ExpressionEvaluator();
            ExpressionEvaluator(sead::Heap *, sead::Heap *, sead::AnyDelegate1Const<agl::shtxt::Clause *> const *);

            void initialize(sead::Heap *, sead::Heap *, sead::AnyDelegate1Const<agl::shtxt::Clause *> const *);
            u64 findSyntaxLeash(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause const *) const;
            u64* createBinaryOperatorSyntaxTree(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *);
            u64* createTernaryOperatorSyntaxTree(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *);
            u64* createTokenOperatorSyntaxTree(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *);
            void resolveOperatorTokenConnect(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorUnary(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorMathHigh(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorMathLow(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorShift(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorCompareHigh(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorCompareLow(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorBitOpAnd(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorBitOpXor(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorBitOpOr(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorLogicalAnd(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorLogicalOr(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorTernary(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperatorAssignment(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveOperator(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolveParenthesis(sead::ObjArray<agl::shtxt::SyntaxLeash> *, agl::shtxt::Clause *, agl::shtxt::Clause *);
            void resolve(agl::shtxt::Clause *, agl::shtxt::Clause *, bool);

            sead::Heap* _0;
            sead::Heap* _8;
            sead::AnyDelegate1Const<agl::shtxt::Clause *>* _10;
        };
    };
};