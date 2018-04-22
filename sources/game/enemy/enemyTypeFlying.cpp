//=================================================================================================
//
// ��s�^�G�l�~�[ [enemyTypeFlying.cpp]
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
// �萔��`
//=================================================================================================
#define ENEMY_BULLET_MOVE       (10.0f)     // �e��

//=================================================================================================
// �\���̐錾
//=================================================================================================

//*************************************************************************************************
// �R���X�g���N�^
//*************************************************************************************************
CEnemyFly::CEnemyFly(int nPriolity) :CEnemy(nPriolity)
{

}

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CEnemyFly::Init(void)
{
    CEnemy::Init();
    return S_OK;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CEnemyFly::Uninit(void)
{
    CEnemy::Uninit();
}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CEnemyFly::Update(void)
{
    D3DXVECTOR3 dir;

    // �G�l�~�[���S
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

    // �G�l�~�[�̃X�e�[�g�Ǘ�
    switch (m_EnemyState)
    {
        //! �i�s��� !//
    case ENEMY_STATE_WALK:
        // �o�H�T��
        Path();
        m_vPos += m_vDir * ENEMY_MOVE_SPEED;
        break;

        //! �U����� !//
    case ENEMY_STATE_ATTACK:
        //�e����
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

    // ��]�s��쐬
    Direction();

    // �G�l�~�[�̎��E������
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

    // �����蔻��
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
// �`�揈��
//*************************************************************************************************
void CEnemyFly::Draw(void)
{
    CEnemy::Draw();
}

//*************************************************************************************************
// �C���X�^���X����
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