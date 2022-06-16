#pragma once

namespace sead {
    class LookAtCamera;
    class Projection;
}

namespace al {
    class IUseCamera;
    class Scene;

    void updateKitListPrev(Scene *);
    void updateKitList(Scene *, const char *);
    void updateKitListPost(Scene *);

    sead::LookAtCamera *getLookAtCamera(al::IUseCamera const*,int);
    sead::Projection *getProjectionSead(al::IUseCamera const*,int);
} // namespace al



// TODO: get this out of here
namespace rs
{
    void requestGraphicsPresetAndCubeMapPause(const al::Scene *);
} // namespace rs
