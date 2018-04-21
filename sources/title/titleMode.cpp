
//================================================================================================
//
// タイトル管理 [TitleMode.cpp]
// Author : TAKUYA EBIHARA
//
//================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "TitleMode.h"
#include "../game/gameMode.h"
#include "../interface/fade.h"
#include "../interface/scene.h"
#include "../interface/scene2D.h"
#include "TitleBG.h"
//#include "TitleBG2.h"
//#include "TitleLogo.h"
//#include "TitleStart.h"
#include "../interface/input.h"
#include "../interface/sound.h"
//#include "TextureManager.h"

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CTitleMode::Init(void)
{
    CManager::mode = MODE_TITLE;
    // テクスチャ読み込み
    //for (int i = 0; i < TEXTURE_MAX; i++) {
    //    CManager::GetTextureManager()->Load(CManager::GetTextureManager()->getTextureName((TEX_PARAM)i));
    //}
    CTitleBG::Create();
    //CTitleBG2::Create();
    //CTitleLogo::Create();
    //CTitleStart::Create();

    //CManager::GetSound()->PlaySound(SOUND_LABEL_TITLE);

    return 0;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CTitleMode::Uninit(void)
{
    //オブジェクトの解放
    CScene::ReleaseAll();

    //CManager::GetSound()->StopSound(SOUND_LABEL_TITLE);

}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CTitleMode::Update(void)
{
    if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN)) {
        CFade::SetFade(FADE_OUT, new CGameMode);
    }
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CTitleMode::Draw(void)
{
}
