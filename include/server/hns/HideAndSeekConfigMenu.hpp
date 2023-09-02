#pragma once

#include "server/gamemode/GameModeConfigMenu.hpp"
#include "game/Layouts/CommonVerticalList.h"
#include "server/gamemode/GameModeBase.hpp"

class HideAndSeekConfigMenu : public GameModeConfigMenu {
public:
    HideAndSeekConfigMenu();
    
    void initMenu(const al::LayoutInitInfo &initInfo) override;
    const sead::WFixedSafeString<0x200>* getStringData() override;
    bool updateMenu(int selectIndex) override;

    const int getMenuSize() override { return mItemCount; }

private:
    static constexpr int mItemCount = 1;
    sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>* gravityOn = nullptr;
    sead::SafeArray<sead::WFixedSafeString<0x200>, mItemCount>* gravityOff = nullptr;
};
