#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/scene/ISceneObj.h"

class RouteGuideDirector : public al::LiveActor, public al::ISceneObj {
public:
    RouteGuideDirector();

    void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;

    bool isValidate(void) const;
    void offGuideSystem(void);
    void deactivateGuide(void);
    void onGuideSystem(void);
    void activateGuide(void);
    void offGuideByActor(al::LiveActor *);
    void addInvidateList(al::LiveActor *);
    void onGuideByActor(al::LiveActor *);
    void removeInvidateList(al::LiveActor const*);
    void addRouteGuidePointBufferCount(int);
    void registerRouteGuidePoint(struct RouteGuidePoint *);
    void addRouteGuideArrowBufferCount(int);
    void registerRouteGuideArrow(struct RouteGuideArrowBase*);
    
    void exeOff(void);
    void exeOn(void);

    virtual const char* getSceneObjName() override;
    virtual void initSceneObj(void) override;
};