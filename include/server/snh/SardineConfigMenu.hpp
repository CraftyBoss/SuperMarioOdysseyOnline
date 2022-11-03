#pragma once

#include "server/gamemode/GameModeConfigMenu.hpp"
#include "game/Layouts/CommonVerticalList.h"
#include "server/gamemode/GameModeBase.hpp"

class SardineConfigMenu : public GameModeConfigMenu {
public:
    SardineConfigMenu();
    
    void initMenu(const al::LayoutInitInfo &initInfo) override;
    const sead::WFixedSafeString<0x200> *getStringData() override;
    bool updateMenu(int selectIndex) override;

    const int getMenuSize() override { return mItemCount; }

private:
    static constexpr int mItemCount = 6;
};