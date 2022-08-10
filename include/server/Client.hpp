/**
 * @file server/Client.hpp
 * @author CraftyBoss (https://github.com/CraftyBoss)
 * @brief main class responsible for handing all client-server related communications, as well as any gamemodes.
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "Keyboard.hpp"
#include "al/actor/ActorInitInfo.h"
#include "al/actor/ActorSceneInfo.h"
#include "al/async/AsyncFunctorThread.h"
#include "al/async/FunctorV0M.hpp"
#include "al/LiveActor/LiveActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/layout/WindowConfirmWait.h"
#include "al/util.hpp"
#include "al/layout/LayoutActor.h"
#include "al/gamepad/util.h"
#include "al/camera/CameraPoser.h"
#include "al/camera/alCameraPoserFunction.h"

#include "container/seadPtrArray.h"
#include "game/Actors/Shine.h"
#include "game/GameData/GameDataHolderAccessor.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"
#include "game/Layouts/CoinCounter.h"
#include "game/Player/PlayerFunction.h"
#include "game/GameData/GameDataHolderWriter.h"
#include "game/GameData/GameDataFunction.h"

#include "heap/seadFrameHeap.h"
#include "heap/seadHeap.h"
#include "layouts/HideAndSeekIcon.h"
#include "rs/util.hpp"

#include "sead/heap/seadDisposer.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "sead/prim/seadSafeString.h"
#include "sead/prim/seadSafeString.hpp"
#include "sead/gfx/seadCamera.h"
#include "sead/basis/seadNew.h"
#include "sead/container/seadSafeArray.h"
#include "sead/thread/seadMutex.h"

#include "nn/account.h"

#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeConfigMenu.hpp"
#include "server/gamemode/GameModeInfoBase.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "types.h"

#include "logger.hpp"
#include "server/SocketClient.hpp"
#include "helpers.hpp"
#include "puppets/HackModelHolder.hpp"
#include "puppets/PuppetHolder.hpp"
#include "syssocket/sockdefines.h"
#include "debugMenu.hpp"
#include "Keyboard.hpp"

#include "puppets/PuppetInfo.h"

#include <stdlib.h>

#define MAXPUPINDEX 32

struct UIDIndexNode {
    nn::account::Uid uid;
    int puppetIndex;
};

class HideAndSeekIcon;

class Client {
    SEAD_SINGLETON_DISPOSER(Client)

    public:
        Client();

        void init(al::LayoutInitInfo const &initInfo, GameDataHolderAccessor holder);

        bool StartThreads();
        void readFunc();
        void recvFunc();
        static void restartConnection();

        bool isDone() { return mReadThread->isDone(); };
        static bool isSocketActive() { return sInstance ? sInstance->mSocket->isConnected() : false; };
        bool isPlayerConnected(int index) { return mPuppetInfoArr[index]->isConnected; }
        static bool isNeedUpdateShines();
        bool isShineCollected(int shineId);

        static void sendHackCapInfPacket(const HackCap *hackCap);
        static void sendPlayerInfPacket(const PlayerActorBase *player, bool isYukimaru);
        static void sendGameInfPacket(const PlayerActorHakoniwa *player, GameDataHolderAccessor holder);
        static void sendGameInfPacket(GameDataHolderAccessor holder);
        static void sendCostumeInfPacket(const char *body, const char *cap);
        static void sendShineCollectPacket(int shineId);
        static void sendTagInfPacket();
        static void sendCaptureInfPacket(const PlayerActorHakoniwa *player);

        int getCollectedShinesCount() { return curCollectedShines.size(); }
        int getShineID(int index) { if (index < curCollectedShines.size()) { return curCollectedShines[index]; } return -1; }

        static void setStageInfo(GameDataHolderAccessor holder);

        static bool tryAddPuppet(PuppetActor *puppet);

        static bool tryAddDebugPuppet(PuppetActor* puppet);

        static const char *getClientName() { return sInstance ? sInstance->mUsername.cstr() : "Player"; }

        static PuppetActor *getPuppet(int idx);

        static PuppetInfo *getPuppetInfo(int idx);

        static PuppetInfo *getLatestInfo();

        static PuppetInfo *getDebugPuppetInfo();

        static PuppetActor* getDebugPuppet();

        static int getMaxPlayerCount() { return sInstance ? sInstance->maxPuppets + 1 : 10;}

        static void updateStates();

        static void clearArrays();

        static Keyboard* getKeyboard();

        static const char* getCurrentIP();

        static void setLastUsedIP(const char* ip);

        static const int getCurrentPort();

        static void setLastUsedPort(const int port);

        static void setTagState(bool state);

        static int getConnectCount() {
            if (sInstance)
                return sInstance->mConnectCount;
            return 0;
        }

        static PuppetHolder* getPuppetHolder() {
            if (sInstance)
                return sInstance->mPuppetHolder;
            return nullptr;
        }

        static void setSceneInfo(const al::ActorInitInfo& initInfo, const StageScene *stageScene);

        static bool tryRegisterShine(Shine* shine);

        static Shine* findStageShine(int shineID);

        static void updateShines();

        static bool openKeyboardIP();
        static bool openKeyboardPort();

        static void showConnect();

        static void showConnectError(const char16_t* msg);

        static void hideConnect();

        void resetCollectedShines();

        void removeShine(int shineId);

        // public for debug purposes
        SocketClient *mSocket;

    private:
        void updatePlayerInfo(PlayerInf *packet);
        void updateHackCapInfo(HackCapInf *packet);
        void updateGameInfo(GameInf *packet);
        void updateCostumeInfo(CostumeInf *packet);
        void updateShineInfo(ShineCollect *packet);
        void updatePlayerConnect(PlayerConnect *packet);
        void updateTagInfo(TagInf *packet);
        void updateCaptureInfo(CaptureInf* packet);
        void sendToStage(ChangeStagePacket* packet);
        void disconnectPlayer(PlayerDC *packet);

        PuppetInfo* findPuppetInfo(const nn::account::Uid& id, bool isFindAvailable);

        bool startConnection();

        // --- General Server Members ---

        // currently, only readThread is used to recieve and update PuppetInfo, while the main game thread is used to send packets without queueing them up first, which might cause performance issues
        al::AsyncFunctorThread *mReadThread = nullptr;    // TODO: use this thread to send any queued packets
        // al::AsyncFunctorThread *mRecvThread; // TODO: use this thread to recieve packets and update PuppetInfo
        
        int mConnectCount = 0;

        nn::account::Uid mUserID;

        sead::FixedSafeString<0x20> mUsername;

        bool mIsConnectionActive = false;

        // --- Server Syncing Members --- 
        
        // array of shine IDs for checking if multiple shines have been collected in quick sucession, all moons within the players stage that match the ID will be deleted
        sead::SafeArray<int, 128> curCollectedShines;
        int collectedShineCount = 0;

        int lastCollectedShine = -1;

        // Backups for our last player/game packets, used for example to re-send them for newly connected clients
        PlayerInf lastPlayerInfPacket = PlayerInf();
        GameInf lastGameInfPacket = GameInf();
        CostumeInf lastCostumeInfPacket = CostumeInf();

        Keyboard* mKeyboard = nullptr; // keyboard for setting server IP

        hostname mServerIP;

        int mServerPort = 0;

        bool waitForGameInit = true;
        bool isFirstConnect = true;

        // --- Game Layouts ---

        al::WindowConfirmWait* mConnectionWait;

        // --- Game Info ---

        bool isClientCaptured = false;

        bool isSentCaptureInf = false;

        bool isSentHackInf = false;

        al::ActorSceneInfo*
            mSceneInfo  = nullptr;  // TODO: create custom scene info class with only the info we actually need

        const StageScene *mCurStageScene = nullptr;

        sead::PtrArray<Shine> mShineArray;  // List of all Shines currently in a Stage

        sead::FixedSafeString<0x40> mStageName;

        GameDataHolderAccessor mHolder;

        u8 mScenario = 0;

        sead::FrameHeap *mHeap = nullptr; // Custom FrameHeap used for all Client related memory

        // --- Puppet Info ---

        int maxPuppets = 9;  // default max player count is 10, so default max puppets will be 9
        
        PuppetInfo *mPuppetInfoArr[MAXPUPINDEX] = {};

        PuppetHolder *mPuppetHolder = nullptr;

        PuppetInfo mDebugPuppetInfo;
};
