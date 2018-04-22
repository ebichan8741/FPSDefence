//=============================================================================
//
// レティクル [playerReticle.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef MOUSECURSOL_H
#define MOUSECURSOL_H

#include "../../interface/scene2D.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CReticle :public CScene2D
{
public:
    CReticle(int nPriolity);
    ~CReticle();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CReticle *Create(void);

private:
};

#endif