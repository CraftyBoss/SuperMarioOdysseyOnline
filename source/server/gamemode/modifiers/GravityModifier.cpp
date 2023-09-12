#include "server/gamemode/modifiers/GravityModifier.hpp"
#include "helpers.hpp"
#include "math/seadVector.h"
#include "rs/util.hpp"

GravityModifier::GravityModifier(GameModeBase* mode) : ModeModifierBase(mode) {}

void GravityModifier::enable() {
    ModeModifierBase::enable();
    if(mTicket && mScene)
        al::startCamera(mScene, mTicket, -1);
}

void GravityModifier::disable() {
    ModeModifierBase::disable();
    if(mTicket && mScene)
        al::endCamera(mScene, mTicket, -1, false);
}

void GravityModifier::update() {

    sead::Vector3f gravity;
    PlayerActorBase *playerBase = rs::getPlayerActor(mScene);

    if (rs::calcOnGroundNormalOrGravityDir(&gravity, playerBase, playerBase->getPlayerCollision())) {
        gravity = -gravity;
        al::normalize(&gravity);
        al::setGravity(playerBase, gravity);
        al::setGravity(((PlayerActorHakoniwa*)playerBase)->mHackCap, gravity);
    }
    
    if (al::isPadHoldL(-1)) {
        if (al::isPadTriggerRight(-1)) {
            if (al::isActiveCamera(mTicket)) {
                al::endCamera(mScene, mTicket, -1, false);
            } else {
                al::startCamera(mScene, mTicket, -1);
            }
        }
    } else if (al::isPadTriggerZL(-1)) {
        if (al::isPadTriggerLeft(-1)) {
            killMainPlayer(((PlayerActorHakoniwa*)playerBase));
        }
    }

}