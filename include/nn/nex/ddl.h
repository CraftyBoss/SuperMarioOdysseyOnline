/**
 * @file ddl.h
 * @brief DDL Declaration Implementation.
 */

#pragma once

#include "RootObject.h"
#include "types.h"

namespace nn
{
    namespace nex
    {
        class DDLDeclarations : public nn::nex::RootObject
        {
        public:
            DDLDeclarations(bool);

            virtual ~DDLDeclarations();

            virtual void Init() = 0;

            void RegisterIfRequired();
            void Unregister();
            static void UnregisterAll();
            void LoadAll();
            void Load();
            void UnloadAll();
            void Unload();
            void ResetDOClassIDs();

            u32 mNumDecsLoaded; // _8
            u8 _C;
            u8 _D; // padding
            u8 _E; // ^^
            u8 _F; // ^^
            u64 _10;
            bool _18;

            static nn::nex::DDLDeclarations* s_pFirstDDLDecl;
        };
    };
};