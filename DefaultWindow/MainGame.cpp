#include "stdafx.h"
#include "MainGame.h"
#include "Item.h"
#include "Map.h"
CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr), m_pMap(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer(this);
		m_pPlayer->Initialize();

		m_listObj.push_back(m_pPlayer);
	}

	for (size_t i = 0; i < 3; i++)
	{
		m_pItem[i] = new CItem;
		m_pItem[i]->Set_Pos(400.f, 25.f + i * 225.f);
		m_pItem[i]->Initialize();

		m_listObj.push_back(m_pItem[i]);
	}

	if (!m_pMap)
	{
		m_pMap = new CMap;
		m_pMap->Initialize();

		m_listObj.push_back(m_pMap);
	}
}

void CMainGame::Update()
{
	for (auto iter : m_listObj)
	{
		iter->Update();
	}

	if (m_IsObserver)
	{
		static int iCount = 0;
		iCount++;
		static bool bLerpMinus = false;
		static bool bLerpPlus = false;

		if (!bLerpMinus && !bLerpPlus && iCount > 65.f * 1.f)
		{
			for (auto iter : m_listObj)
			{
				iter->SetLerp(true);
			}
			bLerpMinus = true;
			iCount = 0;
		}

		if (bLerpMinus && !bLerpPlus && iCount > 65.f * 1.f)
		{
			for (auto iter : m_listObj)
			{
				iter->SetLerp(false);
			}
			iCount = 0;
			bLerpMinus = false;
			bLerpPlus = true;
		}

		if (!bLerpMinus && bLerpPlus && iCount > 65.f * 1.f)
		{
			for (auto iter : m_listObj)
			{
				iter->SetLerpFactor(false);
			}
			iCount = 0;
			bLerpMinus = false;
			bLerpPlus = false;
			m_IsObserver = false;
		}
	}
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	for (auto iter : m_listObj)
	{
		iter->Render(m_DC);
	}
}

void CMainGame::Release()
{
	for (auto iter : m_listObj)
	{
		Safe_Delete<CObj*>(iter);
	}

	ReleaseDC(g_hWnd, m_DC);
}

void CMainGame::ObserverPlayer(pair<bool, int> _pair)
{
	if (!m_IsObserver)
		m_IsObserver = true;

	for (auto iter : m_listObj)
	{
		iter->SetLerpFactor(true);
		iter->SetLerp(true);
	}

	m_listObj.remove(m_pItem[_pair.second]);
	Safe_Delete<CObj*>(m_pItem[_pair.second]);
}
