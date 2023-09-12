#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Interfaces for Classes that use PlayerHack (PlayerActorBase)
* Vtable loc: 
*/

class IUsePlayerHack {
public:
    virtual struct PlayerHackKeeper *getPlayerHackKeeper() const = 0;
};