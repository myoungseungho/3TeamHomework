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

    void Spawn_Star(); //�� ��ȯ. ��Ÿ�� �Ǿ���.



public:
    //�浹ó��
    void Collision_Player_Star(list<CObj*> _PlayerList, list<CObj*> _StarList); //��� ������ �浹�Ǵ�.
    bool SAT_Player_Star(CPlayer2* _Player, CStar* _Star, D3DXVECTOR3 _Normal); //�ϳ��� �࿡���� �浹���� �Ǵ�

private:
    int     m_iScore;
    DWORD   m_dwStarSpawnCoolTime;


};

