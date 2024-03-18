#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
	{
		m_fScrollX = 0.f;
	}

	if (0.f < m_fScrollY)
	{
		m_fScrollY = 0.f;
	}

	if (800 - 1920 > m_fScrollX)
		m_fScrollX = 800 - 1920;

	if (600 - 1280 > m_fScrollY)
		m_fScrollY = 600 - 1280;

}
