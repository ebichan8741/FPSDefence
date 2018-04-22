//=================================================================================================
//
// 球の当たり判定確認用 [hitCheckToSphere.h]
// Author : TAKUYA EBIHARA
//
//=================================================================================================
#ifndef _HITDOME_H_
#define _HITDOME_H_

//=================================================================================================
// クラス宣言
//=================================================================================================
class CHitCheckSphere :public CScene
{
public:
    CHitCheckSphere(int nPriolity);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
    HRESULT MakeIndex(LPDIRECT3DDEVICE9 pDevice);

    static CHitCheckSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void HitToSphere(void);

private:
    LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
    bool m_Hit;
    D3DXCOLOR m_Color;
    float m_Len;
};
#endif