#include "main.hpp"

#include <cmath>
#include <math.h>

#include "actors/PuppetActor.h"

#include "al/execute/ExecuteOrder.h"
#include "al/execute/ExecuteTable.h"
#include "al/execute/ExecuteTableHolderDraw.h"
#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"
#include "al/util/AudioUtil.h"
#include "al/util/CameraUtil.h"
#include "al/util/ControllerUtil.h"
#include "al/util/GraphicsUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/NerveUtil.h"

#include "debugMenu.hpp"

#include "game/GameData/GameDataHolderAccessor.h"
#include "game/GameData/GameDataFunction.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerHackKeeper.h"
#include "game/StageScene/StageScene.h"

#include "helpers.hpp"

#include "logger.hpp"

#include "puppets/PuppetInfo.h"

#include "sead/container/seadSafeArray.h"
#include "sead/gfx/seadPrimitiveRenderer.h"
#include "sead/heap/seadHeap.h"
#include "sead/math/seadVector.h"

#include "server/Client.hpp"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeFactory.hpp"
#include "server/gamemode/GameModeManager.hpp"

#include "rs/util.hpp"

static int pInfSendTimer = 0;
static int gameInfSendTimer = 0;

void updatePlayerInfo(GameDataHolderAccessor holder, PlayerActorBase* playerBase, bool isYukimaru) {
    if (pInfSendTimer >= 3) {
        Client::sendPlayerInfPacket(playerBase, isYukimaru);

        if (!isYukimaru) {
            Client::sendHackCapInfPacket(((PlayerActorHakoniwa*)playerBase)->mHackCap);

            Client::sendCaptureInfPacket((PlayerActorHakoniwa*)playerBase);
        }

        pInfSendTimer = 0;
    }

    if (gameInfSendTimer >= 60) {
        if (isYukimaru) {
            Client::sendGameInfPacket(holder);
        } else {
            Client::sendGameInfPacket((PlayerActorHakoniwa*)playerBase, holder);
        }

        gameInfSendTimer = 0;
    }

    pInfSendTimer++;
    gameInfSendTimer++;
}

// ------------- Hooks -------------

int debugPuppetIndex = 0;
int debugCaptureIndex = 0;
static int pageIndex = 0;

static const int maxPages = 3;

void drawMainHook(HakoniwaSequence* curSequence, sead::Viewport* viewport, sead::DrawContext* drawContext) {
    GameModeManager* gmm  = GameModeManager::instance();
    GameModeBase*    mode = gmm->getMode<GameModeBase>();

    if (!mode || !mode->pauseTimeWhenPaused() || !gmm->isPaused()) {
        Time::calcTime(); // this needs to be ran every frame, so running it here works
    }

    if (!debugMode) {
        al::executeDraw(curSequence->mLytKit, "２Ｄバック（メイン画面）");
        return;
    }

    Client*       client      = Client::instance();
    SocketClient* socket      = client->mSocket;
    bool          isConnected = socket->isConnected();

    int dispHeight = al::getLayoutDisplayHeight();

    gTextWriter->mViewport = viewport;

    gTextWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);

    drawBackground((agl::DrawContext*)drawContext);

    gTextWriter->beginDraw();
    gTextWriter->setCursorFromTopLeft(sead::Vector2f(10.f, 10.f));

    gTextWriter->printf("FPS: %d\n", static_cast<int>(round(Application::sInstance->mFramework->calcFps())));

    gTextWriter->setCursorFromTopLeft(sead::Vector2f(10.f, (dispHeight / 3) + 30.f));
    gTextWriter->setScaleFromFontHeight(20.f);

    if (Client::isServerHidden()) {
        gTextWriter->printf(
            isConnected ? "Server: <hidden> | %d/%d Players\n" : "Server: <hidden>\n",
            isConnected ? Client::getConnectCount() + 1 : 0,
            isConnected ? Client::getMaxPlayerCount()   : 0
        );
    } else {
        gTextWriter->printf(
            isConnected ? "Server: %s:%d | %d/%d Players\n" : "Server: %s:%d\n",
            socket->getIP(),
            socket->getPort(),
            isConnected ? Client::getConnectCount() + 1 : 0,
            isConnected ? Client::getMaxPlayerCount()   : 0
        );
    }
    gTextWriter->printf("Your TCP status: %s\n", socket->getStateChar());
    gTextWriter->printf("Your UDP status: %s\n", socket->getUdpStateChar());

    sead::Heap* clientHeap = Client::getClientHeap();
    if (clientHeap) {
        sead::Heap* gmHeap = GameModeManager::instance()->getHeap();
        gTextWriter->printf(
            "Heap Use: %.1f/%.0f (Client) %.1f/%.0f (Gmode)\n",
            0.0009765625 * (clientHeap->getSize() - clientHeap->getFreeSize()),
            0.0009765625 * clientHeap->getSize(),
            0.0009765625 * (gmHeap->getSize() - gmHeap->getFreeSize()),
            0.0009765625 * gmHeap->getSize()
        );
    }

    gTextWriter->printf(
        "Queue Count: %d/%d (Send) %d/%d (Receive)\n",
        socket->getSendCount(),
        socket->getSendMaxCount(),
        socket->getRecvCount(),
        socket->getRecvMaxCount()
    );

#if EMU
    gTextWriter->printf("Mod version: %s for Emulators\n", TOSTRING(BUILDVERSTR));
#else
    gTextWriter->printf("Mod version: %s for Switch\n", TOSTRING(BUILDVERSTR));
#endif

    al::Scene* curScene = curSequence->curScene;

    if (curScene && isInGame) {
        sead::LookAtCamera* cam        = al::getLookAtCamera(curScene, 0);
        sead::Projection*   projection = al::getProjectionSead(curScene, 0);

        PlayerActorBase* playerBase = rs::getPlayerActor(curScene);

        PuppetActor* curPuppet   = Client::getPuppet(debugPuppetIndex - 1);
        PuppetActor* debugPuppet = Client::getDebugPuppet();
        if (debugPuppet) {
            curPuppet = debugPuppet;
        }

        sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
        renderer->setDrawContext(drawContext);
        renderer->setCamera(*cam);
        renderer->setProjection(*projection);

        GameMode      gameMode     = GameModeManager::instance()->getGameMode();
        GameModeBase* gameModeBase = GameModeManager::instance()->getMode<GameModeBase>();

        gTextWriter->printf("(ZR ←)------------ Page %d/%d -------------(ZR →)\n", pageIndex + 1, maxPages);

        switch (pageIndex)
        {
        case 0:
            {
                gTextWriter->printf(
                    "(ZL ←)----------%s Player %d/%d %s-----------(ZL →)\n\n",
                    debugPuppetIndex + 1 < 10 ? "-" : "",
                    debugPuppetIndex + 1,
                    Client::getMaxPlayerCount(),
                    Client::getMaxPlayerCount() < 10 ? "-" : ""
                );

                // Hide sensitive player information while an in a gamemode
                GameMode currentMode = GameModeManager::instance()->getGameMode();
                bool hideGameModeInfo = GameModeManager::instance()->isActive() &&
                (currentMode == GameMode::HIDEANDSEEK || currentMode == GameMode::SARDINE || currentMode == GameMode::FREEZETAG);

                if (debugPuppetIndex == 0) {
                    gTextWriter->printf("Player Name: %s\n",       Client::getClientName());
                    gTextWriter->printf("Connection Status: %s\n", isConnected ? "Online" : "Offline");
                    gTextWriter->printf("Game mode: %i | %s\n",    gameMode, GameModeFactory::getModeName(gameMode));
                    gTextWriter->printf("Costume: H: %s B: %s\n",client->getLastCostumeInfPacket()->capModel, client->getLastCostumeInfPacket()->bodyModel);

                // Only shows Stage, Scenario, Capture and Animation information when a player is NOT in a gamemode
                if (!hideGameModeInfo) {
                    gTextWriter->printf("Is in same Stage: Yes\n");
                    gTextWriter->printf("Stage: %s\n",            client->getLastGameInfPacket()->stageName);
                    gTextWriter->printf("Scenario: %u\n",         client->getLastGameInfPacket()->scenarioNo);

                    PlayerHackKeeper* hackKeeper = playerBase->getPlayerHackKeeper();
                    if (hackKeeper) {
                        PlayerActorHakoniwa* p1 = (PlayerActorHakoniwa*)playerBase;
                        if (hackKeeper->currentHackActor) {
                            gTextWriter->printf("Animation: %s\n", al::getActionName(hackKeeper->currentHackActor));
                        } else {
                            gTextWriter->printf("Animation: %s\n", p1->mPlayerAnimator->mAnimFrameCtrl->getActionName());
                        }
                    }
                }

                    if (gameModeBase) {
                        gameModeBase->debugMenuPlayer(gTextWriter);
                    }
                } else if (curPuppet) {
                    al::LiveActor* curModel = curPuppet->getCurrentModel();
                    PuppetInfo* curPupInfo = curPuppet->getInfo();

                    if (curModel && curPupInfo) {
                        gTextWriter->printf("Player Name: %s\n",       curPupInfo->puppetName);
                        gTextWriter->printf("Connection Status: %s\n", curPupInfo->isConnected ? "Online" : "Offline");
                        gTextWriter->printf("Game mode: %i | %s\n",    curPupInfo->gameMode, GameModeFactory::getModeName(curPupInfo->gameMode));
                        gTextWriter->printf("Costume: H: %s B: %s\n",  curPupInfo->costumeHead, curPupInfo->costumeBody);

                    // Hide the information that could reveal a player's position in a gamemode
                    if (!hideGameModeInfo) {
                        gTextWriter->printf("Is in same Stage: %s\n",  curPupInfo->isInSameStage ? "Yes" : "No");
                        gTextWriter->printf("Stage: %s\n",             curPupInfo->stageName);
                        gTextWriter->printf("Scenario: %u\n",          curPupInfo->scenarioNo);
                        gTextWriter->printf("Capture: %s\n",           curPupInfo->isCaptured ? curPupInfo->curHack : "");
                        gTextWriter->printf("Animation:  %d  %s\n",    curPupInfo->curAnim, curPupInfo->curAnimStr);
                       if (!curPupInfo->isCaptured) {
                            gTextWriter->printf("Model Animation: %s\n", al::getActionName(curModel));
                        }
                    }
                        if (gameModeBase) {
                            gameModeBase->debugMenuPlayer(gTextWriter, curPupInfo);
                        }
                    }
                }
            }
            break;
        case 1:
            {
                gTextWriter->printf("--------------- Animation & Cappy ---------------\n\n");
                PlayerHackKeeper* hackKeeper = playerBase->getPlayerHackKeeper();

                if (hackKeeper) {
                    PlayerActorHakoniwa* p1 = (PlayerActorHakoniwa*)playerBase; // its safe to assume that we're using a playeractorhakoniwa if the hack keeper isnt null

                    if (hackKeeper->currentHackActor) {
                        al::LiveActor* curHack = hackKeeper->currentHackActor;

                        gTextWriter->printf("Current Hack Animation: %s\n", al::getActionName(curHack));
                        gTextWriter->printf("Current Hack Name: %s\n", hackKeeper->getCurrentHackName());
                        sead::Quatf captureRot = curHack->mPoseKeeper->getQuat();
                        gTextWriter->printf("Current Hack Rot: %.3f %.3f %.3f %f\n", captureRot.x, captureRot.y, captureRot.z, captureRot.w);
                        sead::Quatf calcRot;
                        al::calcQuat(&calcRot, curHack);
                        gTextWriter->printf("Calc Hack Rot: %.3f %.3f %.3f %.3f\n", calcRot.x, calcRot.y, calcRot.z, calcRot.w);
                    } else {
                        gTextWriter->printf("Cur Action: %s\n", p1->mPlayerAnimator->mAnimFrameCtrl->getActionName());
                        gTextWriter->printf("Cur Sub Action: %s\n", p1->mPlayerAnimator->curSubAnim.cstr());
                        gTextWriter->printf("Is Cappy Flying? %s\n", BTOC(p1->mHackCap->isFlying()));
                        if (p1->mHackCap->isFlying()) {
                            gTextWriter->printf("Cappy Action: %s\n", al::getActionName(p1->mHackCap));
                            sead::Vector3f* capTrans = al::getTransPtr(p1->mHackCap);
                            sead::Vector3f* capRot = &p1->mHackCap->mJointKeeper->mJointRot;
                            gTextWriter->printf("Cappy: Position   Rotation\nX:   % 10.3f % 10.3f\nY:   % 10.3f % 10.3f\nZ:   % 10.3f % 10.3f\n",
                                capTrans->x, capRot->x,
                                capTrans->y, capRot->y,
                                capTrans->z, capRot->z
                            );
                            gTextWriter->printf("Cappy Skew: %.3f\n", p1->mHackCap->mJointKeeper->mSkew);
                        }
                    }
                }
            }
            break;
        case 2:
            {
                gTextWriter->printf("------------------- Controls --------------------\n\n");
                if (gameModeBase) {
                    gameModeBase->debugMenuControls(gTextWriter);
                }
                gTextWriter->printf("\n- ZR + ↑ | Open/close this debug menu\n");
            }
            break;
        default:
            break;
        }

        renderer->begin();

        // sead::Matrix34f mat = sead::Matrix34f::ident;
        // mat.setBase(3, sead::Vector3f::zero); // Sets the position of the matrix.
        //     For cubes, you need to put this at the location.
        //     For spheres, you can leave this at 0 0 0 since you set it in its draw function.
        renderer->setModelMatrix(sead::Matrix34f::ident);

        if (curPuppet) {
            renderer->drawSphere4x8(curPuppet->getInfo()->playerPos, 20, sead::Color4f(1.f, 0.f, 0.f, 0.25f));
            renderer->drawSphere4x8(al::getTrans(curPuppet), 20, sead::Color4f(0.f, 0.f, 1.f, 0.25f));
        } else if (debugPuppetIndex == 0) {
            renderer->drawSphere4x8(client->getLastPlayerInfPacket()->playerPos, 20, sead::Color4f(1.f, 0.f, 0.f, 0.25f));
        }

        renderer->end();

        isInGame = false;
    }

    gTextWriter->endDraw();

    al::executeDraw(curSequence->mLytKit, "２Ｄバック（メイン画面）");
}

void sendShinePacket(GameDataHolderAccessor thisPtr, Shine* curShine) {
    if (!curShine->isGot()) {
        GameDataFile::HintInfo* curHintInfo = &thisPtr.mData->mGameDataFile->mShineHintList[curShine->mShineIdx];

        Client::sendShineCollectPacket(curHintInfo->mUniqueID);
    }

    GameDataFunction::setGotShine(thisPtr, curShine->curShineInfo);
}

void stageInitHook(
    al::ActorInitInfo* info,
    StageScene* curScene,
    al::PlacementInfo const* placement,
    al::LayoutInitInfo const* lytInfo,
    al::ActorFactory const* factory,
    al::SceneMsgCtrl* sceneMsgCtrl,
    al::GameDataHolderBase* dataHolder
) {
    al::initActorInitInfo(info, curScene, placement, lytInfo, factory, sceneMsgCtrl, dataHolder);

    Client::clearArrays();

    Client::setSceneInfo(*info, curScene);

    if (GameModeManager::instance()->getGameMode() != NONE) {
        GameModeInitInfo initModeInfo(info, curScene);
        initModeInfo.initServerInfo(GameModeManager::instance()->getNextGameMode(), Client::getPuppetHolder());

        GameModeManager::instance()->initScene(initModeInfo);
    }

    Client::sendGameInfPacket(info->mActorSceneInfo.mSceneObjHolder);
}

PlayerCostumeInfo* setPlayerModel(
    al::LiveActor* player,
    const al::ActorInitInfo& initInfo,
    const char* bodyModel,
    const char* capModel,
    al::AudioKeeper* keeper,
    bool isCloset
) {
    Client::sendCostumeInfPacket(bodyModel, capModel);
    return PlayerFunction::initMarioModelActor(player, initInfo, bodyModel, capModel, keeper, isCloset);
}

al::SequenceInitInfo* initInfo;

ulong constructHook() { // hook for constructing anything we need to globally be accesible
    asm("STR X21, [X19,#0x208]"); // stores WorldResourceLoader into HakoniwaSequence

    asm("MOV %[result], X20" : [result] "=r"(initInfo)); // Save our scenes init info to a gloabl ptr so we can access it later

    Client::createInstance(al::getCurrentHeap());
    GameModeManager::createInstance(al::getCurrentHeap()); // Create the GameModeManager on the current al heap

    return 0x20;
}

bool threadInit(HakoniwaSequence* mainSeq) { // hook for initializing client class
    al::LayoutInitInfo lytInfo = al::LayoutInitInfo();

    al::initLayoutInitInfo(
        &lytInfo,
        mainSeq->mLytKit,
        0,
        mainSeq->mAudioDirector,
        initInfo->mSystemInfo->mLayoutSys,
        initInfo->mSystemInfo->mMessageSys,
        initInfo->mSystemInfo->mGamePadSys
    );

    Client::instance()->init(lytInfo, mainSeq->mGameDataHolder);

    return GameDataFunction::isPlayDemoOpening(mainSeq->mGameDataHolder);
}

bool hakoniwaSequenceHook(HakoniwaSequence* sequence) {
    StageScene* stageScene = (StageScene*)sequence->curScene;

    bool isFirstStep = al::isFirstStep(sequence);

    al::PlayerHolder* pHolder    = al::getScenePlayerHolder(stageScene);
    PlayerActorBase*  playerBase = al::tryGetPlayerActor(pHolder, 0);

    bool isYukimaru = !playerBase->getPlayerInfo();

    isInGame = !stageScene->isPause();

    GameModeManager::instance()->setPaused(stageScene->isPause());
    Client::setStageInfo(stageScene->mHolder);

    Client::update();

    updatePlayerInfo(stageScene->mHolder, playerBase, isYukimaru);

    static bool isDisableMusic = false;

    if (al::isPadHoldZR(-1)) {
        if (al::isPadTriggerUp(-1)) { // ZR + Up => Debug menu
            debugMode = !debugMode;
        }
        if (debugMode) {
            if (al::isPadTriggerLeft(-1)) { // [Debug menu] ZR + Left => Previous page
                pageIndex--;
                if (pageIndex < 0) {
                    pageIndex = maxPages - 1;
                }
            }
            if (al::isPadTriggerRight(-1)) { // [Debug menu] ZR + Right => Next page
                pageIndex++;
                if (pageIndex >= maxPages) {
                    pageIndex = 0;
                }
            }
        }
    } else if (al::isPadHoldZL(-1)) {
        if (debugMode && pageIndex == 0) {
            if (al::isPadTriggerLeft(-1)) { // [Debug menu] ZL + Left => Previous player
                debugPuppetIndex--;
                if (debugPuppetIndex < 0) {
                    debugPuppetIndex = Client::getMaxPlayerCount() - 1;
                }
            }
            if (al::isPadTriggerRight(-1)) { // [Debug menu] ZL + Right => Next player
                debugPuppetIndex++;
                if (debugPuppetIndex >= Client::getMaxPlayerCount()) {
                    debugPuppetIndex = 0;
                }
            }
        }
    } else if (al::isPadHoldL(-1)) {
        if (al::isPadTriggerLeft(-1)) { // L + Left => Activate gamemode
            GameModeManager::instance()->toggleActive();
        }
        if (al::isPadTriggerUp(-1)) { // L + Up => Disable background music
            isDisableMusic = !isDisableMusic;
        }
    }

    if (isDisableMusic) {
        if (al::isPlayingBgm(stageScene)) {
            al::stopAllBgm(stageScene, 0);
        }
    }

    if (isFirstStep) {
        GameModeBase* mode = GameModeManager::instance()->getMode<GameModeBase>();
        if (mode) {
            mode->onHakoniwaSequenceFirstStep(sequence);
        }
    }

    return isFirstStep;
}

void seadPrintHook(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    Logger::log(fmt, args);

    va_end(args);
}
