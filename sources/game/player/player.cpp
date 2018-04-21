//=================================================================================================
//
// プレイヤー [player.cpp]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../../main.h"
#include "../../manager/manager.h"
#include "../../manager/renderer.h"
#include "../gameMode.h"
#include "../camera.h"
#include "../../interface/sceneModel.h"
#include "player.h"
//#include "bullet.h"
//#include "meshField.h"
#include "../../interface/fade.h"
#include "../../result/resultMode.h"
#include "../../interface/input.h"
//#include "number.h"
#include "../../interface/sound.h"
//#include "effect.h"

//=================================================================================================
// 定数定義
//=================================================================================================
#define PLAYER_LIFE		(100)		// プレイヤーの体力
#define BULLET_NUM		(30)		// 1マガジンの弾数
#define BULLET_RATE		(1)			// 銃の連射速度
#define RELOAD_TIME		(150)		// リロード時間

//=================================================================================================
// 構造体宣言
//=================================================================================================

//=================================================================================================
// グローバル変数
//=================================================================================================

//*************************************************************************************************
// コンストラクタ
//*************************************************************************************************
CPlayer::CPlayer(int nPriolity) :CSceneModel(nPriolity)
{
}

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CPlayer::Init(void)
{
    //メンバ初期化
    m_vSize = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
    m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_LengthSq = m_vSize.x * m_vSize.x + m_vSize.y * m_vSize.y + m_vSize.z * m_vSize.z;
    m_Hit = false;
    m_Reload = false;
    m_Life = PLAYER_LIFE;
    m_BulletNum = BULLET_NUM;
    m_BulletRate = 0;
    m_ReloadCnt = 0;

    CSceneModel::Init();
    return S_OK;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CPlayer::Uninit(void)
{
    CSceneModel::Uninit();
}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CPlayer::Update(void)
{
    if (CManager::GetInputKeyboard()->GetKeyPress(DIK_UP)) {
        m_vPos.z += 0.5f;
    }
    else if (CManager::GetInputKeyboard()->GetKeyPress(DIK_DOWN)) {
        m_vPos.z -= 0.5f;
    }
    if (CManager::GetInputKeyboard()->GetKeyPress(DIK_RIGHT)) {
        m_vPos.x += 0.5f;
    }
    else if (CManager::GetInputKeyboard()->GetKeyPress(DIK_LEFT)) {
        m_vPos.x -= 0.5f;
    }

    ////Y座標をフィールドに合わせる
    //m_vPos.y = CGameMode::GetMeshField()->GetHeight(m_vPos);

    //FPSモード
    if (CManager::GetCamera()->m_bFps == true) {
        m_vPos = CManager::GetCamera()->GetCameraPos();
    }

    //弾発射
    if (CManager::GetInputMouse()->GetMouseTrigger(CLICK_LEFT)) {
        m_BulletRate = 0;
    }
    //if (CManager::GetInputMouse()->GetMousePress(CLICK_LEFT) && m_BulletRate == 0 && m_BulletNum > 0) {
    //    CBullet::Create(CManager::GetCamera()->GetCameraPos(), CManager::GetCamera()->GetCameraForward(), m_Type);
    //    CEffect::Create(CManager::GetCamera()->GetCameraPos(), CManager::GetCamera()->GetCameraForward());
    //    CManager::GetSound()->PlaySound(SOUND_LABEL_SE_SHOT);	// 銃声再生
    //    m_BulletNum--;
    //}

    // Rを押すか弾がなくなったときリロード処理
    if (m_Reload == false && m_BulletNum != BULLET_NUM && CManager::GetInputKeyboard()->GetKeyTrigger(DIK_R) || m_BulletNum == 0) {
        m_Reload = true;
        CManager::GetSound()->PlaySound(SOUND_LABEL_SE_RELOAD);	// リロード音再生
    }
    if (m_Reload == true) {
        Reload();
    }

    // 弾の連射速度
    m_BulletRate = (m_BulletRate + 1) % BULLET_RATE;

    // 弾数表示
    //CGameMode::GetBulletNumber(0)->SetNumber(m_BulletNum / 10, 0.0f);
    //CGameMode::GetBulletNumber(1)->SetNumber(m_BulletNum % 10, 0.0f);
    //CGameMode::GetBulletNumber(2)->SetNumber(4, 0.5f);
    //CGameMode::GetBulletNumber(3)->SetNumber(BULLET_NUM / 10, 0.0f);
    //CGameMode::GetBulletNumber(4)->SetNumber(BULLET_NUM % 10, 0.0f);

    //// ＨＰ表示
    //CGameMode::GetHPNumber(0)->SetNumber(m_Life * 0.01f, 0.0f);
    //CGameMode::GetHPNumber(1)->SetNumber((m_Life % 100) * 0.1f, 0.0f);
    //CGameMode::GetHPNumber(2)->SetNumber(m_Life % 10, 0.0f);

    CSceneModel::Update();

    //デバッグ表示
#ifdef _DEBUG
    char text[256];
    sprintf(text, "PlayerPos  X : %f  Y : %f  Z : %f  PlayerLife  %d\n", m_vPos.x, m_vPos.y, m_vPos.z, m_Life);
    CDebug::AddText(text);
#endif
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CPlayer::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;
    D3DMATERIAL9 matDef;
    D3DXMATRIX mtxWorld;
    D3DXMATRIX mtxTrans, mtxScale, mtxRotY;
    D3DXMATRIX mtxRot = CManager::GetCamera()->GetCameraRotMat();

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //ワールド座標変換行列の初期化
    D3DXMatrixIdentity(&mtxWorld);

    //D3DXMatrixScaling(&mtxScale,0.25f,0.25f,0.25f);

    //回転
    D3DXMatrixRotationYawPitchRoll(&mtxRotY, D3DX_PI, 0.0f, 0.0f);

    //平行移動
    D3DXMatrixTranslation(&mtxTrans, m_vPos.x, m_vPos.y, m_vPos.z);

    //行列の乗算（出力先,左辺,右辺）
    //D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxScale);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotY);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

    //ワールド座標変換行列の適用
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    CSceneModel::Draw();
}

//*************************************************************************************************
// インスタンス生成
//*************************************************************************************************
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
    CPlayer *player;
    player = new CPlayer(PRIOLITY_1);

    player->m_vPos = pos;

    player->Init();

    player->LoadModel(MODEL_PLAYER);
    player->m_Type = SCENE_TYPE_PLAYER;

    return player;
}

//*************************************************************************************************
// ダメージ判定
//*************************************************************************************************
void CPlayer::Hit(int damage)
{
    m_Life -= damage;
    m_Hit = true;
}

//*************************************************************************************************
// リロード処理
//*************************************************************************************************
void CPlayer::Reload(void)
{
    m_ReloadCnt++;

    if (m_ReloadCnt >= RELOAD_TIME) {
        m_BulletNum = BULLET_NUM;
        m_ReloadCnt = 0;
        m_Reload = false;
    }
}

//*************************************************************************************************
// 体力取得
//*************************************************************************************************
int CPlayer::GetLife(void) {
    return m_Life;
}