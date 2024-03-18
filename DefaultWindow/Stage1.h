#pragma once

#include "Define.h"
#include "Player_Stage1.h"
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
	list<CObj_Stage1*> m_listObj;
	CObj_Stage1* m_pPlayer;
	CObj_Stage1* m_pMonster;
	CObj_Stage1* m_pItem[3];
	CObj_Stage1* m_pMap;
	CObj_Stage1* m_pShield;
	CObj_Stage1* m_pTrailer;

	bool m_IsObserver = false;
	bool bMaxScale = false;
	bool bMinScale = false;
};
