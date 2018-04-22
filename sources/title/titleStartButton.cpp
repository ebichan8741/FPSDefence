//=================================================================================================
//
// タイトルロゴ [ TitleLogo.cpp ]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "../interface/scene2D.h"
#include "titleStartButton.h"

//=================================================================================================
// 定数定義
//=================================================================================================
#define START_POS_X	        (640.0f)	// X座標
#define START_POS_Y	        (750.0f)	// Y座標
#define START_SIZE_X	    (350.0f)	// 幅
#define START_SIZE_Y	    (70.0f)		// 高さ
#define START_ALPHA_RATE    (0.01f)     // 点滅の速さ


//*************************************************************************************************
// コンストラクタ
//*************************************************************************************************
CTitleStart::CTitleStart(int nPriolity) :CScene2D(nPriolity)
{
}

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CTitleStart::Init(void)
{
    m_vPos = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
    m_vSize = D3DXVECTOR3(START_SIZE_X, START_SIZE_Y, 0.0f);
    m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_AlphaRate = -START_ALPHA_RATE;
    CScene2D::Init();
    return S_OK;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CTitleStart::Uninit(void)
{
    CScene2D::Uninit();
}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CTitleStart::Update(void)
{
    m_Color.a += m_AlphaRate;

    if (m_Color.a <= 0.0f) { m_AlphaRate *= -1; }
    else if (m_Color.a >= 1.0f) { m_AlphaRate *= -1; }

    SetColor(m_Color);
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CTitleStart::Draw(void)
{
    CScene2D::Draw();
}

//*************************************************************************************************
// インスタンス生成
//*************************************************************************************************
CTitleStart *CTitleStart::Create(void)
{
    CTitleStart *titleStart;
    titleStart = new CTitleStart(PRIOLITY_2);
    titleStart->Init();

    titleStart->LoadTexture(TEXTURE_TITLESTARTBUTTON);
    //titleStart->m_pTexture = CManager::GetTextureManager()->getResource(CManager::GetTextureManager()->getTextureName(TEXTURE_TITLESTART));

    return titleStart;
}
