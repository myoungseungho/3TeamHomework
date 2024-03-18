#include "stdafx.h"
#include "Obj_Stage1.h"


CObj_Stage1::CObj_Stage1() : m_fSpeed(0.f), m_fAngle(0.f), m_MaxScale(2.f), m_MinScale(1.f), m_ScaleY(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj_Stage1::~CObj_Stage1()
{
}

bool CObj_Stage1::Lerp(int _lerp)
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
	m_ScaleY += newInterPolation;

	if (m_Scale <= m_MinScale)
	{
		m_Scale = m_MinScale;
		m_ScaleY = m_MinScale;
		return false;
	}

	if (m_Scale >= m_MaxScale)
	{
		m_Scale = m_MaxScale;
		m_ScaleY = m_MaxScale;
		return false;
	}

	return true;
}

