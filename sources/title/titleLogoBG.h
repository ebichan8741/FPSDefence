//=============================================================================
//
// �^�C�g���w�i2 [ TitleBG2.h ]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef TITLELOGOBG_H
#define TITLELOGOBG_H

//=============================================================================
// �N���X�錾
//=============================================================================
class CTitleLogoBG :public CScene2D
{
public:
    CTitleLogoBG(int nPriolity);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CTitleLogoBG* Create(void);

private:
    float m_Deg;
};


#endif
