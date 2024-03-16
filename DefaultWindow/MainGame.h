#pragma once

#include "Define.h"
#include "Player.h"
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
	void		ObserverPlayer(pair<bool,int>);

private:
	HDC			m_DC;
	list<CObj*> m_listObj;
	CObj* m_pPlayer;
	CObj* m_pMonster;
	CObj* m_pItem[3];
	CObj* m_pMap;

	bool m_IsObserver = false;
};
