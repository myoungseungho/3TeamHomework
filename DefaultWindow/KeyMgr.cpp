#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_eKeyState, sizeof(m_eKeyState));
	ZeroMemory(m_bPrePush, sizeof(m_bPrePush));
}


CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Update()
{
	for (int iKey = 0; iKey < VK_MAX; ++iKey)
	{
		if (GetAsyncKeyState(iKey) & 0x8000)
		{
			if (m_bPrePush[iKey])
			{
				m_eKeyState[iKey] = PRESSING;
			}
			else
			{
				m_eKeyState[iKey] = DOWN;
			}
			m_bPrePush[iKey] = true;
		}
		else
		{
			if (m_bPrePush[iKey])
			{
				m_eKeyState[iKey] = UP;
			}
			else
			{
				m_eKeyState[iKey] = NONE;
			}
			m_bPrePush[iKey] = false;
		}
	}
}