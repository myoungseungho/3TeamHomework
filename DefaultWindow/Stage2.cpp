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
            //4��?�� �˻� ��� ����ؾ���.

            size_t iCount(0);

            //�÷��̾� �� ���� ��
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, PlayerUpNomal))
                ++iCount;
            else
                continue; //��Ƽ���� ���� ����ȭ?
            //�÷��̾� ����Ʈ ���� ��
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, PlayerRightNomal))
                ++iCount;
            else
                continue;
            //���� �� ���� ��
            if (SAT_Player_Star(DowncastPlayer, DowncastStar, StarUpNormal))
                ++iCount;
            else
                continue;
            //���� ����Ʈ ���� ��
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



    //�÷��̾� �� ���� ��

    //float fPlayerDot = abs(D3DXVec3Dot(&(_Player->Get_Body()[0] - _Player->Get_Info().vPos), &_Normal));


    D3DXVECTOR3 PlayerPoint = _Player->Get_Body()[0] - _Player->Get_Info().vPos;
    float fPlayerDot(0.f);
    float fPlayerPointDotUpVector = D3DXVec3Dot(&PlayerPoint, &PlayerUpNomal);                                  //�÷��̾��� �������� �� ������ ���ϴ� ���Ϳ� �÷��̾� �� ���Ϳ��� ����.
    float fPlayerPointDotRightVector = D3DXVec3Dot(&PlayerPoint, &PlayerRightNomal);                            //�÷��̾��� �������� �� ������ ���ϴ� ���Ϳ� �÷��̾� ����Ʈ ���Ϳ��� ����.
    float fPlayerUpVectorDot = abs(D3DXVec3Dot(&(fPlayerPointDotUpVector * PlayerUpNomal), &_Normal));          //���� �����Ϳ� ������ ����� �÷��̾� �������� �������Ϳ� �����ְ� �� ���͸� ���ϰ��� �ϴ� ��� ����
    float fPlayerRightVectorDot = abs(D3DXVec3Dot(&(fPlayerPointDotRightVector * PlayerRightNomal), &_Normal)); //���� ����Ʈ���Ϳ� ������ ����� �÷��̾� ����Ʈ������ �������Ϳ� �����ְ� �� ���͸� ���ϰ��� �ϴ� ��� ����
    fPlayerDot = fPlayerUpVectorDot + fPlayerRightVectorDot;                                                    //����� ���� ���� ����Ʈ ������ �������� ���������� �÷��̾��� ���� ���� ����� ����.

    D3DXVECTOR3 StonePoint = _Star->Get_Point()[0] - _Star->Get_Info().vPos;
    float fStoneDot(0.f);
    float fStoneUpVectorDot = D3DXVec3Dot(&StonePoint, &StoneUpNomal);                                      //������ �������� �� ������ ���ϴ� ���Ϳ� �÷��̾� �� ���Ϳ��� ����.
    float fStoneRightVectorDot = D3DXVec3Dot(&StonePoint, &StoneRightNomal);                                //������ �������� �� ������ ���ϴ� ���Ϳ� �÷��̾� ����Ʈ ���Ϳ��� ����.
    fStoneUpVectorDot = abs(D3DXVec3Dot(&(fStoneUpVectorDot * StoneUpNomal), &_Normal));                    //���� �����Ϳ� ������ ����� �÷��̾� �������� �������Ϳ� �����ְ� �� ���͸� ���ϰ��� �ϴ� ��� ����
    fStoneRightVectorDot = abs(D3DXVec3Dot(&(fStoneRightVectorDot * StoneRightNomal), &_Normal));           //���� ����Ʈ���Ϳ� ������ ����� �÷��̾� ����Ʈ������ �������Ϳ� �����ְ� �� ���͸� ���ϰ��� �ϴ� ��� ����
    fStoneDot = fStoneUpVectorDot + fStoneRightVectorDot;                                                   //����� ���� ���� ����Ʈ ������ �������� ���������� ������ ���� ���� ����� ����.


    float fDistanceDot = abs(D3DXVec3Dot(&(_Player->Get_Info().vPos - _Star->Get_Info().vPos), &_Normal)); //�� ������Ʈ �߽ɿ��� �ٸ� ������Ʈ �߽��� ����Ű�� ���͸� ��� ����.

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
