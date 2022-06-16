/**
 * @file FileIOMgr.h
 * @brief Defines classes that handle shader management I/O.
 */

#pragma once

#include "sead/heap.h"
#include "sead/hostio.h"
#include "sead/string.h"
#include "sead/xml.h"

namespace agl
{
    namespace detail
    {
        class FileIOMgr : public sead::hostio::Node
        {
        public:

            class SingletonDisposer
            {
            public:
                ~SingletonDisposer();
            };

            class CreateArg
            {   
            public:
                CreateArg();

                u32 mArg; // _0
            };

            class DialogArg
            {
            public:
                DialogArg();

                u64* _0;
                u64* _8;
                u64 _10;
                u64 _18;
                u64 _20;
                char* mMsg; // _28
                u64* _30;
                u64* _38;
                u64 _40;
                u32 _48; // set to 0x20
                u8 _4C;
                u8 _4D;
                u8 _4E;
                u8 _4F;
                u32 _50;
            };

            FileIOMgr();

            void initialize(agl::detail::FileIOMgr::CreateArg const &, sead::Heap *);
            void setCheckoutCommandPath(sead::SafeStringBase<char> const &);
            void save(sead::XmlDocument const &, agl::detail::FileIOMgr::DialogArg const &, u32);
            void showDialog(sead::hostio::FileInfo *, sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &) const;
            void checkout_(sead::SafeStringBase<char> const &) const;
            void showErrorDialog_(sead::SafeStringBase<char> const &) const;
            void save(void const*, u32, agl::detail::FileIOMgr::DialogArg const &);
            s32 load(agl::detail::FileIOMgr::DialogArg const &);
            void close(s32);
            void genMessage(sead::hostio::Context *);
            void listenPropertyEvent(sead::hostio::PropertyEvent const *);

            static agl::detail::FileIOMgr* createInstance(sead::Heap *);
            static void deleteInstance();

            u64* _28; // sead::NinHostIOFileDevice *
        };
    };
};