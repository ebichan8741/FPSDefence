//=================================================================================================
//
// �^�C�g���w�i2 [TitleBG2.cpp]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "../interface/scene2D.h"
#include "TitleLogoBG.h"
#include "TitleLogo.h"

//=================================================================================================
// �萔��`
//=================================================================================================

//=================================================================================================
// �\���̐錾
//=================================================================================================

//=================================================================================================
// �O���[�o���ϐ�
//=================================================================================================

//*************************************************************************************************
// �R���X�g���N�^
//*************************************************************************************************
CTitleLogoBG::CTitleLogoBG(int nPriolity) :CScene2D(nPriolity)
{
}

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CTitleLogoBG::Init(void)
{
    m_vPos = D3DXVECTOR3(LOGO_POS_X - 15.0f, LOGO_POS_Y, 0.0f);
    m_vSize = D3DXVECTOR3(550.0f, 550.0f, 0.0f);
    m_Deg = 0;
    CScene2D::Init();
    return S_OK;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CTitleLogoBG::Uninit(void)
{
    CScene2D::Uninit();
}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CTitleLogoBG::Update(void)
{
    m_Deg -= 0.5f;

    CScene2D::Rotation(D3DXVECTOR2(m_vPos.x, m_vPos.y), m_Deg);
}

//*************************************************************************************************
// �`�揈��
//*************************************************************************************************
void CTitleLogoBG::Draw(void)
{
    CScene2D::Draw();
}

//*************************************************************************************************
// �C���X�^���X����
//*************************************************************************************************
CTitleLogoBG *CTitleLogoBG::Create(void)
{
    CTitleLogoBG *titleBG;
    titleBG = new CTitleLogoBG(PRIOLITY_0);
    titleBG->Init();

    titleBG->LoadTexture(TEXTURE_TITLELOGOBG);
    //titleBG->m_pTexture = CManager::GetTextureManager()->getResource(CManager::GetTextureManager()->getTextureName(TEXTURE_TITLEBG02));

    return titleBG;
}