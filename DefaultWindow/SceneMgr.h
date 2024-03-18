#pragma once

#include "Define.h"
#include "Scene.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eScene);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	SCENEID		Get_CurSceneId() { return m_eCurScene; }

public:
	static CSceneMgr*	Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}
	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CSceneMgr*	m_pInstance;
	CScene*				m_pScene;
	
	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;

};

