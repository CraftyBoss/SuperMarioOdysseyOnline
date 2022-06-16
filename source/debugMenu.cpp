#include "debugMenu.hpp"

static const char *DBG_FONT_PATH = "DebugData/Font/nvn_font_jis1.ntx";
static const char *DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char *DBG_TBL_PATH = "DebugData/Font/nvn_font_jis1_tbl.bin";

sead::TextWriter *gTextWriter;

void setupDebugMenu(GameSystem *gSys) {

    sead::Heap *curHeap = al::getCurrentHeap();

    agl::DrawContext *context = gSys->mSystemInfo->mDrawInfo->mDrawContext;

    if(curHeap) {
        if (context) {
            
            sead::DebugFontMgrJis1Nvn::sInstance = sead::DebugFontMgrJis1Nvn::createInstance(curHeap);
            
            if(al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_TBL_PATH)) {
                sead::DebugFontMgrJis1Nvn::sInstance->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH, 0x100000);
                sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::sInstance);
                gTextWriter = new sead::TextWriter(context);
                gTextWriter->setupGraphics(context);
            }

            sead::PrimitiveDrawer drawer(context);
        }
    }

    __asm("MOV W23, #0x3F800000");
    __asm("MOV W8, #0xFFFFFFFF");
}

void drawBackground(agl::DrawContext *context) {
    sead::Vector3<float> p1(-1, .3, 0); // top left
    sead::Vector3<float> p2(-.2, .3, 0); // top right
    sead::Vector3<float> p3(-1, -1, 0); // bottom left
    sead::Vector3<float> p4(-.2, -1, 0); // bottom right
    sead::Color4f c(.1, .1, .1, .9);

    agl::utl::DevTools::beginDrawImm(context, sead::Matrix34<float>::ident, sead::Matrix44<float>::ident);
    agl::utl::DevTools::drawTriangleImm(context, p1, p2, p3, c);
    agl::utl::DevTools::drawTriangleImm(context, p3, p4, p2, c);

}