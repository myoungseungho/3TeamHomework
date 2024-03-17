#pragma once

#include "Define.h"
#include "Player.h"
#include "Monster.h"
#include "Shield.h"
#include "Trailer.h"
class CStage1
{
public:
	CStage1();
	~CStage1();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Release();
	void		ObserverPlayer(pair<bool,int>);
	void		ExecuteObserver();

private:
	HDC			m_DC;
	list<CObj*> m_listObj;
	CObj* m_pPlayer;
	CObj* m_pMonster;
	CObj* m_pItem[3];
	CObj* m_pMap;
	CObj* m_pShield;
	CObj* m_pTrailer;

	bool m_IsObserver = false;
	bool bMaxScale = false;
	bool bMinScale = false;
};
