#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "sead/math/seadMatrix.h"
#include "sead/math/seadVector.h"

class MapIconLayout{};
class IconType {};
class MapIconInfo {};

struct MapLayout : public al::LayoutActor {
    MapLayout(const char* name, const al::LayoutInitInfo& initInfo);
    void changePrintWorld(int);
    void loadTexture();
    void reset();
    void appear();
    void moveFocusLayout(const sead::Vector3f&, const sead::Vector2f&);
    void updateST();
    void addAmiiboHint();
    void appearAmiiboHint();
    void end();
    void updatePlayerPosLayout();
    void appearWithHint();
    void appearWithMoonRockDemo();
    void appearCollectionList();
    bool isEnd();
    bool isEnableCheckpointWarp();
    void changeOut();
    void changeIn();
    void control();
    void updateLine(al::LayoutActor*);
    void appearParts();
    void startNumberAction();
    void calcSeaOfTreeIconPos(sead::Vector3f*);
    void setLocalTransAndAppear(MapIconLayout*, MapIconInfo*, const sead::Vector3f&, IconType, bool);
    void calcMapTransAndAppear(MapIconLayout*, MapIconInfo*, const sead::Vector3f&, IconType, bool);
    void scroll(const sead::Vector2f&);
    void addSize(const sead::Vector2f&);
    bool isAppear();
    sead::Matrix44f* getViewProjMtx();
    sead::Matrix44f* getProjMtx();
    void updateIconLine(al::LayoutActor*, const sead::Vector3f&, const sead::Vector2f&);
    void focusIcon(const MapIconInfo*);
    void lostFocusIcon(MapIconLayout*);
    void tryCalcNorthDir(sead::Vector3f*);
    const char* getSceneObjName() {
        return "マップレイアウト";
    }

    void exeAppear();
    void exeWait();
    void exeHintInitWait();
    void exeHintAppear();
    void exeHintDecideIconAppear();
    void exeHintDecideIconWait();
    void exeHintPressDecide();
    void exeEnd();
    void exeChangeOut();
};
