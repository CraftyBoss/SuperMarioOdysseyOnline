#include "server/Client.hpp"
#include <cmath>
#include <cstring>
#include "al/actor/ActorSceneInfo.h"
#include "al/layout/WindowConfirmWait.h"
#include "al/util/ControllerUtil.h"
#include "al/util/LiveActorUtil.h"
#include "algorithms/PlayerAnims.h"
#include "game/GameData/GameDataFunction.h"
#include "game/GameData/GameDataHolderAccessor.h"
#include "game/Info/QuestInfo.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/SaveData/SaveDataAccessFunction.h"
#include "game/StageScene/StageScene.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"
#include "heap/seadFrameHeap.h"
#include "heap/seadHeapMgr.h"
#include "helpers.hpp"
#include "layouts/HideAndSeekIcon.h"
#include "logger.hpp"
#include "math/seadVector.h"
#include "nn/err.h"
#include "nn/result.h"
#include "nn/swkbd/swkbd.h"
#include "nn/util.h"
#include "packets/ChangeStagePacket.h"
#include "packets/InitPacket.h"
#include "packets/Packet.h"
#include "packets/PlayerConnect.h"
#include "packets/PlayerDC.h"
#include "packets/TagInf.h"
#include "puppets/PuppetInfo.h"
#include "sead/basis/seadRawPrint.h"
#include "sead/math/seadQuat.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeManager.hpp"
#include "server/hns/HideAndSeekConfigMenu.hpp"
#include "server/hns/HideAndSeekMode.hpp"

SEAD_SINGLETON_DISPOSER_IMPL(Client)

typedef void (Client::*ClientThreadFunc)(void);

/**
 * @brief Construct a new Client:: Client object
 * 
 * @param bufferSize defines the maximum amount of puppets the client can handle
 */
Client::Client() {

    mHeap = sead::FrameHeap::create(0x100000, "ClientHeap", sead::HeapMgr::instance()->getCurrentHeap(), 8, sead::Heap::cHeapDirection_Forward, false);

    sead::ScopedCurrentHeapSetter heapSetter(mHeap); // every new call after this will use ClientHeap instead of SequenceHeap

    this->mReadThread = new al::AsyncFunctorThread("ClientReadThread", al::FunctorV0M<Client*, ClientThreadFunc>(this, &Client::readFunc), 0, 0x10000, {0});

    mKeyboard = new Keyboard(nn::swkbd::GetRequiredStringBufferSize());

    mSocket = new SocketClient("SocketClient");
    
    mPuppetHolder = new PuppetHolder(maxPuppets);

    for (size_t i = 0; i < MAXPUPINDEX; i++)
    {
        mPuppetInfoArr[i] = new PuppetInfo();

        sprintf(mPuppetInfoArr[i]->puppetName, "Puppet%zu", i);
    }

    strcpy(mDebugPuppetInfo.puppetName, "PuppetDebug");

    mConnectCount = 0;

    curCollectedShines.fill(-1);

    collectedShineCount = 0;

    mShineArray.allocBuffer(100, nullptr); // max of 100 shine actors in buffer

    nn::account::GetLastOpenedUser(&mUserID);

    nn::account::Nickname playerName;
    nn::account::GetNickname(&playerName, mUserID);
    Logger::setLogName(playerName.name);  // set Debug logger name to player name

    mUsername = playerName.name;
    
    mUserID.print();

    Logger::log("Player Name: %s\n", playerName.name);

    Logger::log("%s Build Number: %s\n", playerName.name, TOSTRING(BUILDVERSTR));

}

/**
 * @brief initializes client class using initInfo obtained from StageScene::init
 * 
 * @param initInfo init info used to create layouts used by client
 */
void Client::init(al::LayoutInitInfo const &initInfo, GameDataHolderAccessor holder) {

    mConnectionWait = new (mHeap) al::WindowConfirmWait("ServerWaitConnect", "WindowConfirmWait", initInfo);

    mConnectionWait->setTxtMessage(u"Connecting to Server.");

    mConnectionWait->setTxtMessageConfirm(u"Failed to Connect!");

    mHolder = holder;

    StartThreads();

    Logger::log("Remaining Heap Size: %d\n", mHeap->getFreeSize());

}

/**
 * @brief starts client read thread
 * 
 * @return true if read thread was sucessfully started
 * @return false if read thread was unable to start, or thread was already started.
 */
bool Client::StartThreads() {
    if(this->mReadThread->isDone()) { // && this->recvThread->isDone()) {
        this->mReadThread->start();
        //this->recvThread->start();
        Logger::log("Threads Sucessfully Started.\n");
        return true;
    }else {
        Logger::log("Thread(s) has/have already started! Or other unknown reason.\n");
        return false;
    }
}
/**
 * @brief restarts currently active connection to server
 * 
 */
void Client::restartConnection() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return;
    }

    Logger::log("Sending Disconnect.\n");

    PlayerDC playerDC = PlayerDC();

    playerDC.mUserID = sInstance->mUserID;

    sInstance->mSocket->SEND(&playerDC);

    if (sInstance->mSocket->closeSocket()) {
        Logger::log("Sucessfully Closed Socket.\n");
    }

    sInstance->mConnectCount = 0;

    sInstance->mIsConnectionActive = sInstance->mSocket->init(sInstance->mServerIP.cstr(), sInstance->mServerPort).isSuccess();

    if(sInstance->mSocket->getLogState() == SOCKET_LOG_CONNECTED) {

        Logger::log("Reconnect Sucessful!\n");

        PlayerConnect initPacket;
        initPacket.mUserID = sInstance->mUserID;
        strcpy(initPacket.clientName, sInstance->mUsername.cstr());

        initPacket.conType = ConnectionTypes::INIT;

        sInstance->mSocket->SEND(&initPacket);

    } else {
        Logger::log("Reconnect Unsuccessful.\n");
    }
}
/**
 * @brief starts a connection using client's TCP socket class, pulling up the software keyboard for user inputted IP if save file does not have one saved.
 * 
 * @return true if successful connection to server
 * @return false if connection was unable to establish
 */
bool Client::startConnection() {

    bool isNeedSave = false;

    bool isOverride = al::isPadHoldZL(-1);

    if (mServerIP.isEmpty() || isOverride) {
        mKeyboard->setHeaderText(u"Save File does not contain an IP!");
        mKeyboard->setSubText(u"Please set a Server IP Below.");
        mServerIP = "127.0.0.1";
        Client::openKeyboardIP();
        isNeedSave = true;
    }

    if (!mServerPort || isOverride) {
        mKeyboard->setHeaderText(u"Save File does not contain a port!");
        mKeyboard->setSubText(u"Please set a Server Port Below.");
        mServerPort = 1027;
        Client::openKeyboardPort();
        isNeedSave = true;
    }

    if (isNeedSave) {
        SaveDataAccessFunction::startSaveDataWrite(mHolder.mData);
    }

    mIsConnectionActive = mSocket->init(mServerIP.cstr(), mServerPort).isSuccess();

    if (mIsConnectionActive) {

        Logger::log("Sucessful Connection. Waiting to recieve init packet.\n");

        bool waitingForInitPacket = true;
        // wait for client init packet
        while (waitingForInitPacket) {
            if (mSocket->RECV()) {
                if(!mSocket->mPacketQueue.isEmpty()){

                    Packet* curPacket = mSocket->mPacketQueue.popFront();

                    if (curPacket->mType == PacketType::CLIENTINIT) {
                        InitPacket* initPacket = (InitPacket*)curPacket;

                        Logger::log("Server Max Player Size: %d\n", initPacket->maxPlayers);

                        maxPuppets = initPacket->maxPlayers - 1;
                    } else {
                        Logger::log("First Packet was not Init!\n");
                        mIsConnectionActive = false;
                    }

                    free(curPacket);
                    waitingForInitPacket = false;
                }

            } else {
                Logger::log("Recieve failed! Stopping Connection.\n");
                mIsConnectionActive = false;
                waitingForInitPacket = false;
            }
        }
    }

    return mIsConnectionActive;
}

/**
 * @brief Opens up OS's software keyboard in order to change the currently used server IP.
 * @returns whether or not a new IP has been defined and needs to be saved.
 */
bool Client::openKeyboardIP() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return false;
    }

    // opens swkbd with the initial text set to the last saved IP
    sInstance->mKeyboard->openKeyboard(
        sInstance->mServerIP.cstr(), [](nn::swkbd::KeyboardConfig& config) {
            config.keyboardMode = nn::swkbd::KeyboardMode::ModeASCII;
            config.textMaxLength = MAX_HOSTNAME_LENGTH;
            config.textMinLength = 1;
            config.isUseUtf8 = true;
            config.inputFormMode = nn::swkbd::InputFormMode::OneLine;
        });

    hostname prevIp = sInstance->mServerIP;

    while (true) {
        if (sInstance->mKeyboard->isThreadDone()) {
            if(!sInstance->mKeyboard->isKeyboardCancelled())
                sInstance->mServerIP = sInstance->mKeyboard->getResult();
            break;
        }
        nn::os::YieldThread(); // allow other threads to run
    }

    sInstance->isFirstConnect = prevIp != sInstance->mServerIP;

    return sInstance->isFirstConnect;
}

/**
 * @brief Opens up OS's software keyboard in order to change the currently used server port.
 * @returns whether or not a new port has been defined and needs to be saved.
 */
bool Client::openKeyboardPort() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return false;
    }

    // opens swkbd with the initial text set to the last saved port
    char buf[6];
    nn::util::SNPrintf(buf, 6, "%u", sInstance->mServerPort);

    sInstance->mKeyboard->openKeyboard(buf, [](nn::swkbd::KeyboardConfig& config) {
        config.keyboardMode = nn::swkbd::KeyboardMode::ModeNumeric;
        config.textMaxLength = 5;
        config.textMinLength = 2;
        config.isUseUtf8 = true;
        config.inputFormMode = nn::swkbd::InputFormMode::OneLine;
    });

    int prevPort = sInstance->mServerPort;

    while (true) {
        if (sInstance->mKeyboard->isThreadDone()) {
            if(!sInstance->mKeyboard->isKeyboardCancelled())
                sInstance->mServerPort = ::atoi(sInstance->mKeyboard->getResult());
            break;
        }
        nn::os::YieldThread(); // allow other threads to run
    }

    sInstance->isFirstConnect = prevPort != sInstance->mServerPort;

    return sInstance->isFirstConnect;
}

/**
 * @brief main thread function for read thread, responsible for receiving and processing packets from server
 * 
 */
void Client::readFunc() {

    if (waitForGameInit) {
        nn::os::YieldThread(); // sleep the thread for the first thing we do so that game init can finish
        nn::os::SleepThread(nn::TimeSpan::FromSeconds(2));
        waitForGameInit = false;
    }

    // we can use the start of readFunc to display an al::WindowConfirmWait while the client
    // connects

    mConnectionWait->appear();

    mConnectionWait->playLoop();

    if (!startConnection()) {

        Logger::log("Failed to Connect to Server.\n");

        al::hidePane(mConnectionWait, "Page01"); // hide A button prompt since connection message automatically hides after 0.25 seconds

        al::startAction(mConnectionWait, "Confirm", "State");

        nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(250000000)); // sleep active thread for 0.25 seconds

        mConnectionWait->tryEnd();
        
        return;
    }

    PlayerConnect initPacket;
    initPacket.mUserID = mUserID;
    strcpy(initPacket.clientName, mUsername.cstr());

    if (isFirstConnect) {
        initPacket.conType = ConnectionTypes::INIT;
        isFirstConnect = false;
    } else {
        initPacket.conType = ConnectionTypes::RECONNECT;
    }

    mSocket->SEND(&initPacket);  // send initial packet
    
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(500000000)); // sleep for 0.5 seconds to let connection layout fully show (probably should find a better way to do this)

    mConnectionWait->tryEnd();

    while(mIsConnectionActive) {

        if (mSocket->getLogState() != SOCKET_LOG_CONNECTED) {
            
            if (!mConnectionWait->mIsAlive) {
                
                mConnectionWait->appear();

                mConnectionWait->playLoop();
            }
            
            // if we ever disconnect, reset all our values until we reconnect

            mConnectCount = 0;

            if (mSocket->init(mServerIP.cstr(), mServerPort).isSuccess()) {

                Logger::log("Connected!\n");

                if (isFirstConnect) {
                    initPacket.conType =
                        ConnectionTypes::INIT;  // if we've changed the IP/Port since last connect,
                                                // send init instead of reconnect
                    isFirstConnect = false;
                } else {
                    initPacket.conType = ConnectionTypes::RECONNECT;
                }

                mSocket->SEND(&initPacket);
                mConnectionWait->tryEnd();
                continue;
            } else {
                Logger::log("%s: not reconnected\n", __func__);
            }

            nn::os::YieldThread(); // if we're currently waiting on the socket to be initialized, wait until it is
            nn::os::SleepThread(nn::TimeSpan::FromSeconds(5));
        }

        if(mSocket->RECV()) { // will block until a packet has been recieved, or socket disconnected

            while(!mSocket->mPacketQueue.isEmpty()) {

                Packet *curPacket = mSocket->mPacketQueue.popFront();

                switch (curPacket->mType)
                {
                case PacketType::PLAYERINF:
                    updatePlayerInfo((PlayerInf*)curPacket);
                    break;
                case PacketType::GAMEINF:
                    updateGameInfo((GameInf*)curPacket);
                    break;
                case PacketType::HACKCAPINF:
                    updateHackCapInfo((HackCapInf *)curPacket);
                    break;
                case PacketType::CAPTUREINF:                    
                    updateCaptureInfo((CaptureInf*)curPacket);
                    break;
                case PacketType::PLAYERCON:
                    updatePlayerConnect((PlayerConnect*)curPacket);

                    // Send relevant info packets when another client is connected

                    // Assume game packets are empty from first connection
                    if (lastGameInfPacket.mUserID != mUserID)
                        lastGameInfPacket.mUserID = mUserID;
                    mSocket->SEND(&lastGameInfPacket);

                    // No need to send player/costume packets if they're empty
                    if (lastPlayerInfPacket.mUserID == mUserID)
                        mSocket->SEND(&lastPlayerInfPacket);
                    if (lastCostumeInfPacket.mUserID == mUserID)
                        mSocket->SEND(&lastCostumeInfPacket);

                    break;
                case PacketType::COSTUMEINF:
                    updateCostumeInfo((CostumeInf*)curPacket);
                    break;
                case PacketType::SHINECOLL:
                    updateShineInfo((ShineCollect*)curPacket);
                    break;
                case PacketType::PLAYERDC:
                    Logger::log("Received Player Disconnect!\n");
                    curPacket->mUserID.print();
                    disconnectPlayer((PlayerDC*)curPacket);
                    break;
                case PacketType::TAGINF:
                    updateTagInfo((TagInf*)curPacket);
                    break;
                case PacketType::CHANGESTAGE:
                    sendToStage((ChangeStagePacket*)curPacket);
                    break;
                case PacketType::CLIENTINIT: {
                    InitPacket* initPacket = (InitPacket*)curPacket;
                    Logger::log("Server Max Player Size: %d\n", initPacket->maxPlayers);
                    maxPuppets = initPacket->maxPlayers - 1;
                    break;
                }
                default:
                    break;
                }

                free(curPacket);

            }

        }else { // if false, socket has errored or disconnected, so close the socket and end this thread.
            Logger::log("Client Socket Encountered an Error! Errno: 0x%x\n", mSocket->socket_errno);
        }

        nn::os::YieldThread(); // allow other threads to run
    }

    Logger::log("Client Read Thread ending.\n");
}
/**
 * @brief unused thread function for receiving thread
 * 
 */
void Client::recvFunc() {}

/**
 * @brief sends player info packet to current server
 * 
 * @param player pointer to current player class, used to get translation, animation, and capture data
 */
void Client::sendPlayerInfPacket(const PlayerActorBase *playerBase, bool isYukimaru) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    if(!playerBase) {
        Logger::log("Error: Null Player Reference\n");
        return;
    }

    PlayerInf packet = PlayerInf();
    packet.mUserID = sInstance->mUserID;

    packet.playerPos = al::getTrans(playerBase);

    al::calcQuat(&packet.playerRot,
                 playerBase);  // calculate rotation based off pose instead of using quat rotation

    if (!isYukimaru) { 
        
        PlayerActorHakoniwa* player = (PlayerActorHakoniwa*)playerBase;

        for (size_t i = 0; i < 6; i++)
        {
            packet.animBlendWeights[i] = player->mPlayerAnimator->getBlendWeight(i);
        }

        const char *hackName = player->mHackKeeper->getCurrentHackName();

        if (hackName != nullptr) {

            sInstance->isClientCaptured = true;

            const char* actName = al::getActionName(player->mHackKeeper->currentHackActor);

            if (actName) {
                packet.actName = PlayerAnims::FindType(actName);
                packet.subActName = PlayerAnims::Type::Unknown;
                //strcpy(packet.actName, actName); 
            } else {
                packet.actName = PlayerAnims::Type::Unknown;
                packet.subActName = PlayerAnims::Type::Unknown;
            }
        } else {
            packet.actName = PlayerAnims::FindType(player->mPlayerAnimator->mAnimFrameCtrl->getActionName());
            packet.subActName = PlayerAnims::FindType(player->mPlayerAnimator->curSubAnim.cstr());

            sInstance->isClientCaptured = false;
        }

    } else {

        // TODO: implement YukimaruRacePlayer syncing
        
        for (size_t i = 0; i < 6; i++)
        {
            packet.animBlendWeights[i] = 0;
        }

        sInstance->isClientCaptured = false;

        packet.actName = PlayerAnims::Type::Unknown;
        packet.subActName = PlayerAnims::Type::Unknown;
    }

    if(sInstance->lastPlayerInfPacket != packet) {
        sInstance->mSocket->SEND(&packet);
    }

    sInstance->lastPlayerInfPacket = packet;

}
/**
 * @brief sends info related to player's cap actor to server
 * 
 * @param hackCap pointer to cap actor, used to get translation, animation, and state info
 */
void Client::sendHackCapInfPacket(const HackCap* hackCap) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    bool isFlying = hackCap->isFlying();

    // if cap is in flying state, send packet as often as this function is called
    if (isFlying) {
        HackCapInf packet = HackCapInf();
        packet.mUserID = sInstance->mUserID;
        packet.capPos = al::getTrans(hackCap);

        packet.isCapVisible = isFlying;

        packet.capQuat.x = hackCap->mJointKeeper->mJointRot.x;
        packet.capQuat.y = hackCap->mJointKeeper->mJointRot.y;
        packet.capQuat.z = hackCap->mJointKeeper->mJointRot.z;
        packet.capQuat.w = hackCap->mJointKeeper->mSkew;

        strcpy(packet.capAnim, al::getActionName(hackCap));

        sInstance->mSocket->SEND(&packet);

        sInstance->isSentHackInf = true;

    } else if (sInstance->isSentHackInf) { // if cap is not flying, check to see if previous function call sent a packet, and if so, send one final packet resetting cap data.
        HackCapInf packet = HackCapInf();
        packet.mUserID = sInstance->mUserID;
        packet.isCapVisible = false;
        packet.capPos = sead::Vector3f::zero;
        packet.capQuat = sead::Quatf::unit;
        sInstance->mSocket->SEND(&packet);
        sInstance->isSentHackInf = false;
    }
}

/**
 * @brief 
 * Sends both stage info and player 2D info to the server.
 * @param player 
 * @param holder 
 */
void Client::sendGameInfPacket(const PlayerActorHakoniwa* player, GameDataHolderAccessor holder) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    GameInf packet = GameInf();
    packet.mUserID = sInstance->mUserID;

    if (player) {
        packet.is2D = player->mDimKeeper->is2DModel;
    } else {
        packet.is2D = false;
    }

    packet.scenarioNo = holder.mData->mGameDataFile->getScenarioNo();

    strcpy(packet.stageName, GameDataFunction::getCurrentStageName(holder));

    if(packet != sInstance->lastGameInfPacket) {
        sInstance->mSocket->SEND(&packet);
    }

    sInstance->lastGameInfPacket = packet;
}
/**
 * @brief 
 * Sends only stage info to the server.
 * @param holder 
 */
void Client::sendGameInfPacket(GameDataHolderAccessor holder) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    GameInf packet = GameInf();
    packet.mUserID = sInstance->mUserID;

    packet.is2D = false;

    packet.scenarioNo = holder.mData->mGameDataFile->getScenarioNo();

    strcpy(packet.stageName, GameDataFunction::getCurrentStageName(holder));

    sInstance->mSocket->SEND(&packet);

    sInstance->lastGameInfPacket = packet;
}

/**
 * @brief 
 * 
 */
void Client::sendTagInfPacket() {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }

    HideAndSeekMode* hsMode = GameModeManager::instance()->getMode<HideAndSeekMode>();

    if (!GameModeManager::instance()->isMode(GameMode::HIDEANDSEEK)) {
        Logger::log("State is not Hide and Seek!\n");
        return;
    }

    HideAndSeekInfo* curInfo = GameModeManager::instance()->getInfo<HideAndSeekInfo>();

    TagInf packet = TagInf();

    packet.mUserID = sInstance->mUserID;

    packet.isIt = hsMode->isPlayerIt();

    packet.minutes = curInfo->mHidingTime.mMinutes;
    packet.seconds = curInfo->mHidingTime.mSeconds;
    packet.updateType = static_cast<TagUpdateType>(TagUpdateType::STATE | TagUpdateType::TIME);

    sInstance->mSocket->SEND(&packet);
}

/**
 * @brief 
 * 
 * @param body 
 * @param cap 
 */
void Client::sendCostumeInfPacket(const char* body, const char* cap) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    CostumeInf packet = CostumeInf(body, cap);
    packet.mUserID = sInstance->mUserID;
    sInstance->mSocket->SEND(&packet);
    sInstance->lastCostumeInfPacket = packet;
}

/**
 * @brief 
 * 
 * @param player 
 */
void Client::sendCaptureInfPacket(const PlayerActorHakoniwa* player) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    if (sInstance->isClientCaptured && !sInstance->isSentCaptureInf) {
        CaptureInf packet = CaptureInf();
        packet.mUserID = sInstance->mUserID;
        strcpy(packet.hackName, tryConvertName(player->mHackKeeper->getCurrentHackName()));
        sInstance->mSocket->SEND(&packet);
        sInstance->isSentCaptureInf = true;
    } else if (!sInstance->isClientCaptured && sInstance->isSentCaptureInf) {
        CaptureInf packet = CaptureInf();
        packet.mUserID = sInstance->mUserID;
        strcpy(packet.hackName, "");
        sInstance->mSocket->SEND(&packet);
        sInstance->isSentCaptureInf = false;
    }
}

/**
 * @brief 
 * 
 * @param shineID 
 */
void Client::sendShineCollectPacket(int shineID) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }

    if(sInstance->lastCollectedShine != shineID) {
        ShineCollect packet = ShineCollect();
        packet.mUserID = sInstance->mUserID;
        packet.shineId = shineID;

        sInstance->lastCollectedShine = shineID;

        sInstance->mSocket->SEND(&packet);
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updatePlayerInfo(PlayerInf *packet) {

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (!curInfo) {
        return;
    }

    if(!curInfo->isConnected) {
        curInfo->isConnected = true;
    }

    curInfo->playerPos = packet->playerPos;

    // check if rotation is larger than zero and less than or equal to 1
    if(abs(packet->playerRot.x) > 0.f || abs(packet->playerRot.y) > 0.f || abs(packet->playerRot.z) > 0.f || abs(packet->playerRot.w) > 0.f) {
        if(abs(packet->playerRot.x) <= 1.f || abs(packet->playerRot.y) <= 1.f || abs(packet->playerRot.z) <= 1.f || abs(packet->playerRot.w) <= 1.f) {
            curInfo->playerRot = packet->playerRot;
        }
    }

        if (packet->actName != PlayerAnims::Type::Unknown) {
            strcpy(curInfo->curAnimStr, PlayerAnims::FindStr(packet->actName));
            if (curInfo->curAnimStr[0] == '\0')
                Logger::log("[ERROR] %s: actName was out of bounds: %d\n", __func__, packet->actName);
        } else {
            strcpy(curInfo->curAnimStr, "Wait");
        }

        if(packet->subActName != PlayerAnims::Type::Unknown) {
            strcpy(curInfo->curSubAnimStr, PlayerAnims::FindStr(packet->subActName));
            if (curInfo->curSubAnimStr[0] == '\0')
                Logger::log("[ERROR] %s: subActName was out of bounds: %d\n", __func__, packet->subActName);
        } else {
            strcpy(curInfo->curSubAnimStr, "");
        }

    curInfo->curAnim = packet->actName;
    curInfo->curSubAnim = packet->subActName;

    for (size_t i = 0; i < 6; i++)
    {
        // weights can only be between 0 and 1
        if(packet->animBlendWeights[i] >= 0.f && packet->animBlendWeights[i] <= 1.f) {
            curInfo->blendWeights[i] = packet->animBlendWeights[i];
        }
    }

    //TEMP

    if(!curInfo->isCapThrow) {
        curInfo->capPos = packet->playerPos;
    }

}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateHackCapInfo(HackCapInf *packet) {

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (curInfo) {
        curInfo->capPos = packet->capPos;
        curInfo->capRot = packet->capQuat;

        curInfo->isCapThrow = packet->isCapVisible;

        strcpy(curInfo->capAnim, packet->capAnim);
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateCaptureInfo(CaptureInf* packet) {
    
    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);
        
    if (!curInfo) {
        return;
    }

    curInfo->isCaptured = strlen(packet->hackName) > 0;

    if (curInfo->isCaptured) {
        strcpy(curInfo->curHack, packet->hackName);
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateCostumeInfo(CostumeInf *packet) {

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (!curInfo) {
        return;
    }

    strcpy(curInfo->costumeBody, packet->bodyModel);
    strcpy(curInfo->costumeHead, packet->capModel);
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateShineInfo(ShineCollect* packet) {
    if(collectedShineCount < curCollectedShines.size() - 1) {
        curCollectedShines[collectedShineCount] = packet->shineId;
        collectedShineCount++;
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updatePlayerConnect(PlayerConnect* packet) {
    
    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, true);

    if (!curInfo) {
        return;
    }

    if (curInfo->isConnected) {

        Logger::log("Info is already being used by another connected player!\n");
        packet->mUserID.print("Connection ID");
        curInfo->playerID.print("Target Info");

    } else {

        packet->mUserID.print("Player Connected! ID");

        curInfo->playerID = packet->mUserID;
        curInfo->isConnected = true;
        strcpy(curInfo->puppetName, packet->clientName);

        mConnectCount++;
    }
}
/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateGameInfo(GameInf *packet) {

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (!curInfo) {
        return;
    }

    if(curInfo->isConnected) {

        curInfo->scenarioNo = packet->scenarioNo;

        if(strcmp(packet->stageName, "") != 0 && strlen(packet->stageName) > 3) {
            strcpy(curInfo->stageName, packet->stageName);
        }

        curInfo->is2D = packet->is2D;
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateTagInfo(TagInf *packet) {
    
    // if the packet is for our player, edit info for our player
    if (packet->mUserID == mUserID && GameModeManager::instance()->isMode(GameMode::HIDEANDSEEK)) {

        HideAndSeekMode* mMode = GameModeManager::instance()->getMode<HideAndSeekMode>();
        HideAndSeekInfo* curInfo = GameModeManager::instance()->getInfo<HideAndSeekInfo>();

        if (packet->updateType & TagUpdateType::STATE) {
            mMode->setPlayerTagState(packet->isIt);
        }

        if (packet->updateType & TagUpdateType::TIME) {
            curInfo->mHidingTime.mSeconds = packet->seconds;
            curInfo->mHidingTime.mMinutes = packet->minutes;
        }

        return;

    }

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (!curInfo) {
        return;
    }

    curInfo->isIt = packet->isIt;
    curInfo->seconds = packet->seconds;
    curInfo->minutes = packet->minutes;
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::sendToStage(ChangeStagePacket* packet) {
    if (mSceneInfo && mSceneInfo->mSceneObjHolder) {

        GameDataHolderAccessor accessor(mSceneInfo->mSceneObjHolder);

        Logger::log("Sending Player to %s at Entrance %s in Scenario %d\n", packet->changeStage,
                     packet->changeID, packet->scenarioNo);
        
        ChangeStageInfo info(accessor.mData, packet->changeID, packet->changeStage, false, packet->scenarioNo, static_cast<ChangeStageInfo::SubScenarioType>(packet->subScenarioType));
        GameDataFunction::tryChangeNextStage(accessor, &info);
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::disconnectPlayer(PlayerDC *packet) {

    PuppetInfo* curInfo = findPuppetInfo(packet->mUserID, false);

    if (!curInfo || !curInfo->isConnected) {
        return;
    }
    
    curInfo->isConnected = false;

    curInfo->scenarioNo = -1;
    strcpy(curInfo->stageName, "");
    curInfo->isInSameStage = false;

    mConnectCount--;
}

/**
 * @brief 
 * 
 * @param shineId 
 * @return true 
 * @return false 
 */
bool Client::isShineCollected(int shineId) {

    for (size_t i = 0; i < curCollectedShines.size(); i++)
    {
        if(curCollectedShines[i] >= 0) {
            if(curCollectedShines[i] == shineId) {
                return true;
            }
        }
    }
    
    return false;

}

/**
 * @brief 
 * 
 * @param id 
 * @return int 
 */
PuppetInfo* Client::findPuppetInfo(const nn::account::Uid& id, bool isFindAvailable) {

    PuppetInfo *firstAvailable = nullptr;

    for (size_t i = 0; i < getMaxPlayerCount() - 1; i++) {

        PuppetInfo* curInfo = mPuppetInfoArr[i];

        if (curInfo->playerID == id) {
            return curInfo;
        } else if (isFindAvailable && !firstAvailable && !curInfo->isConnected) {
            firstAvailable = curInfo;
        }
    }

    if (!firstAvailable) {
        Logger::log("Unable to find Assigned Puppet for Player!\n");
        id.print("User ID");
    }

    return firstAvailable;
}

/**
 * @brief 
 * 
 * @param holder 
 */
void Client::setStageInfo(GameDataHolderAccessor holder) {
    if (sInstance) {

        sInstance->mStageName = GameDataFunction::getCurrentStageName(holder);
        sInstance->mScenario = holder.mData->mGameDataFile->getScenarioNo(); //holder.mData->mGameDataFile->getMainScenarioNoCurrent();
        
        sInstance->mPuppetHolder->setStageInfo(sInstance->mStageName.cstr(), sInstance->mScenario);
    }
}

/**
 * @brief 
 * 
 * @param puppet 
 * @return true 
 * @return false 
 */
bool Client::tryAddPuppet(PuppetActor *puppet) {
    if(sInstance) {
        return sInstance->mPuppetHolder->tryRegisterPuppet(puppet);
    }else {
        return false;
    }
}

/**
 * @brief 
 * 
 * @param puppet 
 * @return true 
 * @return false 
 */
bool Client::tryAddDebugPuppet(PuppetActor *puppet) {
    if(sInstance) {
        return sInstance->mPuppetHolder->tryRegisterDebugPuppet(puppet);
    }else {
        return false;
    }
}

/**
 * @brief 
 * 
 * @param idx 
 * @return PuppetActor* 
 */
PuppetActor *Client::getPuppet(int idx) {
    if(sInstance) {
        return sInstance->mPuppetHolder->getPuppetActor(idx);
    }else {
        return nullptr;
    }
}

/**
 * @brief 
 * 
 * @return PuppetInfo* 
 */
PuppetInfo *Client::getLatestInfo() {
    if(sInstance) {
        return Client::getPuppetInfo(sInstance->mPuppetHolder->getSize() - 1);
    }else {
        return nullptr;
    }
}

/**
 * @brief 
 * 
 * @param idx 
 * @return PuppetInfo* 
 */
PuppetInfo *Client::getPuppetInfo(int idx) {
    if(sInstance) {
        // unsafe get
        PuppetInfo *curInfo = sInstance->mPuppetInfoArr[idx];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", idx);
            return nullptr;
        }

        return curInfo;
    }else {
        return nullptr;
    }
}

/**
 * @brief 
 * 
 */
void Client::resetCollectedShines() {
    collectedShineCount = 0;
    curCollectedShines.fill(-1);
}

/**
 * @brief 
 * 
 * @param shineId 
 */
void Client::removeShine(int shineId) {
    for (size_t i = 0; i < curCollectedShines.size(); i++)
    {
        if(curCollectedShines[i] == shineId) {
            curCollectedShines[i] = -1;
            collectedShineCount--;
        }
    }
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Client::isNeedUpdateShines() {
    return sInstance ? sInstance->collectedShineCount > 0 : false;
}

/**
 * @brief 
 * 
 */
void Client::updateShines() {
    if (!sInstance) {
        Logger::log("Client Null!\n");
        return;
    }

    // skip shine sync if player is in cap kingdom scenario zero (very start of the game)
    if (sInstance->mStageName == "CapWorldHomeStage" && (sInstance->mScenario == 0 || sInstance->mScenario == 1)) {
        return;
    }

    GameDataHolderAccessor accessor(sInstance->mCurStageScene);
    
    for (size_t i = 0; i < sInstance->getCollectedShinesCount(); i++)
    {
        int shineID = sInstance->getShineID(i);

        if (shineID >= 0) {
            Shine* stageShine = findStageShine(shineID);

            if (!GameDataFunction::isGotShine(accessor, shineID)) {
                if (stageShine) {

                    if (al::isDead(stageShine)) {
                        stageShine->makeActorAlive();
                    }
                    
                    stageShine->getDirect();
                    stageShine->onSwitchGet();

                    accessor.mData->mGameDataFile->setGotShine(shineID);

                    // TODO: add a system for displaying moon get layout when this runs

                } else {
                    accessor.mData->mGameDataFile->setGotShine(shineID);
                }
            }
        }
    }
    
    sInstance->resetCollectedShines();
    sInstance->mCurStageScene->mSceneLayout->startShineCountAnim(false);
}

/**
 * @brief 
 * 
 */
void Client::updateStates() {
    if(sInstance) {
        sInstance->mPuppetHolder->update();

        GameModeManager::instance()->update();
    }
}

/**
 * @brief 
 * 
 */
void Client::clearArrays() {
    if(sInstance) {
        sInstance->mPuppetHolder->clearPuppets();
        sInstance->mShineArray.clear();

    }
}

/**
 * @brief 
 * 
 * @return PuppetInfo* 
 */
PuppetInfo *Client::getDebugPuppetInfo() {
    if(sInstance) {
        return &sInstance->mDebugPuppetInfo;
    }else {
        return nullptr;
    }
}

/**
 * @brief 
 * 
 * @return PuppetActor* 
 */
PuppetActor *Client::getDebugPuppet() {
    if(sInstance) {
        return sInstance->mPuppetHolder->getDebugPuppet();
    }else {
        return nullptr;
    }
}

/**
 * @brief 
 * 
 * @return Keyboard* 
 */
Keyboard* Client::getKeyboard() {
    if (sInstance) {
        return sInstance->mKeyboard;
    }
    return nullptr;
}

/**
 * @brief 
 * 
 * @return const char* 
 */
const char* Client::getCurrentIP() {
    if (sInstance) {
        return sInstance->mServerIP.cstr();
    }
    return nullptr;
}

/**
 * @brief 
 * 
 * @return const int 
 */
const int Client::getCurrentPort() {
    if (sInstance) {
        return sInstance->mServerPort;
    }
    return -1;
}

/**
 * @brief sets server IP to supplied string, used specifically for loading IP from the save file.
 * 
 * @param ip 
 */
void Client::setLastUsedIP(const char* ip) {
    if (sInstance) {
        sInstance->mServerIP = ip;
    }
}

/**
 * @brief sets server port to supplied string, used specifically for loading port from the save file.
 * 
 * @param port 
 */
void Client::setLastUsedPort(const int port) {
    if (sInstance) {
        sInstance->mServerPort = port;
    }
}

/**
 * @brief creates new scene info and copies supplied info to the new info, as well as stores a const ptr to the current stage scene.
 * 
 * @param initInfo 
 * @param stageScene 
 */
void Client::setSceneInfo(const al::ActorInitInfo& initInfo, const StageScene *stageScene) {

    if (!sInstance) {
        Logger::log("Client Null!\n");
        return;
    }

    sInstance->mSceneInfo = new al::ActorSceneInfo();

    memcpy(sInstance->mSceneInfo, &initInfo.mActorSceneInfo, sizeof(al::ActorSceneInfo));

    sInstance->mCurStageScene = stageScene;
}

/**
 * @brief stores shine pointer supplied into a ptr array if space is available, and shine is not collected.
 * 
 * @param shine 
 * @return true if shine was able to be successfully stored
 * @return false if shine is already collected, or ptr array is full
 */
bool Client::tryRegisterShine(Shine* shine) {
    if (sInstance) {
        if (!sInstance->mShineArray.isFull()) {
            if (!shine->isGot()) {
                sInstance->mShineArray.pushBack(shine);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief finds the actor pointer stored in the shine ptr array based off shine ID
 * 
 * @param shineID Unique ID used for shine actor
 * @return Shine* if shine ptr array contains actor with supplied shine ID.
 */
Shine* Client::findStageShine(int shineID) {
    if (sInstance) {
        for (int i = 0; i < sInstance->mShineArray.size(); i++) {
            Shine* curShine = sInstance->mShineArray[i];
            if (curShine) {
                if (curShine->shineId == shineID) {
                    return curShine;
                }
            }
        }
    }
    return nullptr;
}

void Client::showConnectError(const char16_t* msg) {
    if (!sInstance)
        return;

    sInstance->mConnectionWait->setTxtMessageConfirm(msg);

    al::hidePane(sInstance->mConnectionWait, "Page01");  // hide A button prompt

    if (!sInstance->mConnectionWait->mIsAlive) {
        sInstance->mConnectionWait->appear();

        sInstance->mConnectionWait->playLoop();
    }

    al::startAction(sInstance->mConnectionWait, "Confirm", "State");
}

void Client::showConnect() {
    if (!sInstance)
        return;
    
    sInstance->mConnectionWait->appear();

    sInstance->mConnectionWait->playLoop();
    
}

void Client::hideConnect() {
    if (!sInstance)
        return;

    sInstance->mConnectionWait->tryEnd();
}
