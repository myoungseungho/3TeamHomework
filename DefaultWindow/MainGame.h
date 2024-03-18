#pragma once

#include "Define.h"
#include "Player_Stage3.h"
#include "Monster.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Release();

private:
	HDC			m_DC;
	CObj*		m_pPlayer;
	CObj*		m_pMonster;

};

