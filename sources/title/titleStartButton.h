//=============================================================================
//
// �^�C�g���X�^�[�g [ TitleStart.h ]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef TITLESTART_H
#define TITLESTART_H



//=============================================================================
// �N���X�錾
//=============================================================================
class CTitleStart :public CScene2D
{
public:
    CTitleStart(int nPriolity);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CTitleStart* Create(void);

private:
    D3DXCOLOR m_Color;
    float m_AlphaRate;
};


#endif#pragma once