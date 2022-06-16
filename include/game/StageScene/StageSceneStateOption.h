#pragma once

#include "al/message/MessageSystem.h"
#include "al/nerve/HostStateBase.h"
#include "al/message/IUseMessageSystem.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/scene/Scene.h"
#include "al/LiveActor/LiveActor.h"
#include "al/util/GraphicsUtil.h"
#include "al/util/NerveUtil.h"
#include "game/Input/InputSeparator.h"
#include "game/Layouts/SimpleLayoutMenu.h"

struct CommonVerticalList;

class FooterParts {
    public:
        bool tryChangeTextFade(const char16_t *);
};
class GameConfigData;

namespace al
{
    class SimpleLayoutAppearWaitEnd;
    class WindowConfirm;
    class WindowConfirmData;
    class KeyRepeatCtrl;
} // namespace al

class StageSceneStateOption : public al::HostStateBase<al::Scene>, public al::IUseMessageSystem {
    public:
        StageSceneStateOption(char const*,al::Scene *,al::LayoutInitInfo const&,FooterParts *,GameDataHolder *,bool);
        ~StageSceneStateOption();

        virtual al::MessageSystem* getMessageSystem(void) const override { return mMsgSystem; }
        
        void updateConfigDataInfo(GameConfigData const*);
        void killAllLayouts(void);
        void init(void);
        void appear(void);
        void kill(void);
        void getSelectedFileId(void);
        void decide(al::Nerve const*,SimpleLayoutMenu *,CommonVerticalList *);
        void openConfirm(al::Nerve const*,SimpleLayoutMenu *,CommonVerticalList *);
        void cancel(al::Nerve const*,SimpleLayoutMenu *,CommonVerticalList *);
        void endConfig(void);
        void updateSaveDataInfo(bool);
        void changeNerve(al::Nerve const*, SimpleLayoutMenu*, CommonVerticalList*);
        
        bool isModeSelectEnd(void) const;
        bool isChangeLanguage(void) const;

        void exeOptionTop(void);
        void exeModeSelectSelecting(void);
        void exeModeSelectSelectingByHelp(void);
        void exeModeSelectConfirmYesNo(void);
        void exeModeSelectConfirmEnd(void);
        void exeConfig(void);
        void exeDataManager(void);
        void exeSaveDataSelecting(void);
        void exeSaveDataConfirmYesNo(void);
        void exeSaveDataSaving(void);
        void exeSaveDataSaved(void);
        void exeLoadDataSelecting(void);
        void exeLoadDataConfirmNg(void);
        void exeLoadDataConfirmYesNo(void);
        void exeLoadDataSaving(void);
        void exeDeleteDataSelecting(void);
        void exeDeleteDataConfirmNg(void);
        void exeDeleteDataConfirmYesNo(void);
        void exeDeleteDataDeleting(void);
        void exeDeleteDataDeleted(void);
        void exeLanguageSetting(void);
        void exeLanguageSettingConfirmYesNo(void);
        void exeWaitEndDecideAnim(void);
        void exeWaitEndDecideAnimAndAutoSave(void);
        void exeWaitEndAutoSave(void);
        void exeClose(void);

        void *field_0x28;
        void *field_0x30;
        void *field_0x38;
        char *field_0x40; // stored with "RightIn"
        char *field_0x48; // stored with "RightOut"
        bool field_0x50;
        unsigned char field_0x51[7];
        FooterParts *mFooterParts;
        void *field_0x60;
        SimpleLayoutMenu *field_0x68;
        CommonVerticalList *field_0x70;
        al::SimpleLayoutAppearWaitEnd *field_0x78;
        CommonVerticalList *field_0x80;
        SimpleLayoutMenu *field_0x88;
        CommonVerticalList *field_0x90;
        al::SimpleLayoutAppearWaitEnd *field_0x98;
        FooterParts *field_0xa0;
        SimpleLayoutMenu *field_0xa8;
        CommonVerticalList *field_0xb0;
        SimpleLayoutMenu *field_0xb8;
        CommonVerticalList *field_0xc0;
        SimpleLayoutMenu *field_0xc8;
        void *field_0xd0;
        al::WindowConfirmData *field_0xd8;
        SimpleLayoutMenu *field_0xe0;
        CommonVerticalList *field_0xe8;
        void *field_0xf0;
        void *field_0xf8;
        void *field_0x100;
        void *field_0x108;
        void *field_0x110;
        void *field_0x118;
        void *field_0x120;
        void *field_0x128;
        void *field_0x130;
        void *field_0x138;
        int field_0x140;
        int field_0x144;
        SimpleLayoutMenu *field_0x148;
        FooterParts *field_0x150;
        CommonVerticalList *field_0x158;
        al::WindowConfirm *field_0x160;
        void *field_0x168;
        al::Scene *mScene;
        GameDataHolder *mDataHolder;
        bool field_0x180;
        al::MessageSystem *mMsgSystem;
        InputSeparator *mInputSeperator;
};