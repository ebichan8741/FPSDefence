//=============================================================================
//
// 飛行型エネミー [enemyTypeFlying.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "enemy.h"

//=============================================================================
// 構造体宣言/ 列挙型
//=============================================================================

//=============================================================================
// クラス宣言
//=============================================================================
class CEnemyFly :public CEnemy
{
public:
    CEnemyFly(int nPriolity);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CEnemyFly *Create(D3DXVECTOR3 pos, int hp, int m_ID);
};

#endif
