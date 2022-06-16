#pragma once

namespace al
{
    class CameraPoserFlag {
        public:
            CameraPoserFlag(void);
            bool mFirstCalc = true;
            bool mOffVerticalAbsorb = true;
            bool mInvalidCollider = false;
            bool unkBool4 = false;
            bool mValidKeepPreSelfPoseNextCameraByParam = false;
            bool unkBool6 = false;
            bool mInvalidKeepPreSelfPoseNextCameraOverWriteProgram = false;
            bool mInvalidKeepDistanceNextCamera = false;
            bool unkBool9 = false;
            bool unkBool10 = false;
            bool mInvalidChangeSubjective = false;
            bool unkBool12 = false;
            bool unkBool13 = false;
            bool mInvalidPreCameraEndAfterInterpole = false;
            bool mStopUpdateGyro = false; // 0xE
            // might be better to use a bool array?
    };
};