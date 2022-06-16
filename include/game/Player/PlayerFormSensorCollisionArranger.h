#pragma once

#include "sead/math/seadVector.h"
#include "al/LiveActor/LiveActor.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerHackKeeper.h"

class IPlayerModelChanger;

class PlayerFormSensorCollisionArranger {
    public:
        PlayerFormSensorCollisionArranger(al::LiveActor *, PlayerColliderHakoniwa *, IPlayerModelChanger const*, PlayerHackKeeper const*);
        void setFormModel3D(void);
        void setFormModel2D(void);
        void setFormActionSquat(void);
        void setFormActionStandup(void);
        void setFormActionWallGrab(sead::Vector3f const&);	
        void setFormActionGrabCeil(sead::Vector3f const&);	
        void setFormActionPoleClimb(sead::Vector3f const&);	
        void setFormActionSwim(void);
        void setFormActionHack(void);
        void setFormActionBind(bool);
        void setFormActionRecovery(void);
        void setFormActionAbyss(sead::Vector3f const&);	
        void setFormActionDead(void);
        void setFormAttackSensorNone(void);
        void setFormAttackSensorSpin(void);
        void setFormAttackSensorTornado(void);
        void setCollisionShapeOffsetGround(float);
        const char *getHeadSensorName(void) const;
        sead::Vector3f *getHeadPos(void) const;
        float getHeadRadius(void) const;
        sead::Vector3f *getBodyPos(void) const;
        bool isEnableSafetyPointForm(void) const;
        void update(void);
        void syncForm(void);
        void validateAttackSensor(void);

};