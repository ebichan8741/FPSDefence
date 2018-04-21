
//================================================================================================
//
// �Q�[���Ǘ� [GameMode.cpp]
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
//#include "MouseCursol.h"
//#include "meshField.h"
//#include "meshField2.h"
//#include "meshDome.h"
#include "player/player.h"
//#include "enemy/enemy.h"
//#include "bullet.h"
//#include "HitPoint.h"
#include "camera.h"
#include "../interface/input.h"
#include "../interface/sound.h"
//#include "number.h"
//#include "effect.h"

//=================================================================================================
// �ÓI�����o�ϐ�
//=================================================================================================
//CMeshField *CGameMode::m_pMeshField = 0;
CPlayer *CGameMode::m_pPlayer = 0;
//CEnemy *CGameMode::m_pEnemy[] = { 0 };
//CNumber *CGameMode::m_pBulletNumber[NUMBER_DIGIT] = { 0 };
//CNumber *CGameMode::m_pHPNumber[HP_DIGIT] = { 0 };
bool CGameMode::m_flag = false;
int CGameMode::m_EnemyCnt = 0;

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CGameMode::Init(void)
{
    CManager::mode = MODE_GAME;

    m_flag = false;
    m_EnemyCnt = 0;

    //CHitPoint::Create();

    //CMeshField2::Create();

    ////���b�V���t�B�[���h�̐���
    //m_pMeshField = CMeshField::Create();

    ////���b�V���h�[���̐���
    //CMeshDome::Create();

    //�v���C���[�̐���
    m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -140.0f));

    //�G�l�~�[�̐���
    //m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -70.0f), 0, ENEMY_TYPE_NORMAL);
    //m_pEnemy[1] = CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, -70.0f),1,ENEMY_TYPE_NORMAL);
    //m_pEnemy[2] = CEnemy::Create(D3DXVECTOR3(100.0f, 0.0f, -70.0f),2,ENEMY_TYPE_NORMAL);

    m_EnemyCnt = ENEMY_NUM;

    //�}�E�X�J�[�\���̐���
    //CMouseCursol::Create();

    CManager::GetCamera()->Init();

    //�e�e�N�X�`���ǂݍ���
    //CBullet::Load();

    // �G�t�F�N�g�e�N�X�`���ǂݍ���
    //CEffect::Load();

    // �����e�N�X�`���ǂݍ���
    //CNumber::Load();

    // �e���\������
    //m_pBulletNumber[0] = CNumber::Create(D3DXVECTOR2(800.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pBulletNumber[1] = CNumber::Create(D3DXVECTOR2(830.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pBulletNumber[2] = CNumber::Create(D3DXVECTOR2(860.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pBulletNumber[3] = CNumber::Create(D3DXVECTOR2(890.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pBulletNumber[4] = CNumber::Create(D3DXVECTOR2(920.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));

    //// �g�o�\������
    //m_pHPNumber[0] = CNumber::Create(D3DXVECTOR2(80.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pHPNumber[1] = CNumber::Create(D3DXVECTOR2(110.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));
    //m_pHPNumber[2] = CNumber::Create(D3DXVECTOR2(140.0f, 650.0f), D3DXVECTOR2(30.0f, 50.0f));


    //CManager::GetSound()->PlaySound(SOUND_LABEL_BGM000);

    return S_OK;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CGameMode::Uninit(void)
{
    //�o���b�g�e�N�X�`���̔j��
    //CBullet::Unload();

    //// �����e�N�X�`���̔j��
    //CNumber::Unload();
    //for (int i = 0; i < NUMBER_DIGIT; i++) {
    //    m_pBulletNumber[i]->Uninit();
    //}

    //// �g�o�e�N�X�`���̔j��
    //for (int i = 0; i < HP_DIGIT; i++) {
    //    m_pHPNumber[i]->Uninit();
    //}

    //�I�u�W�F�N�g�̉��
    CScene::ReleaseAll();

    // �v���C���[�|�C���^�̔j��
    if (m_pPlayer != NULL)
    {
        m_pPlayer = NULL;
    }

    //for (int i = 0; i < 3; i++) {
    //    // �v���C���[�|�C���^�̔j��
    //    if (m_pEnemy[i] != NULL)
    //    {
    //        m_pEnemy[i] = NULL;
    //    }
    //}
    //// ���b�V���t�B�[���h�|�C���^�̔j��
    //if (m_pMeshField != NULL)
    //{
    //    m_pMeshField = NULL;
    //}

    //CManager::GetSound()->StopSound(SOUND_LABEL_BGM000);
}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CGameMode::Update(void)
{
    //for (int i = 0; i < NUMBER_DIGIT; i++) {
    //    m_pBulletNumber[i]->Update();
    //}

    //for (int i = 0; i < HP_DIGIT; i++) {
    //    m_pHPNumber[i]->Update();
    //}

    //if (m_pPlayer != NULL) {
    //    if (GetPlayer()->GetLife() == 0 || m_EnemyCnt == 0) {
    //        m_flag = true;
    //    }
    //}

    if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE) || m_flag == true) {
        CFade::SetFade(FADE_OUT, new CResultMode);
    }
}

//*************************************************************************************************
// �`�揈��
//*************************************************************************************************
void CGameMode::Draw(void)
{
    //for (int i = 0; i < NUMBER_DIGIT; i++) {
    //    m_pBulletNumber[i]->Draw();
    //}

    //for (int i = 0; i < HP_DIGIT; i++) {
    //    m_pHPNumber[i]->Draw();
    //}
}

//*************************************************************************************************
// ���b�V���t�B�[���h�̃|�C���^�擾
//*************************************************************************************************
//CMeshField *CGameMode::GetMeshField(void)
//{
//    return CGameMode::m_pMeshField;
//}

//*************************************************************************************************
// �v���C���[�̃|�C���^�擾
//*************************************************************************************************
CPlayer *CGameMode::GetPlayer(void)
{
    return CGameMode::m_pPlayer;
}

//*************************************************************************************************
// �G�l�~�[�̃|�C���^�擾
//*************************************************************************************************
//CEnemy *CGameMode::GetEnemy(int ID)
//{
//    return CGameMode::m_pEnemy[ID];
//}
//
////*************************************************************************************************
//// �e���̃|�C���^�擾
////*************************************************************************************************
//CNumber *CGameMode::GetBulletNumber(int ID)
//{
//    return CGameMode::m_pBulletNumber[ID];
//}
//
////*************************************************************************************************
//// �g�o�̃|�C���^�擾
////*************************************************************************************************
//CNumber *CGameMode::GetHPNumber(int ID)
//{
//    return CGameMode::m_pHPNumber[ID];
//}