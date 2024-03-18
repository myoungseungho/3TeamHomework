#pragma once

#include "Define.h"
#include "Player2.h"
#include "Star.h"
#include "Player_Stage3.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_hDC;


};

