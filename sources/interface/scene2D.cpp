//=================================================================================================
//
// 2D�`�� [scene2D.cpp]
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
// �萔��`
//=================================================================================================

//=================================================================================================
// �\���̐錾
//=================================================================================================
//�e�N�X�`�����\����
typedef struct
{
    char *pFilename;	// �t�@�C����
} TEXPARAM;

//=================================================================================================
// �O���[�o���ϐ�
//=================================================================================================
//�e�N�X�`���p�X
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
// �R���X�g���N�^
//*************************************************************************************************
CScene2D::CScene2D(int nPriolity) :CScene(nPriolity)
{
    m_bLoadTexture = false;
    m_pTexture = NULL;
    m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
    m_TexSize = D3DXVECTOR2(1.0f, 1.0f);
}

//*************************************************************************************************
// �f�X�g���N�^
//*************************************************************************************************
CScene2D::~CScene2D()
{
    m_bLoadTexture = false;
}

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CScene2D::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    //���_�̍쐬
    if (FAILED(MakeVertex(pDevice)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CScene2D::Uninit(void)
{
    //�e�N�X�`�����
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }

    //���_�o�b�t�@���
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CScene2D::Update(void)
{
    VERTEX_2D* pVtx;

    //���z�A�h���X���擾����
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�̐ݒ�(�QD���W�E�E���)
    pVtx[0].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    // �e�N�X�`�����W
    pVtx[0].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y);
    pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y);
    pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexSize.y);
    pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y + m_TexSize.y);

    m_pVtxBuff->Unlock();		//���b�N����
}

//*************************************************************************************************
// �`�揈��
//*************************************************************************************************
void CScene2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    //�X�g���[���̐ݒ�
    pDevice->SetStreamSource(0,				//�X�g���[���ԍ�(�p�C�v�ԍ�)
        m_pVtxBuff,				//�X�g���[���̌��ɂȂ钸�_�o�b�t�@
        0,									//�I�t�Z�b�g(�o�C�g)
        sizeof(VERTEX_2D));					//��̒��_�f�[�^�̃T�C�Y(�X�g���C�h��)

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTexture);

    //�v���~�e�B�u�̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
        0,										//�I�t�Z�b�g(���_��)
        NUM_POLYGON);							//�v���~�e�B�u�̐�
}

//*************************************************************************************************
// ���_���̐ݒ�
//*************************************************************************************************
HRESULT CScene2D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
    VERTEX_2D* pVtx;

    //���_�o�b�t�@
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		//�쐬���������_�o�b�t�@�̃T�C�Y
        D3DUSAGE_WRITEONLY,							//�g�p���@
        FVF_VERTEX_2D,								//
        D3DPOOL_MANAGED,							//�������Ǘ����@(�f�o�C�X�ɂ��C��)
        &m_pVtxBuff,
        NULL)))
    {
        return E_FAIL;
    }

    //���z�A�h���X���擾����
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


    //���_���W�̐ݒ�(�QD���W�E�E���)
    pVtx[0].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    //�e�N�X�`���̒��_���W
    pVtx[0].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y);
    pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y);
    pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexSize.y);
    pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + m_TexSize.x, m_TexPos.y + m_TexSize.y);

    //rhw�̐ݒ�(�K��1.0f)
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�(0�`255�̐����l)
    pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_pVtxBuff->Unlock();		//���b�N����

    return 0;
}

//*************************************************************************************************
// �e�N�X�`���̓ǂݍ��ݏ���
//*************************************************************************************************
void CScene2D::LoadTexture(TEXTURE_LABEL label)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //NULL�`�F�b�N
    if (m_pTexture == NULL)
    {
        //�e�N�X�`���̓ǂݍ���
        if (FAILED(D3DXCreateTextureFromFile(pDevice, g_aTexParam[label].pFilename, &m_pTexture)))
        {
            //�G���[��
            MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�I�����b�Z�[�W", MB_OK);
        }

        m_bLoadTexture = true;
    }
}

//*************************************************************************************************
// ��]�����i�����F��]�Ώۂ̒��S���W�A��]�p�x�j
//*************************************************************************************************
void CScene2D::Rotation(D3DXVECTOR2 imgCenter, float deg)
{
    VERTEX_2D* pVtx;
    float rad = D3DXToRadian(deg);
    // 4���_�̍��W�����炩���ߋ��߂Ă���
    D3DXVECTOR3 pos0, pos1, pos2, pos3;
    pos0 = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pos1 = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, 0.0f);
    pos2 = D3DXVECTOR3(m_vPos.x - m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);
    pos3 = D3DXVECTOR3(m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2, 0.0f);

    //���z�A�h���X�̎擾
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�̐ݒ�(2D���W�E�E���)
    pVtx[0].pos = D3DXVECTOR3((pos0.x - imgCenter.x) * cosf(-rad) - (pos0.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos0.x - imgCenter.x) * sinf(-rad) + (pos0.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos1.x - imgCenter.x) * cosf(-rad) - (pos1.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos1.x - imgCenter.x) * sinf(-rad) + (pos1.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3((pos2.x - imgCenter.x) * cosf(-rad) - (pos2.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos2.x - imgCenter.x) * sinf(-rad) + (pos2.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos3.x - imgCenter.x) * cosf(-rad) - (pos3.y - imgCenter.y) * sinf(-rad) + imgCenter.x,
                              (pos3.x - imgCenter.x) * sinf(-rad) + (pos3.y - imgCenter.y) * cosf(-rad) + imgCenter.y, 0.0f);

    //���z�A�h���X�̉��
    m_pVtxBuff->Unlock();
}

void CScene2D::SetColor(D3DXCOLOR color)
{
    VERTEX_2D* pVtx;

    //���z�A�h���X���擾����
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_�J���[�̐ݒ�(0�`255�̐����l)
    pVtx[0].color = color;
    pVtx[1].color = color;
    pVtx[2].color = color;
    pVtx[3].color = color;

    m_pVtxBuff->Unlock();		//���b�N����
}