#include "server/Client.hpp"
#include "logger.hpp"
#include "main.hpp"

al::LiveActor *createPuppetActorFromFactory(al::ActorInitInfo const &rootInitInfo, al::PlacementInfo const &rootPlacementInfo, bool isDebug) {
    al::ActorInitInfo actorInitInfo = al::ActorInitInfo();
    actorInitInfo.initViewIdSelf(&rootPlacementInfo, rootInitInfo);

    al::createActor createActor = actorInitInfo.mActorFactory->getCreator("PuppetActor");
    
    if(createActor) {
        PuppetActor *newActor = (PuppetActor*)createActor("PuppetActor");

        if(!isDebug) {
            if(Client::tryAddPuppet(newActor)) {
                PuppetInfo *curInfo = Client::getLatestInfo();
                if(!curInfo) {
                    Logger::log("Puppet Info is Null!\n");
                }else {

                    newActor->initOnline(curInfo); // set puppet info first before calling init so we can get costume info from the info

                    newActor->init(actorInitInfo);
                }
            }
        } else {

            Logger::log("Creating Test Puppet.\n");

            newActor->initOnline(Client::getDebugPuppetInfo()); 

            newActor->init(actorInitInfo);

            newActor->mIsDebug = true;

            newActor->makeActorAlive();

            if (Client::tryAddDebugPuppet(newActor)) {
                Logger::log("Debug Puppet Created!\n");
            }

        }

        return newActor;
    }else {
        return nullptr;
    }
}

// Hooks

void initPuppetActors(al::Scene *scene, al::ActorInitInfo const &rootInfo, char const *listName) {
    al::StageInfo *stageInfo = al::getStageInfoMap(scene, 0);

    int placementCount = 0;
    al::PlacementInfo rootPlacement = al::PlacementInfo();
    al::tryGetPlacementInfoAndCount(&rootPlacement, &placementCount, stageInfo, "PlayerList");
    // check if default placement count for PlayerList is greater than 0 (so we can use the placement info of the player to init our custom puppet actors)
    if(placementCount > 0) {
        al::PlacementInfo playerPlacement = al::PlacementInfo();
        al::getPlacementInfoByIndex(&playerPlacement, rootPlacement, 0);

        for (size_t i = 0; i < Client::getMaxPlayerCount(); i++)
        {
            createPuppetActorFromFactory(rootInfo, playerPlacement, false);
        }
        
        // create a debug puppet for testing purposes
        // createPuppetActorFromFactory(rootInfo, playerPlacement, true);
    }

    al::initPlacementObjectMap(scene, rootInfo, listName); // run init for ObjectList after we init our puppet actors 
}