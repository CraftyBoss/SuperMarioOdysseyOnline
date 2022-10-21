#pragma once

#include "al/execute/ExecuteDirector.h"
#include "al/model/ModelMaterialCategory.h"
#include "al/resource/Resource.h"
#include "container/seadPtrArray.h"
#include "gfx/seadCamera.h"

#include "UniformBlock.h"
#include "types.h"

namespace al {
    struct GraphicsInitArg;
    struct GraphicsUpdateInfo;
    struct GraphicsCalcGpuInfo;
    struct PartsGraphics;
    struct GraphicsRenderInfo;
    struct GraphicsCopyInfo;
    struct GraphicsComputeInfo;
    struct AreaObjDirector;
    struct EffectSystem;
    struct SceneCameraInfo;
    struct ShaderHolder;
    struct GBufferArray;
    struct Projection;
    struct RenderVariables;
    struct ShaderCubeMapKeeper;
    struct ShaderMirrorDirector;
    struct SubCameraRenderer;
    struct GraphicsParamFilePath;
    struct PlayerHolder;
}

namespace agl {
    struct DrawContext;

    namespace utl {
        struct ParameterOfBool { char size[0x20]; };
        struct ParameterOfInt { char size[0x20]; };
        struct ParameterOfFloat { char size[0x20]; };
        struct IParameterObj { char size[0x30]; };
        struct IParameterIO { char size[0x1D0]; };
    }
}

namespace al {
    class GraphicsSystemInfo {
    public:
        GraphicsSystemInfo();
        ~GraphicsSystemInfo();
        void getModelEnv() const;
        void getDrawContext() const;
        void getShaderCubeMapKeeper() const;
        void getViewIndexedUboArray(char const*) const;
        void setViewIndexedUboArray(char const*, sead::PtrArray<al::UniformBlock> const*);
        void initAtmosScatter(al::ExecuteDirector*);
        void init(al::GraphicsInitArg const&, al::AreaObjDirector*, al::ExecuteDirector*, al::EffectSystem*, al::PlayerHolder*, al::SceneCameraInfo*, al::ShaderHolder*);
        void initProjectResource();
        void initStageResource(al::Resource const*, char const*, char const*);
        void endInit();
        void initAfterPlacement();
        void initAfterCreateDrawTable();
        void setDrawEnv(int, al::GBufferArray*, sead::Camera const*, al::Projection const*);
        void clearGraphicsRequest();
        void cancelLerp();
        void updateGraphics();
        void updatePartsGraphics(al::GraphicsUpdateInfo const&);
        void preDrawGraphics(al::SceneCameraInfo const*);
        void calcGpuPartsGraphics(al::GraphicsCalcGpuInfo const&);
        void updateViewGpu(int, sead::Camera const*, al::Projection const*);
        void updateViewVolume(sead::Matrix34f const&, sead::Matrix44<float> const&);
        void clearViewVolume();
        void tryGetAtmosLightDir(sead::Vector3f*) const;
        void tryDirectionalLightInfo(sead::Vector3f*) const;
        void activateDirLitColorTex() const;
        void activateDirLitColorTex(agl::DrawContext*) const;
        void registPartsGraphics(al::PartsGraphics*);
        void drawSystemPartsGraphics(al::GraphicsRenderInfo const*) const;
        void doPartsGraphicsCommandBufferCopy(al::GraphicsCopyInfo const&) const;
        void doPartsGraphicsCompute(al::GraphicsComputeInfo const&) const;
        void drawPartsGraphics(al::GraphicsRenderInfo const&, al::RenderVariables const&) const;
        void drawPartsGraphicsGBufferAfterSky(al::GraphicsRenderInfo const&) const;
        void drawPartsGraphicsDeferred(al::GraphicsRenderInfo const&) const;
        void drawPartsGraphicsLdr(al::GraphicsRenderInfo const&) const;
        void drawPartsGraphicsIndirect(al::GraphicsRenderInfo const&, al::RenderVariables const&) const;
        void drawPartsGraphicsCubemap(al::GraphicsRenderInfo const&) const;

        void *qword0;
        void *qword8;
        void *qword10;
        void *qword18;
        char gap20[5];
        char byte25;
        u16 word26;
        int dword28;
        int dword2C;
        int dword30;
        int dword34;
        int dword38;
        int dword3C;
        char byte40;
        int dword44;
        char byte48;
        int dword4C;
        int dword50;
        int dword54;
        int dword58;
        int dword5C;
        void *qword60;
        char char68;
        al::ShaderCubeMapKeeper **field_70;
        char gap78[56];
        al::ShadowDirector *field_B0;
        char gapB8[16];
        al::ShaderMirrorDirector *field_C8;
        char gapD0[320];
        char char210;
        void *qword218;
        void *qword220;
        void *qword228;
        void *qword230;
        al::MaterialCategoryKeeper *mMaterialCategoryKeeper;
        void *qword240;
        void *qword248;
        void *qword250;
        void *qword258;
        void *qword260;
        void *qword268;
        void *qword270;
        void *qword278;
        void *qword280;
        al::GpuMemAllocator *field_288;
        char gap290[8];
        void *qword298;
        void *qword2A0;
        char gap2A8[8];
        void *qword2B0;
        al::SubCameraRenderer *field_2B8;
        void *qword2C0;
        void *qword2C8;
        void *qword2D0;
        void *qword2D8;
        void *qword2E0;
        void *qword2E8;
        int dword2F0;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword2F4;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword2FC;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword304;
        int dword30C;
        al::GraphicsParamFilePath *mParamFilePath;
        agl::utl::IParameterIO agl__utl__iparameterio318;
        agl::utl::IParameterObj agl__utl__iparameterobj4E8;
        agl::utl::ParameterOfInt field_518;
        agl::utl::ParameterOfInt field_538;
        agl::utl::ParameterOfBool field_558;
        agl::utl::ParameterOfBool field_578;
        agl::utl::ParameterOfInt field_598;
        agl::utl::IParameterIO field_5B8;
        agl::utl::IParameterObj field_788;
        agl::utl::ParameterOfBool field_7B8;
        agl::utl::ParameterOfBool field_7D8;
        agl::utl::ParameterOfBool field_7F8;
        agl::utl::ParameterOfFloat field_818;
        agl::utl::ParameterOfFloat field_838;
        agl::utl::ParameterOfFloat field_858;
        agl::utl::ParameterOfFloat field_878;
        agl::utl::ParameterOfFloat field_898;
        agl::utl::ParameterOfFloat field_8B8;
        agl::utl::ParameterOfFloat field_8D8;
        agl::utl::ParameterOfFloat field_8F8;
        void *qword918;
        void *qword920;
        void *qword928;
        void *qword930;
        void *qword938;
        void *qword940;
        void *qword948;
        void *qword950;
        void *qword958;
        int dword960;
        void *qword968;
        void *qword970;
        int dword978;
        void *qword980;
        al::ModelOcclusionCullingDirector *field_988;
        void *qword990;
        al::ModelShaderHolder *field_998;
        al::PrepassTriangleCulling *field_9A0;
        char byte9A8;
        void *field_9B0;

   };
}