#pragma once

#include "Define.h"

//사용 방법
//if (CKeyMgr::Get_Instance()->Get_KeyState(확인할 키) == 상태 DOWN || PRESSING || UP )

enum EKeyState
{
	NONE,
	DOWN,
	PRESSING,
	UP
};

struct tKeyInfo
{
	EKeyState	eState;
	bool		bPrePush;
};

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	void	Update();
	EKeyState Get_KeyState(int _iKey) { return m_eKeyState[_iKey]; }

private:
	EKeyState		m_eKeyState[VK_MAX];
	bool			m_bPrePush[VK_MAX];

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;


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
	static	CKeyMgr* m_pInstance;
};
