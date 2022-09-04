#include "al/LiveActor/LiveActor.h"
#include "al/camera/CameraTicket.h"
#include "al/util.hpp"
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutKit.h"
#include "al/gamepad/util.h"
#include "al/camera/CameraPoser.h"
#include "al/camera/alCameraPoserFunction.h"
#include "al/factory/ProjectActorFactory.h"
#include "al/area/AreaObjGroup.h"
#include "al/actor/DemoActor.h"
#include "al/area/ChangeStageInfo.h"

#include "game/StageScene/StageScene.h"
#include "game/Layouts/CoinCounter.h"
#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerCameraTarget.h"
#include "game/Player/PlayerAnimControlRun.h"
#include "game/Player/PlayerFactory.h"
#include "game/Player/PlayerCostumeInfo.h"
#include "game/Controller/ControllerAppletFunction.h"
#include "game/GameData/GameDataHolderWriter.h"
#include "game/GameData/GameDataFunction.h"
#include "game/Actors/Shine.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/UI/MenuSelectParts.h"
#include "game/StageScene/StageSceneStateServerConfig.hpp"
#include "game/System/Application.h"

#include "rs/util.hpp"
#include "rs/util/SensorUtil.h"

#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "sead/prim/seadSafeString.hpp"
#include "sead/gfx/seadCamera.h"
#include "sead/basis/seadNew.h"
#include "sead/gfx/seadColor.h"
#include "types.h"

#include "agl/DrawContext.h"
#include "agl/RenderBuffer.h"
#include "agl/utl.h"

#include "nn/swkbd/swkbd.h"

#include "helpers.hpp"
#include "logger.hpp"
#include "server/Client.hpp"
#include "debugMenu.hpp"
#include "Keyboard.hpp"
#include "server/DeltaTime.hpp"

static bool isInGame = false;

static bool debugMode = false;

constexpr const char* captureNames[] = {
    "AnagramAlphabetCharacter", "Byugo", "Bubble", "Bull", "Car", "ElectricWire",
    "KillerLauncherMagnum", "KuriboPossessed",
    "WanwanBig",  // has sub-actors
    "KillerLauncher", "Koopa",
    "Wanwan",  // has sub-actors
    "Pukupuku", "PukupukuSnow",
    "Gamane",  // has sub-actors
    "FireBrosPossessed", "PackunFire", "Frog", "Kakku", "Hosui", "HammerBrosPossessed", "Megane",
    "KaronWing", "KuriboWing", "PackunPoison", "Radicon", "Tank", "Tsukkun", "TRex", "TRexSleep",
    "TRexPatrol",
    // "Yukimaru", (is a player actor)
    "Imomu", "SenobiGeneratePoint"
    // "HackFork",
    // "Yoshi" (is a player actor)
};