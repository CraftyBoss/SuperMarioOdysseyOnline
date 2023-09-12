#include <string_view>
#include "al/execute/ExecuteOrder.h"
#include "al/execute/ExecuteTable.h"

#include "al/execute/ExecuteTableHolderDraw.h"
#include "al/execute/ExecuteTableHolderUpdate.h"

static constexpr al::ExecuteOrder drawTableArr[] = {
    // ３Ｄ（カリング）
    {"カリング", "ActorModelDrawCulling", 512, "システム"},
    // ３Ｄ（デプスシャドウ）
    {"デプスシャドウ[キャラクター]", "ActorModelDrawDepthShadow", 192, "影"},
    {"デプスシャドウ[地形]", "ActorModelDrawDepthShadow", 192, "影"},
    {"デプスシャドウ[マーチングキューブ]", "ActorModelDrawDepthShadowMarchingCube", 16, "影"},
    {"デプスシャドウ[独自]", "Functor", 16, "影"},
    // ３Ｄ（デプスシャドウプレイヤー）
    {"デプスシャドウ[プレイヤー]", "ActorModelDrawDepthShadow", 128, "影"},
    {"Mii[顔モデル](デプスシャドウ)", "Draw", 8, "影"},
    // ３Ｄ（スタティックデプスシャドウ）
    {"スタティックデプスシャドウ[地形]", "ActorModelDrawStaticDepthShadow", 128, "影"},
    // ３Ｄ（ワールドAo）
    {"ワールドAo[地形]", "ActorModelDrawWorldAo", 192, "影"},
    // ３Ｄ（海用デプス）
    {"海用デプス[浜辺]", "ActorModelDrawWorldAo", 8, "影"},
    {"海用デプス[高さ]", "ActorModelDrawWorldAo", 8, "影"},
    // ３Ｄ（空）
    {"空", "ActorModelDraw", 8, "地形"},
    // ３Ｄ（不透明Ｚプリパス）
    {"Ｚプリパス[カリング]", "ActorModelDrawDepthOnly", 512, "地形"},
    {"Ｚプリパス[キャラクター]", "ActorModelDrawDepthOnly", 128, "敵"},
    {"Ｚプリパス[地形]", "ActorModelDrawDepthOnly", 128, "地形"},
    {"Ｚプリパス[遠景]", "ActorModelDrawDepthOnly", 128, "地形"},
    {"Ｚプリパス[ディザ]", "ActorModelDrawDepthDither", 196, "敵"},
    {"プレイヤー", "ActorModelDrawDepthDither", 196, "プレイヤー"},
    // ３Ｄ（ディファード地形）
    {"地形オブジェ[地形前]", "ActorModelDrawDeferred", 128, "地形オブジェ"},
    {"地形オブジェ[地形前ディファードのみ]", "ActorModelDrawDeferredOnly", 32, "地形オブジェ"},
    {"地形オブジェ[地形前ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "地形オブジェ"},
    {"敵[地形前]", "ActorModelDrawDeferred", 16, "敵"},
    {"敵[地形前ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "敵"},
    {"ＮＰＣ[地形前]", "ActorModelDrawDeferred", 16, "ＮＰＣ"},
    {"ＮＰＣ[地形前ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "ＮＰＣ"},
    {"プレイヤー[地形前]", "ActorModelDrawDeferred", 16, "プレイヤー"},
    {"地形[浮遊]", "ActorModelDrawDeferred", 32, "地形"},
    {"地形", "ActorModelDrawDeferred", 256, "地形"},
    {"地形[ディファード]", "ActorModelDrawDeferredOnly", 32, "地形"},
    {"地形[ディファードのみ]", "ActorModelDrawDeferredOnly", 32, "地形"},
    {"地形[ディファード不透明]", "ActorModelDrawDeferredOpa", 16, "地形"},
    {"地形[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 64, "地形"},
    {"地形[埋没]", "ActorModelDrawDeferred", 32, "地形"},
    // ３Ｄ（ディファード鏡映り込みなし）
    {"地形[鏡映り込みなし]", "ActorModelDrawDeferred", 32, "地形"},
    // ３Ｄ（ディファードキャラクター）
    {"シャドウマスク[地形オブジェ]", "Draw", 3, "影"},
    {"足跡", "ActorModelDrawDeferredFootPrint", 4, "プレイヤー"},
    {"地形オブジェ", "ActorModelDrawDeferred", 128, "地形オブジェ"},
    {"地形オブジェ[ディファードのみ]", "ActorModelDrawDeferredOnly", 16, "地形オブジェ"},
    {"地形オブジェ[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "地形オブジェ"},
    {"地形オブジェ[マーチングキューブ]", "ActorModelDrawDeferredMarchingCube", 32, "地形オブジェ"},
    {"地形[地形オブジェ後]", "ActorModelDrawDeferred", 32, "地形"},
    {"敵[シルエット前]", "ActorModelDrawDeferred", 128, "敵"},
    {"アクター描画[シルエット前]", "ActorDraw", 8, "アクター"},
    {"シルエット[プレイヤー]", "ActorModelDrawDeferredSilhouette", 196, "プレイヤー"},
    {"シルエット[オブジェ]", "ActorModelDrawDeferredSilhouette", 64, "地形オブジェ"},
    {"シルエットモデル[敵]", "ActorModelDrawDeferred", 64, "敵"},
    {"地形[シルエット後]", "ActorModelDrawDeferred", 32, "地形"},
    {"地形オブジェ[シルエット後]", "ActorModelDrawDeferred", 32, "地形オブジェ"},
    {"シャドウマスク[敵]", "Draw", 3, "影"},
    {"敵", "ActorModelDrawDeferred", 128, "敵"},
    {"敵[ディファードのみ]", "ActorModelDrawDeferredOnly", 16, "敵"},
    {"敵[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "敵"},
    {"ＮＰＣ", "ActorModelDrawDeferred", 96, "ＮＰＣ"},
    {"ＮＰＣ[ディファードのみ]", "ActorModelDrawDeferredOnly", 8, "ＮＰＣ"},
    {"ＮＰＣ[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 8, "ＮＰＣ"},
    {"Mii[顔モデル]", "Draw", 4, "システム"},
    {"シャドウマスク[アイテム]", "Draw", 3, "影"},
    {"アイテム", "ActorModelDrawDeferred", 64, "アイテム"},
    {"アイテム[ディファードのみ]", "ActorModelDrawDeferredOnly", 8, "アイテム"},
    {"アイテム[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 8, "アイテム"},
    // ３Ｄ（ディファード異空間）
    {"異空間オブジェ", "ActorModelDrawDeferred", 64, "地形オブジェ"},
    // ３Ｄ（ディファードプレイヤー）
    {"シャドウマスク[プレイヤー]", "Draw", 4, "影"},
    {"プレイヤー", "ActorModelDrawDeferred", 196, "プレイヤー"},
    {"プレイヤー装飾", "ActorModelDrawDeferred", 32, "プレイヤー"},
    {"プレイヤー装飾[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 16, "プレイヤー"},
    // ３Ｄ（ディファード中景）
    {"地形オブジェ[キャラ後]", "ActorModelDrawDeferred", 32, "地形オブジェ"},
    {"シャドウマスク[ブロック]", "Draw", 3, "影"},
    {"中景", "ActorModelDrawDeferred", 8, "地形"},
    {"中景[ディファードのみ]", "ActorModelDrawDeferredOnly", 8, "地形"},
    {"中景[ディファード不透明のみ]", "ActorModelDrawDeferredOpa", 8, "地形"},
    {"大気散乱", "Draw", 1, "地形"},
    {"ディファード空", "ActorModelDrawDeferredSky", 16, "地形"},
    {"ディファード空[デモ]", "ActorModelDrawDeferredSky", 8, "地形"},
    // ３Ｄ（ディファード半透明）
    {"地形[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "地形"},
    {"地形[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 8, "地形"},
    {"地形オブジェ[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "地形オブジェ"},
    {"地形オブジェ[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 8, "地形オブジェ"},
    {"敵[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "敵"},
    {"敵[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 8, "敵"},
    {"ＮＰＣ[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "ＮＰＣ"},
    {"ＮＰＣ[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 8, "ＮＰＣ"},
    {"アイテム[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "アイテム"},
    {"アイテム[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 8, "アイテム"},
    {"プレイヤー装飾[ディファード半透明]", "ActorModelDrawDeferredXlu", 8, "プレイヤー"},
    {"プレイヤー装飾[ディファード半透明のみ]", "ActorModelDrawDeferredXlu", 16, "プレイヤー"},
    {"シャドウマスク[モデルライト後]", "Draw", 4, "影"},
    {"アクター描画", "ActorDraw", 8, "アクター"},
    // ３Ｄ（デプスクリアプレイヤー）
    {"プレイヤー", "ActorModelDrawDepthForce", 196, "プレイヤー"},
    {"プレイヤー装飾[ディファード不透明のみ]", "ActorModelDrawDepthForce", 16, "プレイヤー"},
    {"プレイヤー装飾[ディファード半透明のみ]", "ActorModelDrawDepthForce", 16, "プレイヤー"},
    {"プレイヤー装飾[フォワードのみ]", "ActorModelDrawDepthForce", 16, "プレイヤー"},
    {"プレイヤー装飾[インダイレクトのみ]", "ActorModelDrawDepthForce", 16, "プレイヤー"},
    // ３Ｄ（フォワード遠景）
    {"遠景[ライトバッファ]", "ActorModelDraw", 8, "地形"},
    {"遠景[ライトバッファのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"大気散乱雲遠距離[ライトバッファ]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲遠距離[ライトバッファのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"大気散乱雲[ライトバッファ]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲[ライトバッファのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"大気散乱雲近距離[ライトバッファ]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲近距離[ライトバッファのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    // ３Ｄ（フォワードプレイヤー）
    {"Ｚプリパス[プレイヤー]", "ActorModelDrawDepthOnly", 32, "プレイヤー"},
    {"プレイヤー[地形前]", "ActorModelDrawForwardForce", 16, "プレイヤー"},
    {"プレイヤー", "ActorModelDrawForwardForce", 196, "プレイヤー"},
    {"Ｚプリパス[プレイヤー装飾]", "ActorModelDrawDepthDither", 128, "プレイヤー"},
    {"プレイヤー装飾", "ActorModelDrawForwardForce", 32, "プレイヤー"},
    {"プレイヤー装飾[ディファード不透明のみ]", "ActorModelDrawForwardForce", 16, "プレイヤー"},
    // ３Ｄ（フォワード）
    {"半透明Ｚプリパス", "ActorModelDrawDepthXlu", 8, "地形"},
    {"フォワードＺプリパス[ディザ]", "ActorModelDrawDepthDither", 8, "地形"},
    {"中景[フォワード]", "ActorModelDraw", 8, "地形"},
    {"中景[フォワードのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"大気散乱雲[フォワード]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲[フォワードのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"地形[フォワード]", "ActorModelDraw", 32, "地形"},
    {"地形[フォワードのみ]", "ActorModelDrawForwardOnly", 48, "地形"},
    {"地形オブジェ[フォワード]", "ActorModelDraw", 32, "地形オブジェ"},
    {"地形オブジェ[フォワードのみ]", "ActorModelDrawForwardOnly", 32, "地形オブジェ"},
    {"敵[フォワード]", "ActorModelDraw", 32, "敵"},
    {"敵[フォワードのみ]", "ActorModelDrawForwardOnly", 16, "敵"},
    {"ＮＰＣ[フォワード]", "ActorModelDraw", 32, "ＮＰＣ"},
    {"ＮＰＣ[フォワードのみ]", "ActorModelDrawForwardOnly", 8, "ＮＰＣ"},
    {"アイテム[フォワード]", "ActorModelDraw", 32, "アイテム"},
    {"アイテム[フォワードのみ]", "ActorModelDrawForwardOnly", 8, "アイテム"},
    {"プレイヤー[フォワード]", "ActorModelDraw", 8, "プレイヤー"},
    {"プレイヤー装飾[フォワード]", "ActorModelDraw", 8, "プレイヤー"},
    {"プレイヤー装飾[フォワードのみ]", "ActorModelDrawForwardOnly", 16, "プレイヤー"},
    {"アクター描画[フォワード]", "ActorDraw", 8, "アクター"},
    // ３Ｄ（インダイレクト）
    {"半透明Ｚプリパス[インダイレクト]", "ActorModelDrawDepthIndirect", 8, "地形"},
    {"インダイレクトＺプリパス[ディザ]", "ActorModelDrawDepthDitherIndirect", 8, "地形"},
    {"地形[インダイレクト]", "ActorModelDrawIndirect", 32, "地形"},
    {"地形[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 16, "地形"},
    {"地形オブジェ[インダイレクト]", "ActorModelDrawIndirect", 32, "地形オブジェ"},
    {"地形オブジェ[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 32, "地形オブジェ"},
    {"コイン[インダイレクト]", "ActorModelDrawIndirect", 8, "アイテム"},
    {"ルート土管内側[インダイレクト]", "ActorModelDrawIndirect", 32, "地形オブジェ"},
    {"ルート土管外側[インダイレクト]", "ActorModelDrawIndirect", 32, "地形オブジェ"},
    {"敵[インダイレクト]", "ActorModelDrawIndirect", 32, "敵"},
    {"敵[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 8, "敵"},
    {"ＮＰＣ[インダイレクト]", "ActorModelDrawIndirect", 32, "ＮＰＣ"},
    {"ＮＰＣ[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 8, "ＮＰＣ"},
    {"アイテム[インダイレクト]", "ActorModelDrawIndirect", 32, "アイテム"},
    {"アイテム[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 32, "アイテム"},
    {"プレイヤー装飾[インダイレクト]", "ActorModelDrawIndirect", 8, "プレイヤー"},
    {"プレイヤー装飾[インダイレクトのみ]", "ActorModelDrawIndirectOnly", 8, "プレイヤー"},
    {"アクター描画[インダイレクト]", "ActorDraw", 8, "アクター"},
    // ３Ｄ（インダイレクト後フォワード）
    {"半透明Ｚプリパス[インダイレクト後]", "ActorModelDrawDepthIndirect", 8, "地形"},
    {"地形オブジェ[フォワードインダイレクト後のみ]", "ActorModelDrawForwardOnly", 8,
     "地形オブジェ"},
    {"敵[フォワードインダイレクト後]", "ActorModelDraw", 32, "敵"},
    // ３Ｄ（インダイレクト後遠景）
    {"大気散乱雲[インダイレクト後]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲[インダイレクト後のみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    // ３Ｄ（フォグ後インダイレクト）
    {"地形[インダイレクトフォグ後]", "ActorModelDrawIndirect", 8, "地形"},
    {"地形[インダイレクトフォグ後のみ]", "ActorModelDrawIndirectOnly", 8, "地形"},
    {"敵[インダイレクトフォグ後]", "ActorModelDrawIndirect", 8, "敵"},
    {"敵[インダイレクトフォグ後のみ]", "ActorModelDrawIndirectOnly", 8, "敵"},
    {"アイテム[インダイレクトフォグ後]", "ActorModelDrawIndirect", 32, "アイテム"},
    {"アイテム[インダイレクトフォグ後のみ]", "ActorModelDrawIndirectOnly", 32, "アイテム"},
    // ３Ｄ（フォグ後遠景）
    {"遠景[フォグ後]", "ActorModelDraw", 8, "地形"},
    {"遠景[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"大気散乱雲[フォグ後]", "ActorModelDraw", 8, "地形"},
    {"大気散乱雲[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    // ３Ｄ（フォグ後）
    {"半透明Ｚプリパス[フォグ後]", "ActorModelDrawDepthXlu", 8, "地形"},
    {"地形[フォグ後]", "ActorModelDraw", 8, "地形"},
    {"地形[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"地形オブジェ[フォグ後]", "ActorModelDraw", 8, "地形オブジェ"},
    {"地形オブジェ[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "地形オブジェ"},
    {"敵[フォグ後]", "ActorModelDraw", 8, "敵"},
    {"敵[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "敵"},
    {"ＮＰＣ[フォグ後]", "ActorModelDraw", 8, "ＮＰＣ"},
    {"ＮＰＣ[フォグ後のみ]", "ActorModelDrawForwardOnly", 8, "ＮＰＣ"},
    // ３Ｄ（クロマキーＺプリパス）
    {"Ｚプリパス[プレイヤークロマキー]", "ActorModelDrawDepthChromakey", 208, "プレイヤー"},
    {"Ｚプリパス[ＮＰＣクロマキー]", "ActorModelDrawDepthChromakey", 32, "ＮＰＣ"},
    {"Ｚプリパス[ディザクロマキー]", "ActorModelDrawDitherChromakey", 208, "プレイヤー"},
    // ３Ｄ（クロマキープレイヤー）
    {"プレイヤー[クロマキー]", "ActorModelDrawPlayerChromakey", 208, "プレイヤー"},
    {"プレイヤー[クロマキー不透明]", "ActorModelDrawPlayerChromakeyOpa", 208, "プレイヤー"},
    {"プレイヤー[クロマキー半透明]", "ActorModelDrawPlayerChromakeyXlu", 64, "プレイヤー"},
    // ３Ｄ（クロマキーキャラクター）
    {"ＮＰＣ[クロマキー]", "ActorModelDrawCharacterChromakey", 32, "ＮＰＣ"},
    // ２Ｄバック（メイン画面）
    {"２Ｄバック", "LayoutDraw", 64, "レイアウト"},
    // ２Ｄベース（メイン画面）
    {"２Ｄベース", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄ情報バルーン", "LayoutDraw", 64, "レイアウト"},
    {"２Ｄ会話バルーン", "LayoutDraw", 128, "レイアウト"},
    {"２Ｄ", "LayoutDraw", 256, "レイアウト"},
    {"２Ｄフィルターバルーン", "LayoutDraw", 64, "レイアウト"},
    {"２Ｄフィルター", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄ（メイン画面のみ）", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄガイド", "LayoutDraw", 64, "レイアウト"},
    {"２Ｄカウンター", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄマップアイコン", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄ通知", "LayoutDraw", 8, "レイアウト"},
    // ２Ｄエフェクト（メイン画面）
    {"２Ｄベースエフェクト", "Draw", 1, "エフェクト"},
    // ２Ｄオーバー（メイン画面）
    {"２Ｄヘッド", "LayoutDraw", 16, "レイアウト"},
    {"２Ｄポーズ", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄランキング", "LayoutDraw", 4, "レイアウト"},
    {"２Ｄライン", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄアイコン[最低]", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄアイコン[低]", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄアイコン[中]", "LayoutDraw", 16, "レイアウト"},
    {"２Ｄアイコン[高]", "LayoutDraw", 356, "レイアウト"},
    {"２Ｄアイコン[最高]", "LayoutDraw", 16, "レイアウト"},
    {"２Ｄカーソル", "LayoutDraw", 12, "レイアウト"},
    {"２Ｄリスト", "LayoutDraw", 12, "レイアウト"},
    {"２Ｄリストアイコン", "LayoutDraw", 256, "レイアウト"},
    {"２Ｄリストカーソル", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄゲームオーバー", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄカバー", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄエフェクト", "Draw", 1, "エフェクト"},
    {"２Ｄワイプ[ウィンドウ前]", "LayoutDraw", 4, "レイアウト"},
    {"２Ｄウィンドウ", "LayoutDraw", 24, "レイアウト"},
    {"２Ｄウィンドウカウンター", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄワイプ", "LayoutDraw", 48, "レイアウト"},
    {"２Ｄリザルト", "LayoutDraw", 4, "レイアウト"},
    // ２Ｄ（デモ画面）
    {"２Ｄデモベース", "LayoutDraw", 16, "レイアウト"},
    {"２Ｄデモ", "LayoutDraw", 96, "レイアウト"},
    {"２Ｄデモ情報バルーン", "LayoutDraw", 16, "レイアウト"},
    {"２Ｄデモライン", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄデモアイコン", "LayoutDraw", 196, "レイアウト"},
    {"２Ｄデモアイコンオーバー", "LayoutDraw", 128, "レイアウト"},
    {"２Ｄデモアイコンプレイヤー", "LayoutDraw", 4, "レイアウト"},
    {"２Ｄデモカーソル", "LayoutDraw", 8, "レイアウト"},
    // ポストエフェクトマスク
    {"ポストエフェクトマスク", "ActorModelDrawPostEffectMask", 32, "地形"},
    // アクター描画（独自レンダーターゲット）
    {"アクター描画[独自レンダーターゲット]", "ActorDraw", 8, "アクター"},
    // アクター描画（プロジェクト固有）
    {"アクター描画（プロジェクト固有）", "ActorDraw", 8, "アクター"},
    // モデル描画バッファ更新
    {"モデル描画バッファ更新", "ActorModelDrawUpdate", 1024, "システム"},
    // ３Ｄ（ワールドマップディファード）
    {"ワールドマップ地形", "ActorModelDrawDeferred", 128, "地形"},
    {"ワールドマップ地形[ディファードのみ]", "ActorModelDrawDeferredOnly", 8, "地形"},
    {"ワールドマップディファード空", "ActorModelDrawDeferredSky", 8, "地形"},
    {"ワールドマップ地形[ディファード半透明]", "ActorModelDrawDeferredXlu", 16, "地形"},
    // ３Ｄ（ワールドマップフォワード）
    {"ワールドマップ地形[フォワード]", "ActorModelDraw", 32, "地形"},
    {"ワールドマップ地形[フォワードのみ]", "ActorModelDrawForwardOnly", 8, "地形"},
    {"ワールドマップ地形オブジェ[フォワード]", "ActorModelDraw", 8, "地形オブジェ"},
    // ２Ｄ（ワールドマップ画面）
    {"２Ｄワールドマップベース", "LayoutDraw", 32, "レイアウト"},
    {"２Ｄワールドマップ", "LayoutDraw", 32, "レイアウト"},
    // ２Ｄ（ムーンゲット画面）
    {"２Ｄ（ムーンゲット）", "LayoutDraw", 8, "レイアウト"},
    {"２Ｄカウンター（ムーンゲット）", "LayoutDraw", 1, "レイアウト"},
    {"２Ｄワイプ（ムーンゲット）", "LayoutDraw", 4, "レイアウト"},
    // ２Ｄ（スナップショット）
    {"２Ｄスナップショット", "LayoutDraw", 3, "レイアウト"},
    // ２Ｄ（撮影用）
    {"２Ｄ撮影用", "LayoutDraw", 16, "レイアウト"},
    // ２Ｄ（ミス）
    {"２Ｄミス", "LayoutDraw", 2, "レイアウト"},
    // Custom Entries
    {"PuppetActor", "ActorModelDrawDeferred", 512, "ボス"}
};

static constexpr al::ExecuteOrder updateTableArr[] = {
    // Update Table Name: 更新
    {"ステージ同期カウンタ", "Execute", 1, "システム"},
    {"乗り物（カメラ前）[Movement]", "ActorMovement", 8, "乗り物"},
    {"カメラ前プレイヤー[Movement]", "ActorMovement", 16, "プレイヤー"},
    {"カメラ前プレイヤー", "ActorMovementCalcAnim", 16, "プレイヤー"},
    {"カメラ", "Execute", 1, "カメラ"},
    {"クリッピング", "Execute", 1, "システム"},
    {"センサー", "Execute", 1, "システム"},
    {"試作用処理1", "Execute", 2, "システム"},
    {"試作用処理2", "Execute", 8, "システム"},
    {"試作用処理3", "Execute", 2, "システム"},
    {"試作用処理4", "Execute", 1, "システム"},
    {"空", "ActorMovementCalcAnim", 16, "地形"},
    {"波", "ActorMovement", 16, "地形"},
    {"遠景", "ActorMovementCalcAnim", 8, "地形"},
    {"コリジョン地形", "ActorMovementCalcAnim", 256, "地形"},
    {"コリジョン地形[デモ]", "ActorMovementCalcAnim", 64, "地形"},
    {"コリジョン地形[Movement]", "ActorMovement", 32, "地形"},
    {"コリジョン地形装飾", "ActorMovementCalcAnim", 32, "地形"},
    {"コリジョン地形装飾[Movement]", "ActorMovement", 32, "地形"},
    {"コリジョン地形オブジェ", "ActorMovementCalcAnim", 64, "地形オブジェ"},
    {"コリジョン地形オブジェ[Movement]", "ActorMovement", 32, "地形オブジェ"},
    {"コリジョンディレクター", "Execute", 1, "システム"},
    {"地形オブジェ", "ActorMovementCalcAnim", 128, "地形オブジェ"},
    {"地形オブジェ[Movement]", "ActorMovement", 32, "地形オブジェ"},
    {"地形オブジェ装飾", "ActorMovementCalcAnim", 32, "地形オブジェ"},
    {"乗り物", "ActorMovementCalcAnim", 32, "乗り物"},
    {"エフェクトオブジェ", "ActorMovement", 32, "エフェクト"},
    {"デモプレイヤーロケーター", "ActorMovementCalcAnim", 4, "プレイヤー"},
    {"デモプレイヤー前処理", "ActorMovement", 16, "プレイヤー"},
    {"プレイヤー前処理", "Functor", 1, "プレイヤー"},
    {"プレイヤー[Movement]", "ActorMovement", 16, "プレイヤー"},
    {"プレイヤー", "ActorMovementCalcAnim", 128, "プレイヤー"},
    {"プレイヤー後処理", "Functor", 1, "プレイヤー"},
    {"プレイヤー装飾", "ActorMovementCalcAnim", 64, "プレイヤー"},
    {"プレイヤー装飾２", "ActorMovementCalcAnim", 64, "プレイヤー"},
    {"帽子(武器)", "ActorMovementCalcAnim", 1, "アイテム"},
    {"帽子(表示)", "ActorMovementCalcAnim", 16, "アイテム"},
    {"敵", "ActorMovementCalcAnim", 128, "敵"},
    {"敵[Movement]", "ActorMovement", 32, "敵"},
    {"敵装飾", "ActorMovementCalcAnim", 32, "敵"},
    {"敵装飾[Movement]", "ActorMovement", 32, "敵"},
    {"デモ", "ActorMovementCalcAnim", 32, "地形"},
    {"デモ装飾", "ActorMovementCalcAnim", 32, "地形"},
    {"デモオブジェクト", "ActorMovement", 32, "地形"},
    {"ＮＰＣ", "ActorMovementCalcAnim", 64, "ＮＰＣ"},
    {"ＮＰＣ装飾", "ActorMovementCalcAnim", 32, "ＮＰＣ"},
    {"帽子装着位置更新", "Functor", 8, "システム"},
    {"NPCイベントディレクター", "Execute", 1, "システム"},
    {"エリア監視オブジェ", "Execute", 8, "システム"},
    {"通知レイアウト更新", "Execute", 3, "システム"},
    {"バルーン位置更新", "Execute", 1, "システム"},
    {"ネットワーク", "Execute", 2, "システム"},
    {"プレイヤーゴースト管理", "Execute", 1, "プレイヤー"},
    {"エコーエミッター管理", "Execute", 1, "地形オブジェ"},
    {"メッシュ変形モデル管理", "Execute", 1, "地形オブジェ"},
    {"アイテム", "ActorMovementCalcAnim", 64, "アイテム"},
    {"アイテム[デモ]", "ActorMovementCalcAnim", 64, "アイテム"},
    {"アイテム[Movement]", "ActorMovement", 16, "アイテム"},
    {"シャドウマスク", "ActorMovement", 64, "影"},
    {"グラフィックス要求者", "ActorMovement", 64, "システム"},
    {"プロジェクト用グラフィックス", "Execute", 64, "システム"},
    {"監視オブジェ", "ActorMovement", 32, "システム"},
    {"キッズルートガイド管理", "ActorMovement", 1, "システム"},
    {"キッズルートガイド", "ActorMovementCalcAnim", 4, "システム"},
    {"サウンド制御", "ActorMovement", 10, "システム"},
    {"ステージスイッチディレクター", "Execute", 1, "システム"},
    {"２Ｄ", "LayoutUpdate", 404, "レイアウト"},
    {"２Ｄ（ポーズ無視）", "LayoutUpdate", 360, "レイアウト"},
    {"エフェクト（前処理）", "Functor", 1, "エフェクト"},
    {"エフェクト（３Ｄ）", "Execute", 1, "エフェクト"},
    {"エフェクト（プレイヤー）", "Execute", 1, "エフェクト"},
    {"エフェクト（Ｚソート）", "Execute", 1, "エフェクト"},
    {"エフェクト（カメラデモ）", "Execute", 1, "エフェクト"},
    {"エフェクト（カメラ前エフェクト）", "Execute", 1, "エフェクト"},
    {"エフェクト（ベース２Ｄ）", "Execute", 1, "エフェクト"},
    {"エフェクト（２Ｄ）", "Execute", 1, "エフェクト"},
    {"エフェクト（後処理）", "Functor", 1, "エフェクト"},
    // Update Table Name: ビュー更新(コア1)
    {"ビュー更新(コア1)", "ActorCalcView", 512, "システム"},
    // Update Table Name: ビュー更新(コア2)
    {"ビュー更新(コア2)", "ActorCalcView", 1024, "システム"},
    // Update Table Name: スナップショット
    {"スナップショット[CalcAnim]", "ActorCalcAnim", 16, "NPC"},
    {"スナップショット[ActorMovement]", "ActorMovement", 1, "地形オブジェ"},
    // Custom Tables
    {"PuppetActor", "ActorMovementCalcAnim", 512, "ボス"}
};

static constexpr int getUpdateTableIndex(const char* listName) {
    for (int i = 0; i < sizeof(updateTableArr) / sizeof(updateTableArr[0]); i++) {
        if (std::string_view(updateTableArr[i].mListName)==listName) {
            return i;
        }
    }
    return 0;
}

static constexpr al::ExecuteTable createUpdateTable(const char* tableName, const char* startListName, const char* endListName) {
    al::ExecuteTable drawTable;
    drawTable.mName = tableName;
    int startIndex = getUpdateTableIndex(startListName);
    drawTable.mExecuteOrders = &updateTableArr[startIndex];
    drawTable.mExecuteOrderCount = (getUpdateTableIndex(endListName) - startIndex) + 1;
    return drawTable;
}

static constexpr int getDrawTableIndex(const char* listName, const char *groupName) {
    for (int i = 0; i < sizeof(drawTableArr)/sizeof(drawTableArr[0]); i++) {
        if (std::string_view(drawTableArr[i].mListName)==listName && std::string_view(drawTableArr[i].mExecuteGroup)==groupName) {
            return i;
        }
    }
    return 0;
}

static constexpr al::ExecuteTable createDrawTable(const char* tableName, const char* startListName, const char *groupStartName,  const char* endListName, const char *groupEndName) {
    al::ExecuteTable drawTable;
    drawTable.mName = tableName;
    int startIndex = getDrawTableIndex(startListName, groupStartName);
    drawTable.mExecuteOrders = &drawTableArr[startIndex];
    drawTable.mExecuteOrderCount = (getDrawTableIndex(endListName, groupEndName) - startIndex) + 1;
    return drawTable;
}

constexpr al::ExecuteTable drawTable[] = {
    createDrawTable("３Ｄ（カリング）", "カリング", "ActorModelDrawCulling", "カリング", "ActorModelDrawCulling"),
    createDrawTable("３Ｄ（デプスシャドウ）", "デプスシャドウ[キャラクター]", "ActorModelDrawDepthShadow", "デプスシャドウ[独自]", "Functor"),
    createDrawTable("３Ｄ（デプスシャドウプレイヤー）", "デプスシャドウ[プレイヤー]", "ActorModelDrawDepthShadow", "Mii[顔モデル](デプスシャドウ)", "Draw"),
    createDrawTable("３Ｄ（スタティックデプスシャドウ）", "スタティックデプスシャドウ[地形]", "ActorModelDrawStaticDepthShadow", "スタティックデプスシャドウ[地形]", "ActorModelDrawStaticDepthShadow"),
    createDrawTable("３Ｄ（ワールドAo）", "ワールドAo[地形]", "ActorModelDrawWorldAo", "ワールドAo[地形]", "ActorModelDrawWorldAo"),
    createDrawTable("３Ｄ（海用デプス）", "海用デプス[浜辺]", "ActorModelDrawWorldAo", "海用デプス[高さ]", "ActorModelDrawWorldAo"),
    createDrawTable("３Ｄ（空）", "空", "ActorModelDraw", "空", "ActorModelDraw"),
    createDrawTable("３Ｄ（不透明Ｚプリパス）", "Ｚプリパス[カリング]", "ActorModelDrawDepthOnly", "プレイヤー", "ActorModelDrawDepthDither"),
    createDrawTable("３Ｄ（ディファード地形）", "地形オブジェ[地形前]", "ActorModelDrawDeferred", "地形[埋没]", "ActorModelDrawDeferred"),
    createDrawTable("３Ｄ（ディファード鏡映り込みなし）", "地形[鏡映り込みなし]", "ActorModelDrawDeferred", "地形[鏡映り込みなし]", "ActorModelDrawDeferred"),
    createDrawTable("３Ｄ（ディファードキャラクター）", "シャドウマスク[地形オブジェ]", "Draw", "アイテム[ディファード不透明のみ]", "ActorModelDrawDeferredOpa"),
    createDrawTable("３Ｄ（ディファード異空間）", "異空間オブジェ", "ActorModelDrawDeferred", "異空間オブジェ", "ActorModelDrawDeferred"),
    createDrawTable("３Ｄ（ディファードプレイヤー）", "シャドウマスク[プレイヤー]", "Draw", "プレイヤー装飾[ディファード不透明のみ]", "ActorModelDrawDeferredOpa"),
    createDrawTable("３Ｄ（ディファード中景）", "地形オブジェ[キャラ後]", "ActorModelDrawDeferred", "ディファード空[デモ]", "ActorModelDrawDeferredSky"),
    createDrawTable("３Ｄ（ディファード半透明）", "地形[ディファード半透明]", "ActorModelDrawDeferredXlu", "アクター描画", "ActorDraw"),
    createDrawTable("３Ｄ（デプスクリアプレイヤー）", "プレイヤー", "ActorModelDrawDepthForce", "プレイヤー装飾[インダイレクトのみ]", "ActorModelDrawDepthForce"),
    createDrawTable("３Ｄ（フォワード遠景）", "遠景[ライトバッファ]", "ActorModelDraw", "大気散乱雲近距離[ライトバッファのみ]", "ActorModelDrawForwardOnly"),
    createDrawTable("３Ｄ（フォワードプレイヤー）", "Ｚプリパス[プレイヤー]", "ActorModelDrawDepthOnly", "プレイヤー装飾[ディファード不透明のみ]", "ActorModelDrawForwardForce"),
    createDrawTable("３Ｄ（フォワード）", "半透明Ｚプリパス", "ActorModelDrawDepthXlu", "アクター描画[フォワード]", "ActorDraw"),
    createDrawTable("３Ｄ（インダイレクト）", "半透明Ｚプリパス[インダイレクト]", "ActorModelDrawDepthIndirect", "アクター描画[インダイレクト]", "ActorDraw"),
    createDrawTable("３Ｄ（インダイレクト後フォワード）", "半透明Ｚプリパス[インダイレクト後]", "ActorModelDrawDepthIndirect", "敵[フォワードインダイレクト後]", "ActorModelDraw"),
    createDrawTable("３Ｄ（インダイレクト後遠景）", "大気散乱雲[インダイレクト後]", "ActorModelDraw", "大気散乱雲[インダイレクト後のみ]", "ActorModelDrawForwardOnly"),
    createDrawTable("３Ｄ（フォグ後インダイレクト）", "地形[インダイレクトフォグ後]", "ActorModelDrawIndirect", "アイテム[インダイレクトフォグ後のみ]", "ActorModelDrawIndirectOnly"),
    createDrawTable("３Ｄ（フォグ後遠景）", "遠景[フォグ後]", "ActorModelDraw", "大気散乱雲[フォグ後のみ]", "ActorModelDrawForwardOnly"),
    createDrawTable("３Ｄ（フォグ後）", "半透明Ｚプリパス[フォグ後]", "ActorModelDrawDepthXlu", "ＮＰＣ[フォグ後のみ]", "ActorModelDrawForwardOnly"),
    createDrawTable("３Ｄ（クロマキーＺプリパス）", "Ｚプリパス[プレイヤークロマキー]", "ActorModelDrawDepthChromakey", "Ｚプリパス[ディザクロマキー]", "ActorModelDrawDitherChromakey"),
    createDrawTable("３Ｄ（クロマキープレイヤー）", "プレイヤー[クロマキー]", "ActorModelDrawPlayerChromakey", "プレイヤー[クロマキー半透明]", "ActorModelDrawPlayerChromakeyXlu"),
    createDrawTable("３Ｄ（クロマキーキャラクター）", "ＮＰＣ[クロマキー]", "ActorModelDrawCharacterChromakey", "ＮＰＣ[クロマキー]", "ActorModelDrawCharacterChromakey"),
    createDrawTable("２Ｄバック（メイン画面）", "２Ｄバック", "LayoutDraw", "２Ｄバック", "LayoutDraw"),
    createDrawTable("２Ｄベース（メイン画面）", "２Ｄベース", "LayoutDraw", "２Ｄ通知", "LayoutDraw"),
    createDrawTable("２Ｄエフェクト（メイン画面）", "２Ｄベースエフェクト", "Draw", "２Ｄベースエフェクト", "Draw"),
    createDrawTable("２Ｄオーバー（メイン画面）", "２Ｄヘッド", "LayoutDraw", "２Ｄリザルト", "LayoutDraw"),
    createDrawTable("２Ｄ（デモ画面）", "２Ｄデモベース", "LayoutDraw", "２Ｄデモカーソル", "LayoutDraw"),
    createDrawTable("ポストエフェクトマスク", "ポストエフェクトマスク", "ActorModelDrawPostEffectMask", "ポストエフェクトマスク", "ActorModelDrawPostEffectMask"),
    createDrawTable("アクター描画（独自レンダーターゲット）", "アクター描画[独自レンダーターゲット]", "ActorDraw", "アクター描画[独自レンダーターゲット]", "ActorDraw"),
    createDrawTable("アクター描画（プロジェクト固有）", "アクター描画（プロジェクト固有）", "ActorDraw", "アクター描画（プロジェクト固有）", "ActorDraw"),
    createDrawTable("モデル描画バッファ更新", "モデル描画バッファ更新", "ActorModelDrawUpdate", "モデル描画バッファ更新", "ActorModelDrawUpdate"),
    createDrawTable("３Ｄ（ワールドマップディファード）", "ワールドマップ地形", "ActorModelDrawDeferred", "ワールドマップ地形[ディファード半透明]", "ActorModelDrawDeferredXlu"),
    createDrawTable("３Ｄ（ワールドマップフォワード）", "ワールドマップ地形[フォワード]", "ActorModelDraw", "ワールドマップ地形オブジェ[フォワード]", "ActorModelDraw"),
    createDrawTable("２Ｄ（ワールドマップ画面）", "２Ｄワールドマップベース", "LayoutDraw", "２Ｄワールドマップ", "LayoutDraw"),
    createDrawTable("２Ｄ（ムーンゲット画面）", "２Ｄ（ムーンゲット）", "LayoutDraw", "２Ｄワイプ（ムーンゲット）", "LayoutDraw"),
    createDrawTable("２Ｄ（スナップショット）", "２Ｄスナップショット", "LayoutDraw", "２Ｄスナップショット", "LayoutDraw"),
    createDrawTable("２Ｄ（撮影用）", "２Ｄ撮影用", "LayoutDraw", "２Ｄ撮影用", "LayoutDraw"),
    createDrawTable("２Ｄ（ミス）", "２Ｄミス", "LayoutDraw", "２Ｄミス", "LayoutDraw"),
    // Custom Tables
    createDrawTable("OnlineDrawExecutors", "PuppetActor", "ActorModelDrawDeferred", "PuppetActor", "ActorModelDrawDeferred"),
};

int drawTableSize = sizeof(drawTable)/sizeof(drawTable[0]);

constexpr al::ExecuteTable updateTable[] = {
    createUpdateTable("更新", "ステージ同期カウンタ", "エフェクト（後処理）"),
    createUpdateTable("ビュー更新(コア1)", "ビュー更新(コア1)", "ビュー更新(コア1)"),
    createUpdateTable("ビュー更新(コア2)", "ビュー更新(コア2)", "ビュー更新(コア2)"),
    createUpdateTable("スナップショット", "スナップショット[CalcAnim]", "スナップショット[ActorMovement]"),
    // Custom Tables
    createUpdateTable("OnlineUpdateExecutors", "PuppetActor", "PuppetActor"),
};

int updateTableSize = sizeof(updateTable)/sizeof(updateTable[0]);