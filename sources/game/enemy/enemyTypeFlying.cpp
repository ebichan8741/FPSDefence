//=================================================================================================
//
// 飛行型エネミー [enemyTypeFlying.cpp]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../../main.h"
#include "../../manager/manager.h"
#include "../../manager/renderer.h"
#include "../gameMode.h"
#include "enemy.h"
#include "enemyTypeFlying.h"
#include "enemyBullet.h"
//#include "EnemyExplosion.h"
//#include "Smoke.h"
#include "../camera.h"
#include "../meshField.h"
#include "../meshDome.h"
#include "../hitCheckToSphere.h"
#include "../score.h"

//=================================================================================================
// 定数定義
//=================================================================================================
#define ENEMY_BULLET_MOVE       (10.0f)     // 弾速

//=================================================================================================
// 構造体宣言
//=================================================================================================

//*************************************************************************************************
// コンストラクタ
//*************************************************************************************************
CEnemyFly::CEnemyFly(int nPriolity) :CEnemy(nPriolity)
{

}

//*************************************************************************************************
// 初期化処理
//*************************************************************************************************
HRESULT CEnemyFly::Init(void)
{
    CEnemy::Init();
    return S_OK;
}

//*************************************************************************************************
// 終了処理
//*************************************************************************************************
void CEnemyFly::Uninit(void)
{
    CEnemy::Uninit();
}

//*************************************************************************************************
// 更新処理
//*************************************************************************************************
void CEnemyFly::Update(void)
{
    D3DXVECTOR3 dir;

    // エネミー死亡
    if (m_Life <= 0) {
        DecEnemyNum();
        CScore::AddScore(100);
        //CSmoke::Create(m_vPos);
        //CEnemyExplosion::Create(m_vPos);
        CManager::GetCamera()->Swing(0.05f);
        Release();
#ifdef _DEBUG
        m_pHitDome->Release();
#endif
        CEnemy::Update();
        return;
    }

    // エネミーのステート管理
    switch (m_EnemyState)
    {
        //! 進行状態 !//
    case ENEMY_STATE_WALK:
        // 経路探索
        Path();
        m_vPos += m_vDir * ENEMY_MOVE_SPEED;
        break;

        //! 攻撃状態 !//
    case ENEMY_STATE_ATTACK:
        //弾発射
        if (m_BulletCnt >= 60) {
            D3DXVec3Subtract(&dir, &CManager::GetCamera()->GetCameraPos(), &m_vPos);
            dir.x += ((rand() % 3) - 1) * 0.1f;
            dir.y += ((rand() % 3) - 1) * 0.1f;
            dir.z += ((rand() % 3) - 1) * 0.1f;
            CEnemyBullet::Create(CEnemy::m_vPos, dir, ENEMY_BULLET_MOVE, m_Type);
            m_BulletCnt = 0;
        }
        break;
    }

    //m_vPos.y = CGameMode::GetMeshField()->GetHeight(m_vPos) + 30.0f;

    // 回転行列作成
    Direction();

    // エネミーの視界内判定
    if (CheckEnemySite()) {
        m_vDir = -m_vTargetDir;
        m_EnemyState = ENEMY_STATE_ATTACK;
    }
    else {
        m_EnemyState = ENEMY_STATE_WALK;
    }

#ifdef _DEBUG
    m_pHitDome->SetSphere(m_vPos, m_vSize);
#endif

    // 当たり判定
    if (m_Hit) {
#ifdef _DEBUG
        m_pHitDome->HitToSphere();
#endif
        m_Hit = false;
    }

    m_BulletCnt++;
    CEnemy::Update();
}

//*************************************************************************************************
// 描画処理
//*************************************************************************************************
void CEnemyFly::Draw(void)
{
    CEnemy::Draw();
}

//*************************************************************************************************
// インスタンス生成
//*************************************************************************************************
CEnemyFly *CEnemyFly::Create(D3DXVECTOR3 pos, int hp, int ID)
{
    CEnemyFly *enemyShooter;
    enemyShooter = new CEnemyFly(PRIOLITY_1);

    enemyShooter->m_vPos = pos;
    enemyShooter->m_ID = ID;
    enemyShooter->m_Life = enemyShooter->m_MaxLife = hp;
    enemyShooter->Init();

    //enemyShooter->m_ModelInfo = CManager::GetModelManager()->getResource(CManager::GetModelManager()->getModelName(MODEL_ENEMY0));
    enemyShooter->LoadModel(MODEL_ENEMY0);
    enemyShooter->m_Type = SCENE_TYPE_ENEMY;

    return enemyShooter;
}