#pragma once

namespace al {
    struct PadRumbleParam {
        inline PadRumbleParam() = default;
        float mRumbleNear = 0.0f;
        float mRumbleFar = 3000.0f;
        float mRumbleVolume = 1.0f;
        float mRumblePitchVol = 1.0f;
        float mRumblePitchLeft = 1.0f;
        float mRumblePitchRight = 1.0f;
        int unk = 0;
        bool isUseController = false;
    };
    }  // namespace al