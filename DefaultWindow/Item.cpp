#include "stdafx.h"
#include "Item.h"

CItem::CItem() :m_fAngleSpeed(0.f), m_Scale(0.f), m_bLerpFactor(false), m_MaxScale(0.f), m_MinScale(0.f)
{
	ZeroMemory(m_vPoint, sizeof(m_vPoint));
	ZeroMemory(m_vOriginPoint, sizeof(m_vOriginPoint));
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_fAngleSpeed = 0.05f;
	m_Scale = 1.f;
	m_MaxScale = 5.f;
	m_MinScale = 0.0f;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[4] = { m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 5; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

}

void CItem::Update()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 5; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 400.f, 300.f, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	Lerp();

	m_fAngle += m_fAngleSpeed;
}

void CItem::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 5; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		/*if (i > 1)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f));*/
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CItem::Release()
{
}

void CItem::Lerp()
{
	float fInterpolation = 0.05f;

	if (m_bLerpFactor == false)
	{
		if (m_Scale <= m_MinScale)
			m_bLerpFactor = true;

		float newInterPolation = (m_MinScale - m_MaxScale) * fInterpolation;
		m_Scale += newInterPolation;
	}
	else
	{
		if (m_Scale >= m_MaxScale)
			m_bLerpFactor = false;

		float newInterPolation = (m_MaxScale - m_MinScale) * fInterpolation;
		m_Scale += newInterPolation;
	}
}
