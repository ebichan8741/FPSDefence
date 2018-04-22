//=============================================================================
//
// 2Dï`âÊ [scene2D.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef SCENE2D_H
#define SCENE2D_H

#include "scene.h"

typedef enum
{
    TEXTURE_TITLEBG = 0,
    TEXTURE_TITLELOGO,
    TEXTURE_TITLELOGOBG,
    TEXTURE_TITLESTARTBUTTON,
    TEXTURE_RESULT,
    TEXTURE_MAX
}TEXTURE_LABEL;

//=============================================================================
// ÉNÉâÉXêÈåæ
//=============================================================================
class CScene2D :public CScene
{
public:
    CScene2D(int nPriolity);
    ~CScene2D();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
    void LoadTexture(TEXTURE_LABEL label);
    void SetColor(D3DXCOLOR color);
    void Rotation(D3DXVECTOR2 imgCenter, float deg);

private:
    bool m_bLoadTexture;

protected:
    D3DXVECTOR2 m_TexPos, m_TexSize;
};

#endif