//=============================================================================
//
// ��s�^�G�l�~�[ [enemyTypeFlying.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "enemy.h"

//=============================================================================
// �\���̐錾/ �񋓌^
//=============================================================================

//=============================================================================
// �N���X�錾
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
