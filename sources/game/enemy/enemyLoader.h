//=============================================================================
//
// �G�l�~�[�̓ǂݍ��� [enemyLoad.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef ENEMYLOAD_H
#define ENEMYLOAD_H

#include "../gameMode.h"

//=============================================================================
// �\���̐錾/ �񋓌^
//=============================================================================
typedef enum
{
    ENEMY_STATE_WALK = 0,		//�i�s���
    ENEMY_STATE_ATTACK,			//�U�����
    ENEMY_STATE_MAX
}ENEMY_STATE;

typedef enum
{
    ENEMY_TYPE_FLYING = 0,      // ��s�^
    ENEMY_TYPE_WALKER,          // ���s�^
    ENEMY_TYPE_BOOMER           // �{�}�[
}ENEMY_TYPE;

struct ENEMYDATA {
    int type;           //�G���
    int stype;          //�e���
    int m_pattern;      //�ړ��p�^�[��
    int s_pattern;      //���˃p�^�[��
    int in_time;        //�o������
    int stop_time;      //��~����
    int shot_time;      //�e���ˎ���
    int out_time;       //�A�Ҏ���
    D3DXVECTOR3 pos;    // ���W
    float speed;        //�e�X�s�[�h
    int hp;             //HP
    int item;           //�A�C�e��
};


//=============================================================================
// �N���X�錾
//=============================================================================
class CEnemyLoader :public CGameMode
{
public:
    static void EnemyLoad(void);
    static int GetMaxEnemy(void);

private:
    static int m_MaxEnemy;
};

#endif 