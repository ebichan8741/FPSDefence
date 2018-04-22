//=================================================================================================
//
// �v���C���[�̏e�e [playerBullet.cpp]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../../main.h"
#include "../../manager/manager.h"
#include "../../manager/renderer.h"
#include "../camera.h"
#include "../../interface/scene.h"
#include "../../interface/scene3D.h"
#include "player.h"
#include "../enemy/enemy.h"
#include "playerBullet.h"
//#include "explosion.h"
#include "../collision.h"
#include "../gameMode.h"

//=================================================================================================
// �萔��`
//=================================================================================================
#define BULLET_LIFE     (100)
#define BULLET_MOVE     (2.0f)
#define BULLET_DAMAGE   (1.0f)
#define BULLET_TEXTURE "data/TEXTURE/bullet.png"

//=================================================================================================
// �ÓI�����o�ϐ�
//=================================================================================================
LPDIRECT3DTEXTURE9 CPlayerBullet::m_pTexture = NULL;

//*************************************************************************************************
// �R���X�g���N�^
//*************************************************************************************************
CPlayerBullet::CPlayerBullet(int nPriolity) :CScene3D(nPriolity)
{
}

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CPlayerBullet::Init(void)
{
    //�����o������
    m_vSize = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
    m_Life = BULLET_LIFE;
    m_Move = BULLET_MOVE;
    m_Damage = BULLET_DAMAGE;
    m_LengthSq = m_vSize.x * m_vSize.x + m_vSize.y * m_vSize.y;
    CScene3D::InitLine();
    return S_OK;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CPlayerBullet::Uninit(void)
{
    CScene3D::Uninit();
}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CPlayerBullet::Update(void)
{
    //---------------------------------------------------------------------------------------------
    // �ϐ��錾�J�n
    //---------------------------------------------------------------------------------------------
    VERTEX_3D* pVtx; //���z�A�h���X���擾���邽�߂̃|�C���^
    D3DXVECTOR3 vMove;
    //---------------------------------------------------------------------------------------------
    // �ϐ��錾�I��
    //---------------------------------------------------------------------------------------------

    //�g�p�t���O��false�̎��͏������Ȃ�
    if (!m_Use) {
        Release();
        return;
    }

    m_OldPos = m_vPos;

    //�ړ��ʌv�Z
    vMove = m_Dir * m_Move;
    m_vPos += vMove;

    //�������Z
    m_Life--;
    if (m_Life <= 0) {
        m_Use = false;
        Release();
    }

    HitBullet();

    CScene3D::Update();
}

//*************************************************************************************************
// �`�揈��
//*************************************************************************************************
void CPlayerBullet::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxWorld;   //���[���h���W�ϊ��s��
    D3DXMATRIX mtxTrans, mtxScale, mtxInv;

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    // ���Z����
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    //���C�g�̃I�t
    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    //���[���h���W�ϊ��s��̏�����
    D3DXMatrixIdentity(&mtxWorld);

    //���[���h���W�ϊ��s��̓K�p
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    CScene3D::SetLinePos(m_OldPos, m_vPos);
    CScene3D::SetLineColor(D3DCOLOR_RGBA(255, 191, 63, 191), D3DCOLOR_RGBA(255, 191, 63, 255));
    CScene3D::DrawLine();

    //���C�g�̃I��
    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

    // ��Z����
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//*************************************************************************************************
// �C���X�^���X����
//*************************************************************************************************
CPlayerBullet *CPlayerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float m_vMove, SCENE_TYPE type)
{
    CPlayerBullet *bullet;
    bullet = new CPlayerBullet(PRIOLITY_1);
    bullet->Init();

    bullet->m_vPos = pos;
    bullet->m_OldPos = bullet->m_vPos;
    D3DXVec3Normalize(&dir, &dir);
    bullet->m_Dir = dir;
    bullet->m_Move = m_vMove;
    bullet->m_Use = true;
    bullet->m_BulletType = type;

    bullet->BindTexture(m_pTexture);
    bullet->m_Type = SCENE_TYPE_BULLET;

    return bullet;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPlayerBullet::Load(void)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (m_pTexture == NULL) {
        //�e�N�X�`���̓ǂݍ���
        if (FAILED(D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE, &m_pTexture))) {
            //�G���[��
            MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�I�����b�Z�[�W", MB_OK);
        }
    }
    return S_OK;
}

//=============================================================================
// �e�N�X�`���̉������
//=============================================================================
void CPlayerBullet::Unload(void)
{
    //�e�N�X�`���̔j��
    if (m_pTexture != NULL) {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//=============================================================================
// �e�̓����蔻�菈��
//=============================================================================
void CPlayerBullet::HitBullet(void)
{
    CScene *scene = CScene::GetList(PRIOLITY_1);
    while (scene != NULL) {
        if (scene->GetType() == SCENE_TYPE_ENEMY) {
            D3DXVECTOR3 enemyPos;
            float enemyLen;
            CEnemy *enemy = (CEnemy*)scene;
            enemyPos = enemy->GetPosition();
            enemyLen = enemy->GetLength();
            //�Փ˔���
            if (HitSphereToSphere(m_vPos, m_LengthSq, enemyPos, enemyLen)) {
                enemy->Hit(m_Damage);
                m_Use = false;
            }
        }
        scene = scene->GetNext();
    }
}