#pragma once
#include "Scene.h"
#include "Obj.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	~CStage3();

public:
	void		Initialize();
	void		Render(HDC hDC) override;
	int			Update() override;
	void		Late_Update() override;
	void		Release();

private:
	HDC			m_DC;
	CObj* m_pPlayer;
};

