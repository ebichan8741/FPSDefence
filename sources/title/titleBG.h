//=============================================================================
//
// タイトル背景 [ TitleBG.h ]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef TITLEBG_H
#define TITLEBG_H

//=============================================================================
// クラス宣言
//=============================================================================
class CTitleBG :public CScene2D
{
public:
    CTitleBG(int nPriolity);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CTitleBG* Create(void);
};


#endif