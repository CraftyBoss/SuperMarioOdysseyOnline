/**
 * @file Pane.h
 * @brief Base UI panel.
 */

#pragma once

#include "types.h"
#include "sead/runtime.h"

namespace nn
{
    namespace ui2d
    {
        class AnimTransform;
        class Layout;

        class Pane
        {
        public:
            Pane();
            Pane(nn::ui2d::Pane const &);

            virtual ~Pane();

            virtual sead::RuntimeTypeInfo::Interface* GetRuntimeTypeInfo() const;
            virtual s32 GetVertexColor(s32);
            virtual u8 GetColorElement(s32);
            virtual void SetColorElement(u32, u8);
            virtual u8 GetVertexColorElement(s32);
            virtual void SetVertexColorElement(u32, u8);
            virtual u32 GetMaterialCount() const;
            virtual u64* GetMaterial(s32) const;

            virtual void BindAnimation(nn::ui2d::AnimTransform *, bool, bool);
            virtual void UnbindAnimation(nn::ui2d::AnimTransform *, bool);

            void Initialize();
            void SetName(char const *);
            void SetUserData(char const *);
            void AppendChild(nn::ui2d::Pane *);
            void PrependChild(nn::ui2d::Pane *);
            void InsertChild(nn::ui2d::Pane *, nn::ui2d::Pane *);
            void RemoveChild(nn::ui2d::Pane *);
            void GetVertexPos() const;

            nn::ui2d::Pane* mParent; // _8
            u64 _10;
            u64 _18;
            u64 _20;
            u64 _28;
            u32 mPositionX; // _30
            u32 mPositionY; // _34
            u32 mPositionZ; // _38
            u32 mRotationX; // _3C
            u32 mRotationY; // _40
            u32 mRotationZ; // _44
            u32 mScaleX; // _48
            u32 mScaleY; // _4C
            u32 mSizeX; // _50
            u32 mSizeY; // _54
            u8 mFlags; // _58 (pane + 0x8)
            u8 mAlpha; // _59
            u8 mAlphaInfluence; // _5A
            u8 mOriginFlags; // _5B
            u32 _5C;
            u64 _60;
            u64 _68;
            u128 _70;
            u128 _80;
            u128 _90;
            u64 _A0;
            u64 _A8;
            void* mAnimExtUserData; // _B0
            char[0x18] mPanelName; // _B8
            u8 _D0;
            char [8] mUserData; // _D1
            u8 _D9;
            u16 _DA;
            u32 _DC;
        };
    };
};