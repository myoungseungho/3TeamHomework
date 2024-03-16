#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

void CObj::Lerp()
{
	if (!m_bLerpFactor)
		return;

	float fInterpolation = 0.0005f;

	if (m_bPlusLerp && !m_bMinusLerp)
	{
		if (m_Scale <= m_MinScale)
			m_bLerpFactor = true;

		float newInterPolation = (m_MinScale - m_MaxScale) * fInterpolation;
		m_Scale += newInterPolation;
	}
	else if (m_bMinusLerp && !m_bPlusLerp)
	{
		if (m_Scale >= m_MaxScale)
			m_bLerpFactor = false;

		float newInterPolation = (m_MaxScale - m_MinScale) * fInterpolation;
		m_Scale += newInterPolation;
	}
}

