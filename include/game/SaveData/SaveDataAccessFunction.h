#pragma once

#include "game/GameData/GameDataHolder.h"

namespace SaveDataAccessFunction {
    void startSaveDataInit(GameDataHolder *);
    void startSaveDataInitSync(GameDataHolder *);
    void startSaveDataLoadFile(GameDataHolder *);
    void startSaveDataReadSync(GameDataHolder *);
    void startSaveDataReadAll(GameDataHolder *);
    void startSaveDataWrite(GameDataHolder *);
    void startSaveDataWriteWithWindow(GameDataHolder *);
    void startSaveDataCopyWithWindow(GameDataHolder *,int,int);
    void startSaveDataDeleteWithWindow(GameDataHolder *,int);
    void startSaveDataWriteSync(GameDataHolder *);
    bool updateSaveDataAccess(GameDataHolder *,bool);
    bool isEnableSave(GameDataHolder const*);
    bool isDoneSave(GameDataHolder *);
}