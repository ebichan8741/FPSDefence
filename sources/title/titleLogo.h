//=============================================================================
//
// �^�C�g�����S [ TitleLogo.h ]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef TITLELOGO_H
#define TITLELOGO_H

#define LOGO_POS_X	(640.0f)		// X���W
#define LOGO_POS_Y	(270.0f)	    // Y���W

//=============================================================================
// �N���X�錾
//=============================================================================
class CTitleLogo :public CScene2D
{
public:
    CTitleLogo(int nPriolity);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CTitleLogo* Create(void);
};


#endif#pragma once
