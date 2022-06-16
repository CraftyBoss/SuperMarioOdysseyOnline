#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/layout/LayoutActor.h"
#include "PadRumbleParam.h"

namespace al {
    class PadRumbleDirector;
}

namespace alPadRumbleFunction {
    al::PadRumbleDirector *getPadRumbleDirector(al::LiveActor const*);
    al::PadRumbleDirector *getPadRumbleDirector(al::LayoutActor const*);
    void startPadRumble(al::PadRumbleDirector *,sead::Vector3<float> const&,char const*,float,float,int);
    void startPadRumbleWithParam(al::PadRumbleDirector *,sead::Vector3<float> const&,char const*,al::PadRumbleParam const&,int);
    void startPadRumble(al::LiveActor const*,char const*,float,float,int);
    void startPadRumblePos(al::LiveActor const*,sead::Vector3<float> const&,char const*,float,float,int);
    void startPadRumbleWithParam(al::LiveActor const*,sead::Vector3<float> const&,char const*,al::PadRumbleParam const&,int);
    void startPadRumbleNo3D(al::PadRumbleDirector *,char const*,int);
    void startPadRumbleNo3DWithParam(al::PadRumbleDirector *,char const*,al::PadRumbleParam const&,int);
    void startPadRumbleNo3DWithParam(al::PadRumbleDirector *,char const*,float,float,float,float,int);
    void startPadRumbleNo3D(al::LiveActor const*,char const*,int);
    void startPadRumbleNo3DWithParam(al::LiveActor const*,char const*,al::PadRumbleParam const&,int);
    void startPadRumbleNo3DWithParam(al::LiveActor const*,char const*,float,float,float,float,int);
    void stopPadRumbleOneTime(al::PadRumbleDirector *,char const*,int);
    void stopPadRumbleOneTime(al::LiveActor const*,char const*,int);
    void startPadRumbleLoop(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,float,float,int);
    void startPadRumbleLoopWithParam(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,al::PadRumbleParam const&,int);
    void startPadRumbleLoop(al::LiveActor const*,char const*,sead::Vector3<float> const*,float,float,int);
    void startPadRumbleLoopWithParam(al::LiveActor const*,char const*,sead::Vector3<float> const*,al::PadRumbleParam const&,int);
    void startPadRumbleLoopNo3D(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,int);
    void startPadRumbleLoopNo3DWithParam(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,al::PadRumbleParam const&,int);
    void startPadRumbleLoopNo3D(al::LiveActor const*,char const*,sead::Vector3<float> const*,int);
    void startPadRumbleLoopNo3DWithParam(al::LiveActor const*,char const*,sead::Vector3<float> const*,al::PadRumbleParam const&,int);
    void stopPadRumbleLoop(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,int);
    void stopPadRumbleLoop(al::LiveActor const*,char const*,sead::Vector3<float> const*,int);
    void checkIsAlivePadRumbleLoop(al::PadRumbleDirector *,char const*,sead::Vector3<float> const*,int);
    void checkIsAlivePadRumbleLoop(al::LiveActor const*,char const*,sead::Vector3<float> const*,int);
    void startPadRumbleLoopControlable(al::LiveActor const*,char const*,sead::Vector3<float> const*,int);
    void changePadRumbleLoopVolmue(al::LiveActor const*,char const*,sead::Vector3<float> const*,float,float,int);
    void changePadRumbleLoopVolmueEaseInRange(al::LiveActor const*,char const*,sead::Vector3<float> const*,float,float,float,float,float,int);
    void changePadRumbleLoopPitch(al::LiveActor const*,char const*,sead::Vector3<float> const*,float,float,int);
    void startPadRumbleDirectValue(al::LiveActor const*,float,float,float,float,float,float,int);
    void stopPadRumbleDirectValue(al::LiveActor const*,int);
    void startPadRumbleWithVolume(al::LiveActor const*,char const*,float,float,int);
    void startPadRumbleWithVolume(al::PadRumbleDirector *,char const*,float,float,int);
    void makePadRumbleParamNearFarVolume(al::PadRumbleParam *,float,float,float);
    void makePadRumbleParamNearFarVolumeLR(al::PadRumbleParam *,float,float,float,float);
    void makePadRumbleParamNearFarVolumePitch(al::PadRumbleParam *,float,float,float,float);
    void makePadRumbleParamNearFarVolumePitchLR(al::PadRumbleParam *,float,float,float,float,float,float);

};