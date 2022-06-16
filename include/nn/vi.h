/**
 * @file vi.h
 * @brief Visual interface implementation.
 */

#pragma once

#include "os.h"
#include "types.h"

namespace nn
{
    namespace vi
    {
        class Display;
        class Layer;

        enum ScalingMode
        {
            None,
            Exact,
            FitLayer,
            ScaleAndCrop,
            PreserveAspectRatio
        };

        void Initialize();
        Result OpenDefaultDisplay(nn::vi::Display **out_Disp);
        Result CreateLayer(nn::vi::Layer *out_Layer*, nn::vi::Display *disp);
        Result SetLayerScalingMode(nn::vi::Layer *layer, nn::vi::ScalingMode scalingMode);
        Result GetDisplayVsyncEvent(nn::os::SystemEventType *, nn::vi::Display *);
        Result GetNativeWindow(void **window, nn::vi::Layer *);
    };
};