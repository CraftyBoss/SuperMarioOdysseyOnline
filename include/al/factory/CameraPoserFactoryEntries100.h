#pragma once

#include "CameraPoserFactory.h"
#include "al/factory/Factory.h"

#include "cameras/CameraPoserCustom.h"

class CameraPoserFollowLimit;
class ScenarioStartCameraPoserSimpleZoom;
class ScenarioStartCameraPoserRailMove;

namespace al {
    class CameraPoserFix;
    class CameraPoserFixPoint;
    class CameraPoserRace;
    class CameraPoserRailMoveLookAt;
    class CameraPoserKinopioBrigade;
    class CameraPoserTalk;
    class CameraPoserRailMoveMovie;
    class CameraPoserBossBattle;
    class CameraPoserEntrance;
    class CameraPoserLookBoard;
    class CameraPoserLookDown;
    class CameraPoserSubjective;
    class CameraPoserTower;
    class KeyMoveCameraFix;
    class KeyMoveCameraRailMove;
    class KeyMoveCameraZoom;
    class CameraPoserFix;
    class CameraPoserFix;
    class CameraPoserFix;
    class CameraPoserFix;
    class CameraPoserFix;
    class CameraPoserFix;
    class CameraPoserFix;
}
// 0xE in size
static al::NameToCreator<al::createCameraPoser> poserEntries[] = {
    {"制限付きフォロー", &al::createCameraPoserFunction<CameraPoserFollowLimit>},
    {"制限付き平行", &al::createCameraPoserFunction<CameraPoserFollowLimit>},
    {"2D平行", &al::createCameraPoserFunction<CameraPoserFollowLimit>},
    {"固定", &al::createCameraPoserFunction<al::CameraPoserFix>},
    {"完全固定", &al::createCameraPoserFunction<al::CameraPoserFix>},
    {"出入口専用固定", &al::createCameraPoserFunction<al::CameraPoserFix>},
    {"定点", &al::createCameraPoserFunction<al::CameraPoserFixPoint>},
    {"その場定点", &al::createCameraPoserFunction<al::CameraPoserFixPoint>},
    {"完全追従定点", &al::createCameraPoserFunction<al::CameraPoserFixPoint>},
    {"レース", &al::createCameraPoserFunction<al::CameraPoserRace>},
    {"レール移動", &al::createCameraPoserFunction<al::CameraPoserRailMoveLookAt>},
    {"キノピオ探検隊", &al::createCameraPoserFunction<al::CameraPoserKinopioBrigade>},
    {"会話用2点間", &al::createCameraPoserFunction<al::CameraPoserTalk>},
    {"映像撮影レール", &al::createCameraPoserFunction<al::CameraPoserRailMoveMovie>},
    // Custom Posers
    {"CameraPoserCustom", &cc::createCustomCameraPoser<cc::CameraPoserCustom>} // al::CameraPoserFollowSimple
};

// 0xB in size
static al::NameToCreator<al::createCameraPoser> poserEntries2[] = {
    {"ボス戦カメラ", &al::createCameraPoserFunction<al::CameraPoserBossBattle>},
    {"スタート", &al::createCameraPoserFunction<al::CameraPoserEntrance>},
    {"看板用2点間", &al::createCameraPoserFunction<al::CameraPoserLookBoard>},
    {"見下ろし", &al::createCameraPoserFunction<al::CameraPoserLookDown>},
    {"主観", &al::createCameraPoserFunction<al::CameraPoserSubjective>},
    {"塔", &al::createCameraPoserFunction<al::CameraPoserTower>},
    {"キー移動固定", &al::createCameraPoserFunction<al::KeyMoveCameraFix>},
    {"キー移動レール移動", &al::createCameraPoserFunction<al::KeyMoveCameraRailMove>},
    {"キー移動ズーム", &al::createCameraPoserFunction<al::KeyMoveCameraZoom>},
    {"シナリオ紹介シンプルズームカメラ", &al::createCameraPoserFunction<ScenarioStartCameraPoserSimpleZoom>},
    {"シナリオ紹介レール移動カメラ", &al::createCameraPoserFunction<ScenarioStartCameraPoserRailMove>},
};