/**
 * @file GameDataFunction.h
 * @brief Holds static functions for getting / storage save data.
 */

#pragma once

#include <al/LiveActor/LiveActor.h>
#include "GameDataHolderAccessor.h"
#include "GameDataHolderWriter.h"
#include "al/area/ChangeStageInfo.h"
#include "game/GameData/GameDataFile.h"

class GameDataFunction
{
public:

    // sets the current worn costume
    static void wearCostume(GameDataHolderWriter, char const *);

    // sets the current worn cap
    static void wearCap(GameDataHolderWriter, char const*);

    // remove cappy
    static void disableCapByPlacement(al::LiveActor const*);

    // restarts current stage
    static void restartStage(GameDataHolderWriter);

    // restarts current stage
    static void missAndRestartStage(GameDataHolderWriter);

    // attempts to change the current stage the player is in
    static bool tryChangeNextStage(GameDataHolderWriter, ChangeStageInfo const *);

    // gets prev save file's current world id
    static s32 getPrevWorldId(GameDataHolderAccessor);
    // gets current save file's current world id
    static s32 getCurrentWorldId(GameDataHolderAccessor);
    // gets next save file's current world id
    static s32 getNextWorldId(GameDataHolderAccessor);

    // gets current save file's current stage scenario no
    static u8 getScenarioNo(al::LiveActor const*);

    static s32 calcNextScenarioNo(GameDataHolderAccessor);
    // gets the current scenario No of the specified kingdom
    static s32 getWorldScenarioNo(GameDataHolderAccessor, int);

    static char* getCurrentStageName(GameDataHolderAccessor);

    static char* getMainStageName(GameDataHolderAccessor, int);

    static char* getNextStageName(GameDataHolderAccessor);

    static s32 getCurrentShineNum(GameDataHolderAccessor);

    // gets total moons collected on a specified save file (-1 for current save)
    static s32 getTotalShineNum(GameDataHolderAccessor, int);

    // gets the total amount of moons available in a kingdom
    static s32 getWorldTotalShineNum(GameDataHolderAccessor, int); 

    // checks save file if shine is collected in kingdom index
    static bool isGotShine(GameDataHolderAccessor, int, int);

    // checks save file if shine is collected by shine index only (0 through 725)
    static bool isGotShine(GameDataHolderAccessor, int);

    // Gets Index for X Kingdom
    static s32 getWorldIndexWaterfall(void);
    static s32 getWorldIndexMoon(void);

    // gets the current level of the Odyssey
    static int getHomeLevel(GameDataHolderAccessor);
    
    // checks if cappy is enabled
    static bool isEnableCap(GameDataHolderAccessor);
    // enables cappy if not enabled already
    static void enableCap(GameDataHolderWriter);

    // kills the player
    static void killPlayer(GameDataHolderWriter);

    // damages the player
    static void damagePlayer(GameDataHolderWriter);

    // upgrades the odyssey
    static void upHomeLevel(GameDataHolderWriter);

    // Saves shine if obtained
    static void setGotShine(GameDataHolderWriter, ShineInfo const*);

    //unlocks a kingdom based off index
    static void unlockWorld(GameDataHolderWriter, int);
    //sets the scenario of the specified kingdom
    static void setMainScenarioNo(GameDataHolderWriter, int scenarioNo);

    // checks if the opening cutscene needs to play
    static bool isPlayDemoOpening(GameDataHolderAccessor);

    // checks if odyssey is/needs a repair
    static bool isRepairHome(GameDataHolderAccessor);
    static void repairHome(GameDataHolderWriter);

    // checks if odyssey is crashed
    static bool isCrashHome(GameDataHolderAccessor);
    static void crashHome(GameDataHolderWriter);

    // checks if odyssey is activated 
    static bool isActivateHome(GameDataHolderAccessor);
    static void activateHome(GameDataHolderWriter);

    // checks if the odyssey has launched for the first time.
    static bool isLaunchHome(GameDataHolderAccessor);
    static void launchHome(GameDataHolderWriter);

    static bool isHomeShipStage(GameDataHolder const *);

    // used during the event that enables the odyssey to be used (enables the globe for the odyssey)
    static void talkCapNearHomeInWaterfall(al::LiveActor const*);

    // gives the player a life up heart
    static void getLifeMaxUpItem(al::LiveActor const *);

    // gets current coin count
    static s32 getCoinNum(GameDataHolderAccessor);

    // gets current purple coin count
    static s32 getCoinCollectNum(GameDataHolderAccessor);

    // saves an objects Stage Name, Object ID, and custom value to the save file
    static void saveObjS32(GameDataHolderWriter, al::PlacementId const*, int);

    // gets the value stored in the unique obj info that matches placement id and curstage
    static bool tryFindSaveObjS32Value(int *value, GameDataHolderAccessor accessor, al::PlacementId const* objId);

    // subtracts the supplied int value from the current coin count
    static void subCoin(GameDataHolderWriter, int value);

    static bool isUnlockedWorld(GameDataHolderAccessor, int);

    static bool isUnlockedNextWorld(GameDataHolderAccessor);

    static bool isUnlockedAllWorld(GameDataHolderAccessor);

    static bool isUnlockedCurrentWorld(GameDataHolderAccessor);

    static bool isUnlockWorld(int);

    static bool isUnlockFirstForest(void);
    
    static bool isUnlockFirstSea(void);

};