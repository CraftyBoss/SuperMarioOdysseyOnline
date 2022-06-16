#include "al/factory/ProjectCameraPoserFactory.h"

ProjectCameraPoserFactory::ProjectCameraPoserFactory() : CameraPoserFactory("プロジェクトカメラファクトリー") {
    alCameraPoserFactoryFunction::initAndCreateTableFromOtherTable2(this, poserEntries, sizeof(poserEntries)/sizeof(poserEntries[0]), poserEntries2, sizeof(poserEntries2)/sizeof(poserEntries2[0]));
};