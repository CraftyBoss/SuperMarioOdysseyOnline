#include "game/StageScene/StageSceneStateServerConfig.hpp"
#include <cstdlib>
#include <math.h>
#include "game/SaveData/SaveDataAccessFunction.h"
#include "server/Client.hpp"
#include "al/util.hpp"
#include "al/util/NerveUtil.h"
#include "container/seadPtrArray.h"
#include "container/seadSafeArray.h"
#include "logger.hpp"
#include "prim/seadSafeString.h"
#include "prim/seadStringUtil.h"
#include "rs/util/InputUtil.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeFactory.hpp"
#include "server/HideAndSeekMode.hpp"

StageSceneStateServerConfig::StageSceneStateServerConfig(const char *name, al::Scene *scene, const al::LayoutInitInfo &initInfo, FooterParts *footerParts, GameDataHolder *dataHolder, bool) : al::HostStateBase<al::Scene>(name, scene) {
    mFooterParts = footerParts;
    mGameDataHolder = dataHolder;

    mMsgSystem = initInfo.getMessageSystem();

    mInput = new InputSeparator(mHost, true);

    // page 0 menu
    mMainOptions = new SimpleLayoutMenu("ServerConfigMenu", "OptionSelect", initInfo, 0, false);
    mMainOptionsList = new CommonVerticalList(mMainOptions, initInfo, true);

    al::setPaneString(mMainOptions, "TxtOption", u"Server Configuration", 0);

    mMainOptionsList->initDataNoResetSelected(5);

    sead::SafeArray<sead::WFixedSafeString<0x200>, 5>* mainMenuOptions =
        new sead::SafeArray<sead::WFixedSafeString<0x200>, 5>();

    mainMenuOptions->mBuffer[ServerConfigOption::GAMEMODECONFIG].copy(u"Gamemode Config");
    mainMenuOptions->mBuffer[ServerConfigOption::GAMEMODESWITCH].copy(u"Change Gamemode");
    mainMenuOptions->mBuffer[ServerConfigOption::RECONNECT].copy(u"Reconnect to Server");
    mainMenuOptions->mBuffer[ServerConfigOption::SETIP].copy(u"Change Server IP");
    mainMenuOptions->mBuffer[ServerConfigOption::SETPORT].copy(u"Change Server Port");

    mMainOptionsList->addStringData(mainMenuOptions->mBuffer, "TxtContent");

    // gamemode select menu

    mModeSelect = new SimpleLayoutMenu("GamemodeSelectMenu", "OptionSelect", initInfo, 0, false);
    mModeSelectList = new CommonVerticalList(mModeSelect, initInfo, true);

    al::setPaneString(mModeSelect, "TxtOption", u"Gamemode Selection", 0);

    const int modeCount = GameModeFactory::getModeCount();

    mModeSelectList->initDataNoResetSelected(modeCount);

    sead::SafeArray<sead::WFixedSafeString<0x200>, modeCount>* modeSelectOptions =
        new sead::SafeArray<sead::WFixedSafeString<0x200>, modeCount>();

    for (size_t i = 0; i < modeCount; i++) {
        const char* modeName = GameModeFactory::getModeName(i);
        modeSelectOptions->mBuffer[i].convertFromMultiByteString(modeName, strlen(modeName));
    }

    mModeSelectList->addStringData(modeSelectOptions->mBuffer, "TxtContent");

    // gamemode config menu
    mGamemodeConfig = new SimpleLayoutMenu("GameModeConfigMenu", "OptionSelect", initInfo, 0, false);
    mGameModeConfigList = new CommonVerticalList(mGamemodeConfig, initInfo, true);

    al::setPaneString(mGamemodeConfig, "TxtOption", u"Gamemode Configuration", 0);

    mGamemodeConfigMenu = Client::tryCreateModeMenu();

    if (mGamemodeConfigMenu) {
        mGameModeConfigList->initDataNoResetSelected(mGamemodeConfigMenu->getMenuSize());

        mGameModeConfigList->addStringData(mGamemodeConfigMenu->getStringData(), "TxtContent");
    }

    mCurrentList = mMainOptionsList;
    mCurrentMenu = mMainOptions;
}

void StageSceneStateServerConfig::init() {
    initNerve(&nrvStageSceneStateServerConfigMainMenu, 0);
}

void StageSceneStateServerConfig::appear(void) {
    mCurrentMenu->startAppear("Appear");
    al::NerveStateBase::appear();
}

void StageSceneStateServerConfig::kill(void) {
    mCurrentMenu->startEnd("End");
    al::NerveStateBase::kill();
}

al::MessageSystem* StageSceneStateServerConfig::getMessageSystem(void) const {
    return mMsgSystem;
}

void StageSceneStateServerConfig::exeMainMenu() {
    if (al::isFirstStep(this)) {

        mInput->reset();

        mCurrentList->activate();

        mCurrentList->appearCursor();

        mIsDecideConfig = false;

    }

    mInput->update();

    mCurrentList->update();

    if (mInput->isTriggerUiUp()) {
        mCurrentList->up();    }

    if (mInput->isTriggerUiDown()) {
        mCurrentList->down();
    }

    if (rs::isTriggerUiCancel(mHost)) {
        kill();
    }

    if (rs::isTriggerUiDecide(mHost)) {
        al::startHitReaction(mCurrentMenu, "決定", 0);
        mCurrentList->endCursor();
        mCurrentList->decide();
        mIsDecideConfig = true;
    }

    if (mIsDecideConfig && mCurrentList->isDecideEnd()) {
        switch (mCurrentList->mCurSelected) {
        case ServerConfigOption::GAMEMODECONFIG: {
            al::setNerve(this, &nrvStageSceneStateServerConfigGamemodeConfig);
            break;
        }
        case ServerConfigOption::GAMEMODESWITCH: {
            al::setNerve(this, &nrvStageSceneStateServerConfigGamemodeSelect);
            break;
        }
        case ServerConfigOption::RECONNECT: {
            al::setNerve(this, &nrvStageSceneStateServerConfigRestartServer);
            break;
        }
        case ServerConfigOption::SETIP: {
            al::setNerve(this, &nrvStageSceneStateServerConfigOpenKeyboardIP);
            break;
        }
        case ServerConfigOption::SETPORT: {
            al::setNerve(this, &nrvStageSceneStateServerConfigOpenKeyboardPort);
            break;
        }
        default:
            kill();
            break;
        }
    }
}

void StageSceneStateServerConfig::exeOpenKeyboardIP() {
    if (al::isFirstStep(this)) {

        mCurrentList->deactivate();

        Client::getKeyboard()->setHeaderText(u"Set a Server IP Below.");
        Client::getKeyboard()->setSubText(u"");

        bool isSave = Client::openKeyboardIP(); // anything that happens after this will be ran after the keyboard closes
        
        al::startHitReaction(mCurrentMenu, "リセット", 0);

        if(isSave) 
            al::setNerve(this, &nrvStageSceneStateServerConfigSaveData);
        else
            al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
    }
}

void StageSceneStateServerConfig::exeOpenKeyboardPort() {
    if (al::isFirstStep(this)) {

        mCurrentList->deactivate();

        Client::getKeyboard()->setHeaderText(u"Set a Server Port Below.");
        Client::getKeyboard()->setSubText(u"");

        bool isSave = Client::openKeyboardPort(); // anything that happens after this will be ran after the keyboard closes

        al::startHitReaction(mCurrentMenu, "リセット", 0);
        
        if(isSave) 
            al::setNerve(this, &nrvStageSceneStateServerConfigSaveData);
        else
            al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
    }
}

void StageSceneStateServerConfig::exeRestartServer() {
    if (al::isFirstStep(this)) {
        mCurrentList->deactivate();

        Client::showConnect();

        Client::restartConnection();
    }

    if (Client::isSocketActive()) {

        Client::hideConnect();

        al::startHitReaction(mCurrentMenu, "リセット", 0);
        
        al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
    } else {
        al::setNerve(this, &nrvStageSceneStateServerConfigConnectError);
    }
}

void StageSceneStateServerConfig::exeGamemodeConfig() {
    if (al::isFirstStep(this)) {
        mCurrentList = mGameModeConfigList;
        mCurrentMenu = mGamemodeConfig;
        subMenuStart();
    }

    subMenuUpdate();

    if (mIsDecideConfig && mCurrentList->isDecideEnd()) {
        if (mGamemodeConfigMenu->updateMenu(mCurrentList->mCurSelected)) {
            endSubMenu();
        }
    }
}

void StageSceneStateServerConfig::exeGamemodeSelect() {
    if (al::isFirstStep(this)) {

        mCurrentList = mModeSelectList;
        mCurrentMenu = mModeSelect;

        subMenuStart();

    }

    subMenuUpdate();

    if (mIsDecideConfig && mCurrentList->isDecideEnd()) {
        Logger::log("Setting Server Mode to: %d\n", mCurrentList->mCurSelected);
        Client::setServerMode(static_cast<GameMode>(mCurrentList->mCurSelected));
        endSubMenu();
    }
}

void StageSceneStateServerConfig::exeConnectError() {
    if (al::isFirstStep(this)) {
        Client::showConnectError(u"Failed to Reconnect!");
    }

    if (al::isGreaterEqualStep(this, 60)) { // close after 1 second
        Client::hideConnect();
        al::startHitReaction(mCurrentMenu, "リセット", 0);
        al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
    }
}

void StageSceneStateServerConfig::exeSaveData() {

    if (al::isFirstStep(this)) {
        SaveDataAccessFunction::startSaveDataWrite(mGameDataHolder);
    }

    if (SaveDataAccessFunction::updateSaveDataAccess(mGameDataHolder, false)) {
        al::startHitReaction(mCurrentMenu, "リセット", 0);
        al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
    }
}

void StageSceneStateServerConfig::endSubMenu() {
    mCurrentList->deactivate();
    mCurrentMenu->kill();

    mCurrentList = mMainOptionsList;
    mCurrentMenu = mMainOptions;

    mCurrentMenu->startAppear("Appear");

    al::startHitReaction(mCurrentMenu, "リセット", 0);
    al::setNerve(this, &nrvStageSceneStateServerConfigMainMenu);
}

void StageSceneStateServerConfig::subMenuStart() {
    mCurrentList->deactivate();

    mCurrentMenu->kill();

    mInput->reset();

    mCurrentList->activate();

    mCurrentList->appearCursor();

    mCurrentMenu->startAppear("Appear");

    mIsDecideConfig = false;
}

void StageSceneStateServerConfig::subMenuUpdate() {
    mInput->update();

    mCurrentList->update();

    if (mInput->isTriggerUiUp()) {
        mCurrentList->up();
    }

    if (mInput->isTriggerUiDown()) {
        mCurrentList->down();
    }

    if (rs::isTriggerUiCancel(mHost)) {
        endSubMenu();
    }

    if (rs::isTriggerUiDecide(mHost)) {
        al::startHitReaction(mCurrentMenu, "決定", 0);
        mCurrentList->endCursor();
        mCurrentList->decide();
        mIsDecideConfig = true;
    }
}


namespace {
NERVE_IMPL(StageSceneStateServerConfig, MainMenu)
NERVE_IMPL(StageSceneStateServerConfig, OpenKeyboardIP)
NERVE_IMPL(StageSceneStateServerConfig, OpenKeyboardPort)
NERVE_IMPL(StageSceneStateServerConfig, RestartServer)
NERVE_IMPL(StageSceneStateServerConfig, GamemodeConfig)
NERVE_IMPL(StageSceneStateServerConfig, GamemodeSelect)
NERVE_IMPL(StageSceneStateServerConfig, SaveData)
NERVE_IMPL(StageSceneStateServerConfig, ConnectError)
}