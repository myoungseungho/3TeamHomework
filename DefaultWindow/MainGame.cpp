#include "stdafx.h"
#include "MainGame.h"
#include "ScrollMgr.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
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


}

void CMainGame::Update()
{
	m_pPlayer->Update();
}

void CMainGame::Render()
{

	Rectangle(m_DC, 0, 0, 1920,1080);
	
	m_pPlayer->Render(m_DC);
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	
	ReleaseDC(g_hWnd, m_DC);
}
