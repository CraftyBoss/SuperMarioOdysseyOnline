#pragma once

#include "al/resource/ActorResource.h"
#include "math/seadMatrix.h"
#include "types.h"
#include "ModelCtrl.h"

namespace al {
    struct ModelLodCtrl;
    struct DitherAnimator;
    struct GpuMemAllocator;
    struct ModelShaderHolder;
    struct ModelOcclusionCullingDirector;
    struct ShadowDirector;
    struct PrepassTriangleCulling;
}

namespace al {
    class ModelKeeper {
    public:
        ModelKeeper();
        virtual ~ModelKeeper();
        void initResource(al::ActorResource const*);
        void createMatAnimForProgram(int);
        void getAnimResource() const;
        void getModelResource() const;
        void setDisplayRootJointMtxPtr(sead::Matrix34f const*);
        void setModelLodCtrl(al::ModelLodCtrl*);
        void setDitherAnimator(al::DitherAnimator*);
        void initModel(int, al::GpuMemAllocator*, al::ModelShaderHolder*, al::ModelOcclusionCullingDirector*, al::ShadowDirector*, al::PrepassTriangleCulling*);
        void show();
        void hide();
        void update();
        void updateLast();
        void calc(sead::Matrix34f const&, sead::Vector3f const&);
        void getBaseMtx() const;
        void getWorldMtxPtrByIndex(int) const;

        const char *mResourceName;
        al::ModelCtrl *mModelCtrl;
        const al::ActorResource *mResource;
        char gap20[67];
        bool field_63;

   };
}