#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_fAngle(0.f), m_MaxScale(3.f), m_MinScale(1.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

bool CObj::Lerp(int _lerp)
{
	float fInterpolation = 0.01f;
	float newInterPolation = 0.f;

	if (_lerp == TOMINSCALE)
	{
		newInterPolation = (m_MinScale - m_MaxScale) * fInterpolation;
	}
	else if (_lerp == TOMAXSCALE)
	{
		newInterPolation = (m_MaxScale - m_MinScale) * fInterpolation;
	}

	m_Scale += newInterPolation;

	if (m_Scale <= m_MinScale)
	{
		m_Scale = m_MinScale;
		return false;
	}

	if (m_Scale >= m_MaxScale)
	{
		m_Scale = m_MaxScale;
		return false;
	}

	return true;
}

