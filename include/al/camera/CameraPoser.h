#pragma once

#include "al/actor/Placement.h"
#include "al/byaml/ByamlIter.h"
#include "al/hio/HioNode.h"
#include "al/area/AreaObjDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/collision/CollisionDirector.h"
#include "al/actor/IUseName.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"
#include "al/rail/RailKeeper.h"

#include "CameraPoserFlag.h"
#include "CameraStartInfo.h"
#include "CameraTurnInfo.h"
#include "CameraObjectRequestInfo.h"
#include "al/rail/RailRider.h"

#include "sead/math/seadQuat.h"
#include "sead/gfx/seadCamera.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"

// size is 0x140/320 bytes
namespace al {

    class CameraVerticalAbsorber;
    class CameraAngleCtrlInfo;
    class CameraAngleSwingInfo;
    class CameraArrowCollider;
    class CameraOffsetCtrlPreset;
    class CameraParamMoveLimit;
    class GyroCameraCtrl;
    class SnapShotCameraCtrl;
    class CameraViewInfo;

    class CameraPoser : public al::HioNode, public al::IUseAreaObj, public al::IUseAudioKeeper, public al::IUseCollision, public al::IUseName, public al::IUseNerve, public al::IUseRail {
        public:
            CameraPoser(char const* poserName);

            virtual AreaObjDirector* getAreaObjDirector() const override;
            virtual void init();
            virtual void initByPlacementObj(al::PlacementInfo const&);
            virtual void endInit();
            virtual void start(CameraStartInfo const &);
            virtual void update();
            virtual void end();
            virtual void loadParam(ByamlIter const &);
            virtual void makeLookAtCamera(sead::LookAtCamera*) const;
            virtual void receiveRequestFromObject(CameraObjectRequestInfo const&);
            virtual bool isZooming(void) const;
            virtual bool isEnableRotateByPad(void) const;
            virtual void startSnapShotMode(void);
            virtual void endSnapShotMode(void);

            virtual const char *getName(void) const override;
            virtual CollisionDirector *getCollisionDirector(void) const override;
            virtual NerveKeeper *getNerveKeeper(void) const override;
            virtual AudioKeeper *getAudioKeeper(void) const override;
            virtual RailRider* getRailRider(void) const override;
            
            virtual void load(ByamlIter const&);
            virtual void movement(void);
            virtual void calcCameraPose(sead::LookAtCamera *) const;
            virtual void requestTurnToDirection(al::CameraTurnInfo const *);

            bool isInterpoleByCameraDistance(void) const;
            bool isInterpoleEaseOut(void) const;
            bool isEndInterpoleByStep(void) const;
            bool isFirstCalc(void) const;

            void initNerve(al::Nerve const*,int);
            void initArrowCollider(al::CameraArrowCollider *);
            void initAudioKeeper(char const*);
            void initRail(al::PlacementInfo const&);
            void initLocalInterpole(void);
            void initLookAtInterpole(float);
            void initOrthoProjectionParam(void);
            void tryInitAreaLimitter(al::PlacementInfo const&);

            void makeLookAtCameraPrev(sead::LookAtCamera *) const;
            void makeLookAtCameraPost(sead::LookAtCamera *) const;
            void makeLookAtCameraLast(sead::LookAtCamera *) const;
            void makeLookAtCameraCollide(sead::LookAtCamera*) const;
            
            void getInterpoleStep(void);
            void setInterpoleStep(int);
            void resetInterpoleStep(void);
            void setInterpoleEaseOut(void);
            void getEndInterpoleStep(void);
            
            void appear(al::CameraStartInfo const&);
            void calcCameraPose(sead::LookAtCamera *);
            void receiveRequestFromObjectCore(al::CameraObjectRequestInfo const&);

            void startSnapShotModeCore(void);
            void endSnapShotModeCore(void);

            const char *mPoserName; // 0x30
            float unkFloat1; // 0x38
            sead::Vector3f mPosition; // 0x3C
            sead::Vector3f mTargetTrans = sead::Vector3f::ex; // 0x48
            sead::Vector3f mCameraUp = sead::Vector3f::ey; // 0x54
            float mFovyDegree = 35.0f; // 0x60
            float unkFloat; // 0x64
            sead::Matrix34f mViewMtx = sead::Matrix34f::ident; // 0x68
            bool unkBool1 = false; // 0x98
            CameraViewInfo *mViewInfo; // 0xA0
            al::AreaObjDirector *mAreaDirector; // 0xA8
            CameraPoserFlag *mPoserFlags; // 0xB0
            CameraVerticalAbsorber *mVerticalAbsorber; // 0xB8 
            CameraAngleCtrlInfo *mAngleCtrlInfo; // 0xC0 
            CameraAngleSwingInfo *mAngleSwingInfo; // 0xC8 
            CameraArrowCollider *mArrowCollider; // 0xD0 
            CameraOffsetCtrlPreset *mOffsetCtrlPreset; // 0xD8 
            float *mLocalInterpole; // 0xE0 (size = 0x20)
            float *mLookAtInterpole; // 0xE8 (size = 0x10)
            CameraParamMoveLimit *mParamMoveLimit; // 0xF0 
            void *unkPtr4; // 0xF8
            GyroCameraCtrl *mGyroCtrl; // 0x100 
            SnapShotCameraCtrl *mSnapshotCtrl; // 0x108 
            AudioKeeper *mAudioKeeper; // 0x110 
            NerveKeeper *mNerveKeeper; // 0x118 
            RailKeeper *mRailKeeper; // 0x120 
            int *unkPtr5; // 0x128 (size = 0xC) interpolesteptype?
            int *unkPtr6; // 0x130 (size - 0x8)
            sead::Vector3f *mOrthoProjectionParam; // 0x138 (gets init'd with new of size 0xC)
    };

    static_assert(sizeof(CameraPoser) == 0x140, "Camera Poser Size");
};
