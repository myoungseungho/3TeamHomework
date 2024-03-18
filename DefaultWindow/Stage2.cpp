#include "stdafx.h"
#include "Stage2.h"
#include <ctime>
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player2.h"
#include "Star.h"

CStage2::CStage2() :
    m_iScore(0),
    m_dwStarSpawnCoolTime(GetTickCount())
{
}

void CStage2::Initialize()
{
    srand(unsigned(time(nullptr)));
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer2>::Create_Obj());    
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create_Obj_LTH({ 100.f,100.f,0.f }));

}

int CStage2::Update()
{
    Spawn_Star();
    CObjMgr::Get_Instance()->Update();
    return 0;
}

void CStage2::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    Collision_Player_Star(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM));
}

void CStage2::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
    Rendering_Score(hDC);
}

void CStage2::Release()
{
}

void CStage2::Rendering_Score(HDC hDC)
{
    TCHAR szScore[32] = L"";
    swprintf_s(szScore, L"Score : %.2d", m_iScore);
    TextOut(hDC, 50, 50, szScore, lstrlen(szScore));


}

void CStage2::Spawn_Star()
{
    if (GetTickCount() > m_dwStarSpawnCoolTime)
    {
        m_dwStarSpawnCoolTime = GetTickCount() + STAGE_KYS_STAR_SPAWN_COOLTIME;
        D3DXVECTOR3 vPlayerPosTemp = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos;
        CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create_Obj_LTH({ vPlayerPosTemp.x - WINCX * 0.5f + rand() % WINCX, vPlayerPosTemp.y - WINCY * 0.5f + rand() % WINCY, 0.f }));

    }
}

void CStage2::Collision_Player_Star(list<CObj*> _PlayerList, list<CObj*> _StarList)
{
    for (auto& Player : _PlayerList)
    {
        CPlayer2* DowncastPlayer = static_cast<CPlayer2*>(Player);

        D3DXVECTOR3 PlayerUpNomal;
        D3DXVec3Normalize(&PlayerUpNomal, &(DowncastPlayer->Get_Up_Vector()));

        D3DXVECTOR3 PlayerRightNomal;
        D3DXVec3Normalize(&PlayerRightNomal, &(DowncastPlayer->Get_Right_Vector()));

        for (auto& Star : _StarList)
        {
            CStar* DowncastStar = static_cast<CStar*>(Star);

            D3DXVECTOR3 StarUpNormal;
            D3DXVec3Normalize(&StarUpNormal, &(DowncastStar->Get_Up_Vector()));

            D3DXVECTOR3 StarRightNormal;
            D3DXVec3Normalize(&StarRightNormal, &(DowncastStar->Get_Right_Vector()));
            //4번?의 검사 모두 통과해야함.

            size_t iCount(0);

            //플레이어 업 방향 축
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, PlayerUpNomal))
                ++iCount;
            else
                continue; //컨티뉴를 통해 최적화?
            //플레이어 라이트 방향 축
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, PlayerRightNomal))
                ++iCount;
            else
                continue;
            //스톤 업 방향 축
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, StarUpNormal))
                ++iCount;
            else
                continue;
            //스톤 라이트 방향 축
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, StarRightNormal))
                ++iCount;
            else
                continue;

            if (4 <= iCount)
            {
                DowncastStar->Set_Dead();
                ++m_iScore;
            }

        }
    }
}

bool CStage2::SAT_Player_Star(CPlayer2* _Player, CStar* _Star, D3DXVECTOR3 _Normal)
{
    D3DXVECTOR3 PlayerUpNomal;
    D3DXVec3Normalize(&PlayerUpNomal, &(_Player->Get_Up_Vector()));

    D3DXVECTOR3 PlayerRightNomal;
    D3DXVec3Normalize(&PlayerRightNomal, &(_Player->Get_Right_Vector()));


    D3DXVECTOR3 StoneUpNomal;
    D3DXVec3Normalize(&StoneUpNomal, &(_Star->Get_Up_Vector()));

    D3DXVECTOR3 StoneRightNomal;
    D3DXVec3Normalize(&StoneRightNomal, &(_Star->Get_Right_Vector()));



    //플레이어 업 방향 축

    //float fPlayerDot = abs(D3DXVec3Dot(&(_Player->Get_Body()[0] - _Player->Get_Info().vPos), &_Normal));


    D3DXVECTOR3 PlayerPoint = _Player->Get_Body()[0] - _Player->Get_Info().vPos;
    float fPlayerDot(0.f);
    float fPlayerPointDotUpVector = D3DXVec3Dot(&PlayerPoint, &PlayerUpNomal);                                  //플레이어의 중점에서 한 점으로 향하는 벡터와 플레이어 업 벡터와의 내적.
    float fPlayerPointDotRightVector = D3DXVec3Dot(&PlayerPoint, &PlayerRightNomal);                            //플레이어의 중점에서 한 점으로 향하는 벡터와 플레이어 라이트 벡터와의 내적.
    float fPlayerUpVectorDot = abs(D3DXVec3Dot(&(fPlayerPointDotUpVector * PlayerUpNomal), &_Normal));          //위의 업벡터와 내적한 결과를 플레이어 업벡터의 법선벡터와 곱해주고 그 벡터를 비교하고자 하는 축과 내적
    float fPlayerRightVectorDot = abs(D3DXVec3Dot(&(fPlayerPointDotRightVector * PlayerRightNomal), &_Normal)); //위의 라이트벡터와 내적한 결과를 플레이어 라이트벡터의 법선벡터와 곱해주고 그 벡터를 비교하고자 하는 축과 내적
    fPlayerDot = fPlayerUpVectorDot + fPlayerRightVectorDot;                                                    //결과로 나온 업과 라이트 벡터의 내적값을 더해줌으로 플레이어의 내적 최종 결과가 나옴.

    D3DXVECTOR3 StonePoint = _Star->Get_Point()[0] - _Star->Get_Info().vPos;
    float fStoneDot(0.f);
    float fStoneUpVectorDot = D3DXVec3Dot(&StonePoint, &StoneUpNomal);                                      //스톤의 중점에서 한 점으로 향하는 벡터와 플레이어 업 벡터와의 내적.
    float fStoneRightVectorDot = D3DXVec3Dot(&StonePoint, &StoneRightNomal);                                //스톤의 중점에서 한 점으로 향하는 벡터와 플레이어 라이트 벡터와의 내적.
    fStoneUpVectorDot = abs(D3DXVec3Dot(&(fStoneUpVectorDot * StoneUpNomal), &_Normal));                    //위의 업벡터와 내적한 결과를 플레이어 업벡터의 법선벡터와 곱해주고 그 벡터를 비교하고자 하는 축과 내적
    fStoneRightVectorDot = abs(D3DXVec3Dot(&(fStoneRightVectorDot * StoneRightNomal), &_Normal));           //위의 라이트벡터와 내적한 결과를 플레이어 라이트벡터의 법선벡터와 곱해주고 그 벡터를 비교하고자 하는 축과 내적
    fStoneDot = fStoneUpVectorDot + fStoneRightVectorDot;                                                   //결과로 나온 업과 라이트 벡터의 내적값을 더해줌으로 스톤의 내적 최종 결과가 나옴.


    float fDistanceDot = abs(D3DXVec3Dot(&(_Player->Get_Info().vPos - _Star->Get_Info().vPos), &_Normal)); //한 오브젝트 중심에서 다른 오브젝트 중심을 가르키는 벡터를 축과 내적.

    if (fPlayerDot + fStoneDot < fDistanceDot)
    {
        return false;
    }
    else if (fPlayerDot + fStoneDot >= fDistanceDot)
    {
        return true;
    }

    return false;
}
