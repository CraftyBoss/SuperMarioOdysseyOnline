#pragma once
/**
 * @file PlayerActorBase.h
 * @brief base class for PlayerActor
* Vtable loc: 1D77980
*/

#include "PlayerHackKeeper.h"
#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerCollision.h"
#include "game/Interfaces/IUsePlayerHack.h"
#include "game/Player/PlayerCollider.h"
#include "game/Player/PlayerInfo.h"
#include "game/Player/PlayerInitInfo.h"
#include "game/Player/PlayerPuppet.h"

class PlayerActorBase : public al::LiveActor, public IUsePlayerHack {
    public: 
        PlayerActorBase(char const*);

        virtual void movement(void) override;
        virtual void init(al::ActorInitInfo const&) override;
        virtual void initPlayer(al::ActorInitInfo const&, PlayerInitInfo const&);
        virtual int getPortNo(void);
        virtual sead::Matrix34f *getViewMtx(void) const;
        virtual IUsePlayerCollision* getPlayerCollision(void) const;

        virtual bool isEnableDemo(void);
        virtual void startDemo(void);
        virtual void endDemo(void);

        virtual void startDemoPuppetable(void);
        virtual void endDemoPuppetable(void);

        virtual void startDemoShineGet(void);
        virtual void endDemoShineGet(void);

        virtual void startDemoMainShineGet(void);
        virtual void endDemoMainShineGet(void);

        virtual void startDemoHack(void);
        virtual void endDemoHack(void);

        virtual void startDemoKeepBind(void);
        virtual void noticeDemoKeepBindExecute(void);
        virtual void endDemoKeepBind(void);

        virtual void startDemoKeepCarry(void);
        virtual void endDemoKeepCarry(void);

        virtual void getDemoActor(void);
        virtual void getDemoAnimator(void);

        virtual bool isDamageStopDemo(void) const;

        virtual PlayerPuppet *getPlayerPuppet(void);
        virtual PlayerInfo *getPlayerInfo(void) const;

        virtual bool checkDeathArea(void);
        virtual void sendCollisionMsg(void);

        virtual bool receivePushMsg(al::SensorMsg const*,al::HitSensor *,al::HitSensor *,float);
        virtual PlayerHackKeeper* getPlayerHackKeeper() const override;

        sead::Matrix34f* mViewMtx;  // 0x110
        int mPortNo; // 0x118
};