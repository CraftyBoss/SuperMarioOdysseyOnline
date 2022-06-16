#pragma once

#include <math/seadVector.h>

#include "al/LiveActor/LiveActor.h"
#include "al/camera/CameraDirector.h"
#include "al/camera/CameraTicket.h"
#include "al/camera/CameraTargetBase.h"
#include "al/scene/Scene.h"

namespace al {

struct SceneCameraInfo;
struct PauseCameraCtrl;
struct CameraPoseInfo;

sead::Vector3f* getCameraUp(al::IUseCamera const*, int);

void requestStopCameraVerticalAbsorb(al::IUseCamera *);

bool isActiveCamera(al::CameraTicket const*);
bool isActiveCameraTarget(al::CameraTargetBase const*);
bool isActiveCameraSubTarget(al::CameraSubTargetBase const*);
bool isActiveCameraInterpole(al::IUseCamera const*,int);
bool isActiveCameraInterpole(al::SceneCameraInfo const*, int);

void startCamera(al::IUseCamera const*,al::CameraTicket *,int priority);
void startCameraSub(al::IUseCamera const*,al::CameraTicket *,int priority);
void startCameraShakeByAction(al::LiveActor const*,char const*,char const*,int,int);
void startCameraShakeByHitReaction(al::IUseCamera const*,char const*,char const*,char const*,int,int);
void startCameraInterpole(al::IUseCamera const*,int,int);
void restartCameraByDeathPlayer(al::Scene *);
void startCameraSnapShotMode(al::Scene *,bool);
void startCameraPause(al::PauseCameraCtrl*);

void endCamera(al::IUseCamera const*,al::CameraTicket *,int,bool);
void endCameraWithNextCameraPose(al::IUseCamera const*,al::CameraTicket *,al::CameraPoseInfo const*,int);
void endCameraSub(al::IUseCamera const*,al::CameraTicket *,int);
void endCameraSnapShotMode(al::Scene *);
void endCameraPause(al::PauseCameraCtrl *);

}