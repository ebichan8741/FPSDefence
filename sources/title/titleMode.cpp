
//================================================================================================
//
// �^�C�g���Ǘ� [titleMode.cpp]
// Author : TAKUYA EBIHARA
//
//================================================================================================
#include "../main.h"
#include "../manager/manager.h"
#include "../manager/renderer.h"
#include "titleMode.h"
#include "../game/gameMode.h"
#include "../interface/fade.h"
#include "../interface/scene.h"
#include "../interface/scene2D.h"
#include "titleBG.h"
#include "titleLogo.h"
#include "titleLogoBG.h"
#include "titleStartButton.h"
#include "../interface/input.h"
#include "../interface/sound.h"
//#include "TextureManager.h"

//*************************************************************************************************
// ����������
//*************************************************************************************************
HRESULT CTitleMode::Init(void)
{
    CManager::mode = MODE_TITLE;
    // �e�N�X�`���ǂݍ���
    //for (int i = 0; i < TEXTURE_MAX; i++) {
    //    CManager::GetTextureManager()->Load(CManager::GetTextureManager()->getTextureName((TEX_PARAM)i));
    //}
    CTitleBG::Create();
    CTitleLogoBG::Create();
    CTitleLogo::Create();
    CTitleStart::Create();

    //CManager::GetSound()->PlaySound(SOUND_LABEL_TITLE);

    return 0;
}

//*************************************************************************************************
// �I������
//*************************************************************************************************
void CTitleMode::Uninit(void)
{
    //�I�u�W�F�N�g�̉��
    CScene::ReleaseAll();

    //CManager::GetSound()->StopSound(SOUND_LABEL_TITLE);

}

//*************************************************************************************************
// �X�V����
//*************************************************************************************************
void CTitleMode::Update(void)
{
    if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN)) {
        CFade::SetFade(FADE_OUT, new CGameMode);
    }
}

//*************************************************************************************************
// �`�揈��
//*************************************************************************************************
void CTitleMode::Draw(void)
{
}
