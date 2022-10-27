#include "server/snh/SardineConfigMenu.hpp"
#include "logger.hpp"
#include "server/Client.hpp"
#include "server/gamemode/GameModeManager.hpp"
#include "server/snh/SardineMode.hpp"
#include <cmath>

SardineConfigMenu::SardineConfigMenu()
    : GameModeConfigMenu()
{
}

void SardineConfigMenu::initMenu(const al::LayoutInitInfo& initInfo)
{
}

const sead::WFixedSafeString<0x200>* SardineConfigMenu::getStringData()
{
    sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>* gamemodeConfigOptions = new sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>();

    gamemodeConfigOptions->mBuffer[0].copy(u"Sardine Gravity On");
    gamemodeConfigOptions->mBuffer[1].copy(u"Sardine Gravity Off");
    gamemodeConfigOptions->mBuffer[2].copy(u"Enable Sardine Tether (Default)");
    gamemodeConfigOptions->mBuffer[3].copy(u"Disable Sardine Tether");

    return gamemodeConfigOptions->mBuffer;
}

bool SardineConfigMenu::updateMenu(int selectIndex)
{

    SardineInfo* curMode = GameModeManager::instance()->getInfo<SardineInfo>();

    Logger::log("Setting Gravity Mode.\n");

    if (!curMode) {
        Logger::log("Unable to Load Mode info!\n");
        return true;
    }

    switch (selectIndex) {
    case 0: {
        if (GameModeManager::instance()->isMode(GameMode::SARDINE)) {
            curMode->mIsUseGravity = true;
        }
        return true;
    }
    case 1: {
        if (GameModeManager::instance()->isMode(GameMode::SARDINE)) {
            curMode->mIsUseGravity = false;
        }
        return true;
    }
    case 2: {
        if (GameModeManager::instance()->isMode(GameMode::SARDINE)) {
            curMode->mIsTether = true;
        }
        return true;
    }
    case 3: {
        if (GameModeManager::instance()->isMode(GameMode::SARDINE)) {
            curMode->mIsTether = false;
        }
        return true;
    }
    default:
        Logger::log("Failed to interpret Index!\n");
        return false;
    }
}