#include "stdafx.h"
#include "MainGame.h"
#include "Item.h"
#include "Map.h"
CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr), m_pItem(nullptr), m_pMap(nullptr)
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
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pItem)
	{
		m_pItem = new CItem;
		m_pItem->Initialize();
	}

	if (!m_pMap)
	{
		m_pMap = new CMap;
		m_pMap->Initialize();
	}
}

void CMainGame::Update()
{
	m_pPlayer->Update();
	m_pItem->Update();
	m_pMap->Update();
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_DC);
	m_pItem->Render(m_DC);
	m_pMap->Render(m_DC);
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pItem);
	Safe_Delete<CObj*>(m_pMap);

	ReleaseDC(g_hWnd, m_DC);
}
