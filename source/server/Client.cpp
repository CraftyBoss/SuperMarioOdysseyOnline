#include "server/Client.hpp"
#include <cstring>
#include "al/actor/ActorSceneInfo.h"
#include "al/layout/WindowConfirmWait.h"
#include "al/util/LiveActorUtil.h"
#include "algorithms/PlayerAnims.h"
#include "game/GameData/GameDataFunction.h"
#include "game/GameData/GameDataHolderAccessor.h"
#include "game/Info/QuestInfo.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"
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
#include "packets/TagInf.h"
#include "sead/basis/seadRawPrint.h"
#include "sead/math/seadQuat.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeFactory.hpp"
#include "server/HideAndSeekConfigMenu.hpp"
#include "server/HideAndSeekMode.hpp"

Client* Client::sInstance;

typedef void (Client::*ClientThreadFunc)(void);

/**
 * @brief Construct a new Client:: Client object
 * 
 * @param bufferSize defines the maximum amount of puppets the client can handle
 */
Client::Client(int bufferSize) {
    this->mReadThread = new al::AsyncFunctorThread("ClientReadThread", al::FunctorV0M<Client*, ClientThreadFunc>(this, &Client::readFunc), 0, 0x10000, {0});
    // this->recvThread = new al::AsyncFunctorThread("ClientRecvThread",
    // al::FunctorV0M<typeof(this), typeof(&Client::recvFunc)>(this, &Client::recvFunc), 0, 0x10000,
    // {0});

    mKeyboard = new Keyboard(nn::swkbd::GetRequiredStringBufferSize());

    mSocket = new SocketClient("SocketClient");
    
    maxPuppets = bufferSize - 1;

    mPuppetHolder = new PuppetHolder(maxPuppets);

    for (size_t i = 0; i < bufferSize + 1; i++)
    {
        mPuppetInfoArr[i] = new PuppetInfo();

        sprintf(mPuppetInfoArr[i]->puppetName, "Puppet%zu", i);
    }

    strcpy(mDebugPuppetInfo.puppetName, "PuppetDebug");

    puppetPlayerID.fill({0, 0});

    mConnectCount = 0;

    curCollectedShines.fill(-1);

    collectedShineCount = 0;

    mShineArray.allocBuffer(100, nullptr); // max of 100 shine actors in buffer

    nn::account::GetLastOpenedUser(&mUserID);

    mUserID.print();

    nn::account::Nickname playerName;
    nn::account::GetNickname(&playerName, mUserID);

    mUsername = playerName.name;

    Logger::log("Player Name: %s\n", playerName.name);

    #ifdef BUILDVER
    Logger::log("%s Build Number: %s\n", playerName.name, TOSTRING(BUILDVER));
    #endif

    Logger::setLogName(playerName.name);  // set Debug logger name to player name

    mServerMode = GameMode::HIDEANDSEEK; // temp for testing

    if(!sInstance) {
        sInstance = this;
    }
}

/**
 * @brief initializes client class using initInfo obtained from StageScene::init
 * 
 * @param initInfo init info used to create layouts used by client
 */
void Client::init(al::LayoutInitInfo const &initInfo) {

    mConnectionWait = new al::WindowConfirmWait("ServerWaitConnect", "WindowConfirmWait", initInfo);

    mConnectionWait->setTxtMessage(u"Connecting to Server.");

    mConnectionWait->setTxtMessageConfirm(u"Failed to Connect!");

    StartThreads();

    // mConnectionWait->tryEndForce();
}

/**
 * @brief creates and initializes the gamemode selected by either server or client settings
 * 
 * @param initInfo init info used to initialize gamemode
 */
void Client::initMode(GameModeInitInfo const& initInfo) {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return;
    }

    GameModeInitInfo newInfo = initInfo;

    newInfo.initServerInfo(sInstance->mServerMode, sInstance->mPuppetHolder);

    GameModeFactory modeFactory("GameModeFactory");

    const char* modeName = GameModeFactory::getModeString(newInfo.mMode);

    if (modeName) {
        auto creator = modeFactory.getCreator(modeName);
        if (creator) {
            sInstance->mCurMode = creator(modeName);
        }
    }

    if (sInstance->mCurMode) {
        sInstance->mCurMode->init(newInfo);
    } else {
        Logger::log("Failed to Create Gamemode! Mode: \n", modeName ? modeName : "Unknown");
    }
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
void Client::stopConnection() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return;
    }

    sInstance->mSocket->closeSocket();

    sInstance->puppetPlayerID.fill({0,0});

    sInstance->mConnectCount = 0;

    sInstance->mSocket->init(sInstance->mServerIP.cstr(), sInstance->mServerPort);

    if(sInstance->mSocket->getLogState() == SOCKET_LOG_CONNECTED) {

        Logger::log("Connected!\n");

        PlayerConnect initPacket;
        initPacket.mUserID = sInstance->mUserID;
        strcpy(initPacket.clientName, sInstance->mUsername.cstr());
        initPacket.conType = ConnectionTypes::RECONNECT;
        sInstance->mSocket->SEND(&initPacket);
    }
}
/**
 * @brief starts a connection using client's TCP socket class, pulling up the software keyboard for user inputted IP if save file does not have one saved.
 * 
 * @return true if successful connection to server
 * @return false if connection was unable to establish
 */
bool Client::startConnection() {
    if (mServerIP.isEmpty()) {
        mKeyboard->setHeaderText(u"Save File does not contain an IP!");
        mKeyboard->setSubText(u"Please set a Server IP Below.");
        mServerIP = "0.0.0.0";
        Client::openKeyboardIP();
    }

    if (!mServerPort) {
        mKeyboard->setHeaderText(u"Save File does not contain a port!");
        mKeyboard->setSubText(u"Please set a Server Port Below.");
        mServerPort = 1027;
        Client::openKeyboardPort();
    }

    bool socketConnected = mSocket->isConnected();
    if (!socketConnected) {
        socketConnected = mSocket->init(mServerIP.cstr(), mServerPort).isSuccess();
    }

    bool clientConnected = false;
    if (socketConnected) {
        // wait for client init packet
        while (true) {
            if (mSocket->RECV()) {
                Packet* curPacket = mSocket->mPacketQueue.popFront();

                if (curPacket->mType == PacketType::CLIENTINIT) {
                    InitPacket* initPacket = (InitPacket*)curPacket;

                    Logger::log("Server Max Player Size: %d\n", initPacket->maxPlayers);

                    maxPuppets = initPacket->maxPlayers - 1;

                    clientConnected = true;
                } else {
                    Logger::log("First Packet was not Init!\n");
                    clientConnected = false;
                }

                free(curPacket);
            }

            break;
        }
    }
    
    return clientConnected;
}

/**
 * @brief Opens up OS's software keyboard in order to change the currently used server IP.
 * 
 */
void Client::openKeyboardIP() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return;
    }

    // opens swkbd with the initial text set to the last saved IP
    sInstance->mKeyboard->openKeyboard(sInstance->mServerIP.cstr(), [] (nn::swkbd::KeyboardConfig& config) {
        config.keyboardMode = nn::swkbd::KeyboardMode::ModeNumeric;
        config.leftOptionalSymbolKey = '.';
        config.textMaxLength = 15;
        config.textMinLength = 1;
        config.isUseUtf8 = true;
        config.inputFormMode = nn::swkbd::InputFormMode::OneLine;
    });

    while (true) {
        if (sInstance->mKeyboard->isThreadDone()) {
            sInstance->mServerIP = sInstance->mKeyboard->getResult();
            break;
        }
        nn::os::YieldThread(); // allow other threads to run
    }
}

/**
 * @brief Opens up OS's software keyboard in order to change the currently used server port.
 * 
 */
void Client::openKeyboardPort() {

    if (!sInstance) {
        Logger::log("Static Instance is null!\n");
        return;
    }

    // opens swkbd with the initial text set to the last saved port
    char buf[6];
    nn::util::SNPrintf(buf, 6, "%u", sInstance->mServerPort);
    
    sInstance->mKeyboard->openKeyboard(buf, [] (nn::swkbd::KeyboardConfig& config) {
        config.keyboardMode = nn::swkbd::KeyboardMode::ModeNumeric;
        config.textMaxLength = 5;
        config.textMinLength = 2;
        config.isUseUtf8 = true;
        config.inputFormMode = nn::swkbd::InputFormMode::OneLine;
    });

    while (true) {
        if (sInstance->mKeyboard->isThreadDone()) {
            sInstance->mServerPort = ::atoi(sInstance->mKeyboard->getResult());
            break;
        }
        nn::os::YieldThread(); // allow other threads to run
    }
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

    // we can use the start of readFunc to display an al::WindowConfirmWait while the server
    // connects

    mConnectionWait->appear();

    mConnectionWait->playLoop();

    if (!startConnection()) {

        al::hidePane(mConnectionWait, "Page01"); // hide A button prompt since connection message automatically hides after 0.25 seconds

        al::startAction(mConnectionWait, "Confirm", "State");

        nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(250000000)); // sleep active thread for 0.25 seconds

        mConnectionWait->tryEnd();
        
        return;
    }

    if (isFirstConnect) {
        sead::Heap* seqHeap = sead::HeapMgr::instance()->findHeapByName("SequenceHeap", 0);

        if (seqHeap) {
            Logger::log("Current Heap Name: %s\n", seqHeap->getName().cstr());
        }

        
    }

    PlayerConnect initPacket;
    initPacket.mUserID = mUserID;
    strcpy(initPacket.clientName, mUsername.cstr());

    if (isFirstConnect) {
        initPacket.conType = ConnectionTypes::INIT;
    } else {
        initPacket.conType = ConnectionTypes::RECONNECT;
    }

    mSocket->SEND(&initPacket);  // send initial packet
    
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(500000000)); // sleep for 0.5 seconds to let connection layout fully show (probably should find a better way to do this)

    mConnectionWait->tryEnd();

    isFirstConnect = false;

    while(true) {

        if (mSocket->getLogState() != SOCKET_LOG_CONNECTED) {
            
            if (!mConnectionWait->mIsAlive) {
                
                mConnectionWait->appear();

                mConnectionWait->playLoop();
            }
            
            // if we ever disconnect, reset all our values until we reconnect

            puppetPlayerID.fill({0,0});
            mConnectCount = 0;

            mSocket->closeSocket();

            mSocket->init(mServerIP.cstr(), mServerPort);

            if (mSocket->getLogState() == SOCKET_LOG_CONNECTED) {

                Logger::log("Connected!\n");

                initPacket.conType = ConnectionTypes::RECONNECT;
                mSocket->SEND(&initPacket);  // re-send init packet as reconnect packet
                mConnectionWait->tryEnd();
                continue;
            } else {
                Logger::log("%s: not reconnected\n", __func__);
            }

            nn::os::YieldThread(); // if we're currently waiting on the socket to be initialized, wait until it is
            nn::os::SleepThread(nn::TimeSpan::FromSeconds(5));

            // TODO: if a reconnect is sucessful, we should let the server know that this client has already connected, and that their player ID is already active
            
        }

        if(mSocket->RECV()) { // will block until a packet has been recieved, or socket disconnected

            while(!mSocket->mPacketQueue.isEmpty()) {

                Packet *curPacket = mSocket->mPacketQueue.popFront();

                switch (curPacket->mType)
                {
                case PacketType::PLAYERINF:
                    if(mIsInGame) {
                        updatePlayerInfo((PlayerInf*)curPacket);
                    }
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
            Logger::log("Client Socket Encountered an Error!\n");
        }

        nn::os::YieldThread(); // allow other threads to run
    }
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
void Client::sendPlayerInfPacket(const PlayerActorHakoniwa *player) {

    if (!sInstance) {
        Logger::log("Static Instance is Null!\n");
        return;
    }
    
    if(!player) {
        Logger::log("Error: Null Player Reference\n");
        return;
    }

    PlayerInf packet = PlayerInf();
    packet.mUserID = sInstance->mUserID;

    packet.playerPos = al::getTrans(player);

    al::calcQuat(&packet.playerRot, player); // calculate rotation based off pose instead of using quat rotation

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

        packet.isCapVisible = hackCap->isFlying();

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
 * 
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
 * 
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

    if (sInstance->mServerMode != GameMode::HIDEANDSEEK) {
        Logger::log("State is not Hide and Seek!\n");
        return;
    }

    HideAndSeekMode* hsMode = (HideAndSeekMode*)sInstance->mCurMode;
    HideAndSeekInfo* curInfo = (HideAndSeekInfo*)sInstance->mModeInfo;

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
    
    int puppetIndex = findPuppetID(packet->mUserID);

    if(puppetIndex >= 0) {

        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
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
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateHackCapInfo(HackCapInf *packet) {

    int puppetIndex = findPuppetID(packet->mUserID);

    if(puppetIndex >= 0) {

        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (curInfo) {
            curInfo->capPos = packet->capPos;
            curInfo->capRot = packet->capQuat;

            curInfo->isCapThrow = packet->isCapVisible;

            if (curInfo->capAnim && packet->capAnim) {
                strcpy(curInfo->capAnim, packet->capAnim);
            }
        } else {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
        }
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateCaptureInfo(CaptureInf *packet) {
    int puppetIndex = findPuppetID(packet->mUserID);
    if (puppetIndex >= 0) {
        
        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];
        
        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
            return;
        }

        curInfo->isCaptured = strlen(packet->hackName) > 0;

        if (curInfo->isCaptured) {
            strcpy(curInfo->curHack, packet->hackName);
        }
    }
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateCostumeInfo(CostumeInf *packet) {
    if(packet->bodyModel && packet->capModel) {
        int puppetIndex = findPuppetID(packet->mUserID);
        if(puppetIndex >= 0) {
            PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

            if (!curInfo) {
                Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
                return;
            }

            strcpy(curInfo->costumeBody, packet->bodyModel);
            strcpy(curInfo->costumeHead, packet->capModel);
            
        }
    }
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
void Client::updatePlayerConnect(PlayerConnect *packet) {
    int puppetIndex = findPuppetID(packet->mUserID);
    if(puppetIndex >= 0) {
        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
            return;
        }
        curInfo->playerID = packet->mUserID;
        curInfo->isConnected = true;
        strcpy(curInfo->puppetName, packet->clientName);
    }
}
/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateGameInfo(GameInf *packet) {
    int puppetIndex = findPuppetID(packet->mUserID);

    if(puppetIndex >= 0) {
        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
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
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Client::updateTagInfo(TagInf *packet) {
    
    // if the packet is for our player, edit info for our player
    if (packet->mUserID == mUserID && mCurMode->getMode() == GameMode::HIDEANDSEEK) {

        HideAndSeekMode* mMode = (HideAndSeekMode*)mCurMode;
        HideAndSeekInfo* curInfo = (HideAndSeekInfo*)mModeInfo;

        if (packet->updateType & TagUpdateType::STATE) {
            mMode->setPlayerTagState(packet->isIt);
        }

        if (packet->updateType & TagUpdateType::TIME) {
            curInfo->mHidingTime.mSeconds = packet->seconds;
            curInfo->mHidingTime.mMinutes = packet->minutes;
        }

        return;

    }

    int puppetIndex = findPuppetID(packet->mUserID);

    if(puppetIndex >= 0) {
        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
            return;
        }

        curInfo->isIt = packet->isIt;
        curInfo->seconds = packet->seconds;
        curInfo->minutes = packet->minutes;
    }
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
    int puppetIndex = findPuppetID(packet->mUserID);

    if(puppetIndex >= 0) {
        PuppetInfo* curInfo = mPuppetInfoArr[puppetIndex];

        if (!curInfo) {
            Logger::log("Attempting to Access Puppet Out of Bounds! Value: %d\n", puppetIndex);
            return;
        }
        
        curInfo->isConnected = false;

        curInfo->scenarioNo = -1;
        strcpy(curInfo->stageName, "");
        curInfo->isInSameStage = false;

        mConnectCount--;

        if (mConnectCount < 0) {
            Logger::log("Connection Count went Negative!\n");
            mConnectCount = 0;
        }
    }
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
int Client::findPuppetID(const nn::account::Uid &id) {
    for (size_t i = 0; i < this->puppetPlayerID.size(); i++)
    {
        if(this->puppetPlayerID[i].uid == id) {
            return this->puppetPlayerID[i].puppetIndex;
        }
    }

    if(this->puppetPlayerID.size() > mConnectCount) {
        int newIndex = mConnectCount;
        this->puppetPlayerID[newIndex].puppetIndex = newIndex;
        this->puppetPlayerID[newIndex].uid = id;
        mConnectCount++;
        return newIndex;
    }

    return -1;
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
        
        Client::sInstance->mPuppetHolder->setStageInfo(sInstance->mStageName.cstr(), sInstance->mScenario);
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
    if(Client::sInstance) {
        return Client::sInstance->mPuppetHolder->tryRegisterPuppet(puppet);
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
    if(Client::sInstance) {
        return Client::sInstance->mPuppetHolder->tryRegisterDebugPuppet(puppet);
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
    if(Client::sInstance) {
        return Client::sInstance->mPuppetHolder->getPuppetActor(idx);
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
    if(Client::sInstance) {
        return Client::getPuppetInfo(Client::sInstance->mPuppetHolder->getSize() - 1);
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
    if(Client::sInstance) {
        // unsafe get
        PuppetInfo *curInfo = Client::sInstance->mPuppetInfoArr[idx];

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
    sInstance->mCurStageScene->stageSceneLayout->startShineCountAnim(false);
}

/**
 * @brief 
 * 
 */
void Client::updateStates() {
    if(sInstance) {
        sInstance->mPuppetHolder->update();

        if(sInstance->mCurMode && sInstance->mCurMode->isModeActive())
            sInstance->mCurMode->update();
    }
}

/**
 * @brief 
 * 
 * @param state 
 */
void Client::setGameActive(bool state) {
    if (sInstance) {

        sInstance->mIsInGame = state;
        
        // only modify mode state if mode should be active
        if (sInstance->mIsModeActive) {

            bool modeActive = sInstance->mCurMode->isModeActive();

            if (state && !modeActive) {
                Logger::log("Resuming Current Mode.\n");
                sInstance->mCurMode->begin();
            } else if (!state && modeActive) {
                Logger::log("Pausing Current Mode.\n");
                sInstance->mCurMode->end();
            }
        }
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
    if(Client::sInstance) {
        return &Client::sInstance->mDebugPuppetInfo;
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
    if(Client::sInstance) {
        return Client::sInstance->mPuppetHolder->getDebugPuppet();
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

/**
 * @brief gets the client's currently selected gamemode
 * 
 * @return GameMode 
 */
GameMode Client::getCurrentMode() {
    return sInstance && sInstance->mCurMode ? sInstance->mCurMode->getMode() : GameMode::NONE;
}

/**
 * @brief enables or disables currently selected gamemode
 * 
 */
void Client::toggleCurrentMode() {
    if (!sInstance || !sInstance->mCurMode) {
        return;
    }

    GameModeBase* curMode = sInstance->mCurMode;

    if (curMode->isModeActive()) {
        Logger::log("Ending Gamemode: %s\n", curMode->getName());
        curMode->end();
        sInstance->mIsModeActive = false;
    } else {
        Logger::log("Starting Gamemode: %s\n", curMode->getName());
        curMode->begin();
        sInstance->mIsModeActive = true;
    }
}

/**
 * @brief re-enables current gamemode if previously activated (if a stage reload occurs while the gamemode was previously active, this will turn it back on after initialized)
 * 
 */
void Client::tryRestartCurrentMode() {
    if (!sInstance || !sInstance->mCurMode) {
        return;
    }
    // restart mode if previous scene had one active
    if (sInstance->mIsModeActive) {
        sInstance->mCurMode->begin();
    }
}

GameModeConfigMenu* Client::tryCreateModeMenu() {
    if (!sInstance)
        return nullptr;

    switch (sInstance->mServerMode) {
    case HIDEANDSEEK: {
        return new HideAndSeekConfigMenu();
    }
    default:
        return nullptr;
    }
}
