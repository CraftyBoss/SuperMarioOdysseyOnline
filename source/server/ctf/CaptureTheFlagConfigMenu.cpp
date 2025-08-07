#include "server/ctf/CaptureTheFlagConfigMenu.hpp"
#include "logger.hpp"
#include "server/Client.hpp"
#include "server/ctf/CaptureTheFlagMode.hpp"

CaptureTheFlagConfigMenu::CaptureTheFlagConfigMenu() : GameModeConfigMenu() {}

void CaptureTheFlagConfigMenu::initMenu(const al::LayoutInitInfo &initInfo) {
    Logger::log("CTF Mode: config screen!\n");
    sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>* menuOptions =
        new sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>();
    menuOptions->mBuffer[0].copy(u"Set Score Limit: 3");
    menuOptions->mBuffer[1].copy(u"Set Score Limit: 5");
    menuOptions->mBuffer[2].copy(u"Set Score Limit: 10");
    menuOptions->mBuffer[3].copy(u"Reset Scores");
}

const sead::WFixedSafeString<0x200>* CaptureTheFlagConfigMenu::getStringData() {
    static sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount> menuOptions;
    menuOptions.mBuffer[0].copy(u"Set Score Limit: 3");
    menuOptions.mBuffer[1].copy(u"Set Score Limit: 5");
    menuOptions.mBuffer[2].copy(u"Set Score Limit: 10");
    menuOptions.mBuffer[3].copy(u"Reset Scores");
    return menuOptions.mBuffer;
}

bool CaptureTheFlagConfigMenu::updateMenu(int selectIndex) {
    CaptureTheFlagInfo* info = GameModeManager::instance()->getInfo<CaptureTheFlagInfo>();

    if (!info) {
        Logger::log("Unable to Load Mode info!\n");
        return true;
    }
    
    switch (selectIndex) {
        case 0:
            info->mMaxScore = 3;
            Logger::log("Score limit set to 3\n");
            return true;
        case 1:
            info->mMaxScore = 5;
            Logger::log("Score limit set to 5\n");
            return true;
        case 2:
            info->mMaxScore = 10;
            Logger::log("Score limit set to 10\n");
            return true;
        case 3:
            info->mRedScore = 0;
            info->mBlueScore = 0;
            Logger::log("Scores reset\n");
            return true;
        default:
            return false;
    }
}