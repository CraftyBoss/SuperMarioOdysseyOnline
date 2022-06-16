#include <sead/math/seadQuat.h>
#include <sead/math/seadVector.h>
#include <sead/prim/seadSafeString.h>
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

typedef unsigned short int ushort;

namespace nn::ui2d {
class TextureInfo;
}

namespace al
{

    class IUseLayout;
    class IUseLayoutAction;

    char16_t* getPaneStringBuffer(IUseLayout const* lyt, const char* paneName);
    int getPaneStringBufferLength(IUseLayout const* lyt, const char* paneName);

    void startFreezeActionEnd(IUseLayoutAction*, char const*, char const*);

    void startHitReaction(LayoutActor const *, const char *, const char *);

    void hidePane(IUseLayout* lyt, const char* paneName);
    void hidePaneNoRecursive(IUseLayout* lyt, const char* paneName);
    void showPane(IUseLayout* lyt, const char* paneName);
    void showPaneNoRecursive(IUseLayout* lyt, const char* paneName);

    void hidePaneRoot(al::IUseLayout *);
    void hidePaneRootNoRecursive(al::IUseLayout *);
    void showPaneRoot(al::IUseLayout *);
    void showPaneRootNoRecursive(al::IUseLayout *);

    bool isHidePane(const IUseLayout *lyt, const char *paneName);
    bool isHidePaneRoot(al::IUseLayout const*);
    bool isActionPlaying(IUseLayoutAction *, const char *action, const char *group);
    bool isActionEnd(IUseLayoutAction const*, char const*);
    bool isExistPane(const al::IUseLayout *lyt, char const *paneName);

    void initLayoutActor(LayoutActor*, LayoutInitInfo const&, char const*, char const*);
    void setActionFrameRate(IUseLayoutAction *,float,char const*);
    void setPaneString(IUseLayout *layout, char const *paneName, char16_t const *paneValue, ushort);
    void setPaneStringFormat(IUseLayout* layout, char const* paneName, char const* format, ...);
    void setPaneTexture(IUseLayout*, char const*, nn::ui2d::TextureInfo const*);
    void calcLayoutPosFromWorldPos(sead::Vector2f*, const al::IUseCamera*, const sead::Vector3f &);
    void calcLayoutPosFromWorldPosSub(sead::Vector2f *, const al::IUseCamera *, const sead::Vector3f &);
    void calcPaneTrans(sead::Vector2f*, IUseLayout const*, char const*);
    void setLocalTrans(IUseLayout*, sead::Vector2f const&);
    void setLocalScale(IUseLayout *, float);

} // namespace al
