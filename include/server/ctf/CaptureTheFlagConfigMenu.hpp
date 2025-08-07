#pragma once

#include "server/gamemode/GameModeConfigMenu.hpp"
#include "game/Layouts/CommonVerticalList.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeInfoBase.hpp"
#include "server/gamemode/GameModeTimer.hpp"

class CaptureTheFlagConfigMenu : public GameModeConfigMenu {
public:
    CaptureTheFlagConfigMenu();
    
    void initMenu(const al::LayoutInitInfo &initInfo) override;
    const sead::WFixedSafeString<0x200>* getStringData() override;
    bool updateMenu(int selectIndex) override;
    const int getMenuSize() override { return mItemCount; }
    
private:
    static constexpr int mItemCount = 4;
    
};