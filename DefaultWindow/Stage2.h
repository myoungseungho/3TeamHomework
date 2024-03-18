#pragma once
#include "Scene.h"
#include "Obj.h"
#include "Player2.h"
#include "Star.h"

#define STAGE_KYS_STAR_SPAWN_COOLTIME 100

class CStage2 :
    public CScene
{
public:
    CStage2();
    virtual ~CStage2() { Release(); }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Rendering_Score(HDC hDC);

    void Spawn_Star(); //별 소환. 쿨타임 되야함.



public:
    //충돌처리
    void Collision_Player_Star(list<CObj*> _PlayerList, list<CObj*> _StarList); //모든 별과의 충돌판단.
    bool SAT_Player_Star(CPlayer2* _Player, CStar* _Star, D3DXVECTOR3 _Normal); //하나의 축에서의 충돌여부 판단

private:
    int     m_iScore;
    DWORD   m_dwStarSpawnCoolTime;


};

