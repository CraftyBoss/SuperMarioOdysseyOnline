#pragma once

#include "sead/devenv/seadDebugFontMgrNvn.h"
#include "sead/gfx/seadPrimitiveRenderer.h"
#include "sead/gfx/seadTextWriter.h"
#include "sead/basis/seadNew.h"
#include "sead/gfx/seadViewport.h"

#include "agl/DrawContext.h"
#include "agl/utl.h"

#include "game/System/GameSystem.h"

#include "al/util.hpp"
#include "logger.hpp"

extern sead::TextWriter *gTextWriter;

bool setupDebugMenu(agl::DrawContext* context, sead::Viewport* viewport);

void drawBackground(agl::DrawContext *context);