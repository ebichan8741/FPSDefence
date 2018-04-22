//=============================================================================
//
// ゲームモード管理 [GameMode.h]
// Author : TAKUYA EBIHARA
//
//=============================================================================
#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_

#include <vector>
#include "../manager/modeManager.h"

#define NUMBER_DIGIT	(5)		// 弾数の桁
#define ENEMY_NUM		(1)		// エネミーの数
#define HP_DIGIT		(3)		// HPの桁
#define SCORE_DIGIT     (6)     // スコアの桁数

//=============================================================================
//前方宣言
//=============================================================================
class CMeshField;
class CPlayer;
class CEnemy;
class CEnemyFly;
class CNumber;

//=============================================================================
// クラス定義
//=============================================================================
class CGameMode :public CMode
{
public:
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CMeshField *GetMeshField(void);
    static CPlayer *GetPlayer(void);
    static CEnemy *GetEnemy(int ID);
    static CNumber *GetBulletNumber(int ID);
    static CNumber *GetHPNumber(int ID);
    static CNumber *GetScore(int ID);

    static bool m_flag;
    static int m_EnemyCnt;

protected:
    static CPlayer *m_pPlayer;
    static CMeshField *m_pMeshField;
    static std::vector<CEnemy*> m_pEnemy;
    static CNumber *m_pBulletNumber[NUMBER_DIGIT];
    static CNumber *m_pHPNumber[HP_DIGIT];
    static CNumber *m_pScore[SCORE_DIGIT];

};

#endif