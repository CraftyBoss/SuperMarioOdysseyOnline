#pragma once

#include "game/Layouts/CommonVerticalList.h"

class GameModeConfigMenu {
public:
    GameModeConfigMenu() = default;

    virtual void initMenu(const al::LayoutInitInfo &initInfo) {return;}

    virtual bool updateMenu(int selectIndex) {return false;}

    virtual const sead::WFixedSafeString<0x200>* getStringData() {return nullptr;}

    virtual const int getMenuSize() {return 0;}

};