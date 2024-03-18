#include "stdafx.h"
#include "Stage3.h"
#include "Player_Stage3.h"
CStage3::CStage3() : m_pPlayer(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}
}

void CStage3::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, 1920, 1080);
	m_pPlayer->Render(hDC);
}

int CStage3::Update()
{
	m_pPlayer->Update();
	return 0;
}

void CStage3::Late_Update()
{
}

void CStage3::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	ReleaseDC(g_hWnd, m_DC);
}
