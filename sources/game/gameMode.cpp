
//================================================================================================
//
// ゲーム管理 [GameMode.cpp]
// Author : TAKUYA EBIHARA
//
//================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "gameMode.h"
#include "../result/resultMode.h"
#include "../interface/fade.h"
#include "../interface/scene.h"
#include "meshField.h"
#include "meshDome.h"
#include "player/player.h"
#include "player/playerReticle.h"
#include "enemy/enemy.h"
#include "enemy/enemyLoader.h"
#include "player/playerBullet.h"
#include "enemy/enemyBullet.h"
//#include "HitPoint.h"
#include "camera.h"
#include "../interface/input.h"
#include "../interface/sound.h"
#include "number.h"
//#include "effect.h"

//=================================================================================================
// 静的メンバ変数
//=================================================================================================
CMeshField *CGameMode::m_pMeshField = 0;
CPlayer *CGameMode::m_pPlayer = 0;
std::vector <CEnemy*> CGameMode::m_pEnemy;
CNumber *CGameMode::m_pBulletNumber[NUMBER_DIGIT] = { 0 };
CNumber *CGameMode::m_pHPNumber[HP_DIGIT] = { 0 };
CNumber *CGameMode::m_pScore[SCORE_DIGIT] = { 0 };
bool CGameMode::m_flag = false;
int CGameMode::m_EnemyCnt = 0;

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CGameMode::Init(void)
{
    CManager::mode = MODE_GAME;

    m_flag = false;
    m_EnemyCnt = 0;

    //CHitPoint::Create();

    //メッシュフィールドの生成
    m_pMeshField = CMeshField::Create();

    //メッシュドームの生成
    CMeshDome::Create();

    //プレイヤーの生成
    m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -140.0f));

    //エネミーの生成
    CEnemyLoader::EnemyLoad();

    m_EnemyCnt = CEnemyLoader::GetMaxEnemy();

    //レティクルの生成
    CReticle::Create();

    CManager::GetCamera()->Init();

    //弾テクスチャ読み込み
    //CBullet::Load();

    // エフェクトテクスチャ読み込み
    //CEffect::Load();

    //数字テクスチャ読み込み
    CNumber::Load();

    // 弾数表示生成
    m_pBulletNumber[0] = CNumber::Create(D3DXVECTOR2(1120.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pBulletNumber[1] = CNumber::Create(D3DXVECTOR2(1150.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pBulletNumber[2] = CNumber::Create(D3DXVECTOR2(1180.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pBulletNumber[3] = CNumber::Create(D3DXVECTOR2(1210.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pBulletNumber[4] = CNumber::Create(D3DXVECTOR2(1240.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));

    // ＨＰ表示生成
    m_pHPNumber[0] = CNumber::Create(D3DXVECTOR2(80.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pHPNumber[1] = CNumber::Create(D3DXVECTOR2(110.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));
    m_pHPNumber[2] = CNumber::Create(D3DXVECTOR2(140.0f, 890.0f), D3DXVECTOR2(30.0f, 50.0f));


    //CManager::GetSound()->PlaySound(SOUND_LABEL_BGM000);

    return S_OK;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CGameMode::Uninit(void)
{
    //バレットテクスチャの破棄
    CPlayerBullet::Unload();
    CEnemyBullet::Unload();

    // 数字テクスチャの破棄
    CNumber::Unload();
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        m_pBulletNumber[i]->Uninit();
    }

    // ＨＰテクスチャの破棄
    for (int i = 0; i < HP_DIGIT; i++) {
        m_pHPNumber[i]->Uninit();
    }

    //オブジェクトの解放
    CScene::ReleaseAll();

    // プレイヤーポインタの破棄
    if (m_pPlayer != NULL)
    {
        m_pPlayer = NULL;
    }

    m_pEnemy.clear();

    //for (int i = 0; i < 3; i++) {
    //    // プレイヤーポインタの破棄
    //    if (m_pEnemy[i] != NULL)
    //    {
    //        m_pEnemy[i] = NULL;
    //    }
    //}
    // メッシュフィールドポインタの破棄
    if (m_pMeshField != NULL)
    {
        m_pMeshField = NULL;
    }

    //CManager::GetSound()->StopSound(SOUND_LABEL_BGM000);
}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CGameMode::Update(void)
{
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        m_pBulletNumber[i]->Update();
    }

    for (int i = 0; i < HP_DIGIT; i++) {
        m_pHPNumber[i]->Update();
    }

    //if (m_pPlayer != NULL) {
    //    if (GetPlayer()->GetLife() == 0 || m_EnemyCnt == 0) {
    //        m_flag = true;
    //    }
    //}

    if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || m_flag == true) {
        CFade::SetFade(FADE_OUT, new CResultMode);
    }
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CGameMode::Draw(void)
{
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        m_pBulletNumber[i]->Draw();
    }

    for (int i = 0; i < HP_DIGIT; i++) {
        m_pHPNumber[i]->Draw();
    }
}

//*************************************************************************************************
// メッシュフィールドのポインタ取得
//*************************************************************************************************
CMeshField *CGameMode::GetMeshField(void)
{
    return CGameMode::m_pMeshField;
}

//*************************************************************************************************
// プレイヤーのポインタ取得
//*************************************************************************************************
CPlayer *CGameMode::GetPlayer(void)
{
    return CGameMode::m_pPlayer;
}

//*************************************************************************************************
// エネミーのポインタ取得
//*************************************************************************************************
CEnemy *CGameMode::GetEnemy(int ID)
{
    return CGameMode::m_pEnemy[ID];
}

//*************************************************************************************************
// 弾数のポインタ取得
//*************************************************************************************************
CNumber *CGameMode::GetBulletNumber(int ID)
{
    return CGameMode::m_pBulletNumber[ID];
}

//*************************************************************************************************
// ＨＰのポインタ取得
//*************************************************************************************************
CNumber *CGameMode::GetHPNumber(int ID)
{
    return CGameMode::m_pHPNumber[ID];
}

//*************************************************************************************************
// スコアのポインタ取得
//*************************************************************************************************
CNumber *CGameMode::GetScore(int ID)
{
    return CGameMode::m_pScore[ID];
}