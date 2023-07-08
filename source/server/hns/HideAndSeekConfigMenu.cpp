#include "server/hns/HideAndSeekConfigMenu.hpp"
#include <cmath>
#include "logger.hpp"
#include "server/gamemode/GameModeManager.hpp"
#include "server/hns/HideAndSeekMode.hpp"
#include "server/Client.hpp"

HideAndSeekConfigMenu::HideAndSeekConfigMenu() : GameModeConfigMenu() {
    gravityOn = new sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>();
    gravityOn->mBuffer[0].copy(u"Toggle H&S Gravity (ON)");

    gravityOff = new sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>();
    gravityOff->mBuffer[0].copy(u"Toggle H&S Gravity (OFF)");
}

void HideAndSeekConfigMenu::initMenu(const al::LayoutInitInfo &initInfo) {
    
}

const sead::WFixedSafeString<0x200>* HideAndSeekConfigMenu::getStringData() {
    HideAndSeekInfo *curMode = GameModeManager::instance()->getInfo<HideAndSeekInfo>();
    return (
        GameModeManager::instance()->isMode(GameMode::HIDEANDSEEK)
        && curMode != nullptr
        && curMode->mIsUseGravity
        ? gravityOn->mBuffer
        : gravityOff->mBuffer
    );
}

bool HideAndSeekConfigMenu::updateMenu(int selectIndex) {

    HideAndSeekInfo *curMode = GameModeManager::instance()->getInfo<HideAndSeekInfo>();

    Logger::log("Setting Gravity Mode.\n");

    if (!curMode) {
        Logger::log("Unable to Load Mode info!\n");
        return true;   
    }
    
    switch (selectIndex) {
        case 0: {
            if (GameModeManager::instance()->isMode(GameMode::HIDEANDSEEK)) {
                curMode->mIsUseGravity = !curMode->mIsUseGravity;
            }
            return true;
        }
        default:
            Logger::log("Failed to interpret Index!\n");
            return false;
    }
    
}
