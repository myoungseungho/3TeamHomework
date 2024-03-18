#include "stdafx.h"
#include "Stage1.h"
#include "Item_Stage1.h"
#include "Map_Stage1.h"
CStage1::CStage1()
	: m_pPlayer(nullptr), m_pMonster(nullptr), m_pMap(nullptr), m_pShield(nullptr), m_pTrailer(nullptr)
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer_Stage1(this);
		m_pPlayer->Initialize();

		m_listObj.push_back(m_pPlayer);
	}

	if (!m_pTrailer)
	{
		m_pTrailer = new CTrailer(m_pPlayer);
		m_pTrailer->Initialize();

		m_listObj.push_back(m_pTrailer);
	}

	if (!m_pShield)
	{
		m_pShield = new CShield(m_pPlayer);
		m_pShield->Initialize();

		m_listObj.push_back(m_pShield);
	}

	for (size_t i = 0; i < 3; i++)
	{
		m_pItem[i] = new CItem_Stage1;
		m_pItem[i]->Set_Pos(150.f, 25.f + i * 200.f);
		m_pItem[i]->Initialize();

		m_listObj.push_back(m_pItem[i]);
	}

	if (!m_pMap)
	{
		m_pMap = new CMap_Stage1;
		m_pMap->Initialize();

		m_listObj.push_back(m_pMap);
	}
}

int CStage1::Update()
{
	for (auto iter : m_listObj)
	{
		iter->Update();
	}

	ExecuteObserver();

	return 0;
}

void CStage1::Late_Update()
{
}

void CStage1::Render(HDC hdc)
{
	Rectangle(hdc, 0, 0, WINCX, WINCY);

	for (auto iter : m_listObj)
	{
		iter->Render(hdc);
	}
}

void CStage1::Release()
{
	for (auto iter : m_listObj)
	{
		Safe_Delete<CObj_Stage1*>(iter);
	}

	ReleaseDC(g_hWnd, m_DC);
}

void CStage1::ObserverPlayer(pair<bool, int> _pair)
{
	if (!m_IsObserver)
		m_IsObserver = true;

	m_listObj.remove(m_pItem[_pair.second]);
	Safe_Delete<CObj_Stage1*>(m_pItem[_pair.second]);
}

void CStage1::ExecuteObserver()
{
	if (m_IsObserver)
	{
		if (!bMaxScale)
		{
			for (auto iter : m_listObj)
			{
				m_pPlayer->SetSpeed(2.f);
				if (iter->Lerp(TOMAXSCALE) == false)
					bMaxScale = true;
			}
		}
		else
		{
			for (auto iter : m_listObj)
			{
				if (iter->Lerp(TOMINSCALE) == false)
					bMinScale = true;
			}
		}

		if (bMinScale)
		{
			m_pPlayer->SetSpeed(1.f);
			m_IsObserver = false;
			bMinScale = false;
			bMaxScale = false;
		}
	}
}
