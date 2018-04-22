//=================================================================================================
//
// 2D描画 [scene2D.cpp]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"

//=================================================================================================
// 定数定義
//=================================================================================================

//=================================================================================================
// 構造体宣言
//=================================================================================================
//テクスチャ情報構造体
typedef struct
{
    char *pFilename;	// ファイル名
} TEXPARAM;

//=================================================================================================
// グローバル変数
//=================================================================================================
//テクスチャパス
TEXPARAM g_aTexParam[TEXTURE_MAX] =
{
    "data/TEXTURE/titleBG03.jpg",
    "data/TEXTURE/titleLogo.png",
    "data/TEXTURE/titleLogoBG.png",
    "data/TEXTURE/titleStartButton.png",
    "data/TEXTURE/reticle.png",
    "data/TEXTURE/resultBG.jpg",
    "data/TEXTURE/resultLogo.png"
};

//*************************************************************************************************
// コンストラクタ
//*************************************************************************************************
CScene2D::CScene2D(int nPriolity) :CScene(nPriolity)
{
    m_bLoadTexture = false;
    m_pTexture = NULL;
    m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
    m_TexSize = D3DXVECTOR2(1.0f, 1.0f);
}

//*************************************************************************************************
// デストラクタ
//*************************************************************************************************
CScene2D::~CScene2D()
{
    m_bLoadTexture = false;
}

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CScene2D::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //頂点の作成
    if (FAILED(MakeVertex(pDevice)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CScene2D::Uninit(void)
{
    //テクスチャ解放
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }

    //頂点バッファ解放
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CScene2D::Update(void)
{
    VERTEX_2D* pVtx;

    //仮想アドレスを取得する
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標の設定(２D座標・右回り)
    pVtx[0].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    // テクスチャ座標
    pVtx[0].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y);
    pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y);
    pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexSize.y);
    pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y + m_TexSize.y);

    m_pVtxBuff->Unlock();		//ロック解除
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CScene2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //ストリームの設定
    pDevice->SetStreamSource(0,				//ストリーム番号(パイプ番号)
        m_pVtxBuff,				//ストリームの元になる頂点バッファ
        0,									//オフセット(バイト)
        sizeof(VERTEX_2D));					//一個の頂点データのサイズ(ストライド量)

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    //テクスチャの設定
    pDevice->SetTexture(0, m_pTexture);

    //プリミティブの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
        0,										//オフセット(頂点数)
        NUM_POLYGON);							//プリミティブの数
}

//*************************************************************************************************
// 頂点情報の設定
//*************************************************************************************************
HRESULT CScene2D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
    VERTEX_2D* pVtx;

    //頂点バッファ
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		//作成したい頂点バッファのサイズ
        D3DUSAGE_WRITEONLY,							//使用方法
        FVF_VERTEX_2D,								//
        D3DPOOL_MANAGED,							//メモリ管理方法(デバイスにお任せ)
        &m_pVtxBuff,
        NULL)))
    {
        return E_FAIL;
    }

    //仮想アドレスを取得する
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


    //頂点座標の設定(２D座標・右回り)
    pVtx[0].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    //テクスチャの頂点座標
    pVtx[0].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y);
    pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y);
    pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexSize.y);
    pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y + m_TexSize.y);

    //rhwの設定(必ず1.0f)
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定(0～255の整数値)
    pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_pVtxBuff->Unlock();		//ロック解除

    return 0;
}

//*************************************************************************************************
// テクスチャの読み込み処理
//*************************************************************************************************
void CScene2D::LoadTexture(TEXTURE_LABEL label)
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //NULLチェック
    if (m_pTexture == NULL)
    {
        //テクスチャの読み込み
        if (FAILED(D3DXCreateTextureFromFile(pDevice, g_aTexParam[label].pFilename, &m_pTexture)))
        {
            //エラー時
            MessageBox(NULL, "テクスチャの読み込みに失敗しました", "終了メッセージ", MB_OK);
        }

        m_bLoadTexture = true;
    }
}

//*************************************************************************************************
// 回転処理（引数：回転対象の中心座標、回転角度）
//*************************************************************************************************
void CScene2D::Rotation(D3DXVECTOR2 imgCenter, float deg)
{
    VERTEX_2D* pVtx;
    float rad = D3DXToRadian(deg);
    // 4頂点の座標をあらかじめ求めておく
    D3DXVECTOR3 pos0, pos1, pos2, pos3;
    pos0 = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pos1 = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pos2 = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pos3 = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    //仮想アドレスの取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標の設定(2D座標・右回り)
    pVtx[0].pos = D3DXVECTOR3((pos0.x - imgCenter.x) * cosf(-rad) - (pos0.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos0.x - imgCenter.x) * sinf(-rad) + (pos0.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos1.x - imgCenter.x) * cosf(-rad) - (pos1.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos1.x - imgCenter.x) * sinf(-rad) + (pos1.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3((pos2.x - imgCenter.x) * cosf(-rad) - (pos2.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos2.x - imgCenter.x) * sinf(-rad) + (pos2.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos3.x - imgCenter.x) * cosf(-rad) - (pos3.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos3.x - imgCenter.x) * sinf(-rad) + (pos3.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);

    //仮想アドレスの解放
    m_pVtxBuff->Unlock();
}

void CScene2D::SetColor(D3DXCOLOR color)
{
    VERTEX_2D* pVtx;

    //仮想アドレスを取得する
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点カラーの設定(0～255の整数値)
    pVtx[0].color = color;
    pVtx[1].color = color;
    pVtx[2].color = color;
    pVtx[3].color = color;

    m_pVtxBuff->Unlock();		//ロック解除
}