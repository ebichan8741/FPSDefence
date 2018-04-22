//=============================================================================
//
// エネミーの銃弾 [enemyBullet.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "../../interface/scene.h"
#include "../../interface/scene3D.h"

//=============================================================================
// 構造体宣言
//=============================================================================

//=============================================================================
// クラス宣言
//=============================================================================
class CEnemyBullet :public CScene3D
{
public:
    CEnemyBullet(int nPriolity);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float m_vMove, SCENE_TYPE type);
    static HRESULT Load(void);
    static void Unload(void);

    void HitBullet(void);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;   //テクスチャポインタ
    D3DXVECTOR3 m_OldPos;
    D3DXVECTOR3 m_Dir;
    float m_Move;
    int m_Life;
    int m_Damage;
    bool m_Hit;
    bool m_Use;
    SCENE_TYPE m_BulletType;
};

#endif