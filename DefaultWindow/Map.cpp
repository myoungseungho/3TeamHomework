#include "stdafx.h"
#include "Map.h"

CMap::CMap() : m_bLerpFactor(false), m_Scale(0.f), m_MaxScale(0.f), m_MinScale(0.f), m_bPlusLerp(true), m_bMinusLerp(false)
{
	ZeroMemory(m_vPoint, sizeof(m_vPoint));
	ZeroMemory(m_vOriginPoint, sizeof(m_vOriginPoint));
}

CMap::~CMap()
{
	Release();
}

void CMap::Initialize()
{
	m_tInfo.vPos = { 50.f, 50.f, 0.f };
	m_Scale = 1.f;
	m_MaxScale = 5.f;
	m_MinScale = 0.0f;

	m_vPoint[0] = { m_tInfo.vPos.x , m_tInfo.vPos.y, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y + 100.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x , m_tInfo.vPos.y + 100.f, 0.f };
	m_vPoint[4] = { m_tInfo.vPos.x , m_tInfo.vPos.y + 200.f, 0.f };
	m_vPoint[5] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y + 200.f, 0.f };
	m_vPoint[6] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y + 300.f, 0.f };
	m_vPoint[7] = { m_tInfo.vPos.x , m_tInfo.vPos.y + 300.f, 0.f };
	m_vPoint[8] = { m_tInfo.vPos.x , m_tInfo.vPos.y + 400.f, 0.f };
	m_vPoint[9] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y + 400.f, 0.f };
	m_vPoint[10] = { m_tInfo.vPos.x + 700.f , m_tInfo.vPos.y + 500.f, 0.f };

	for (int i = 0; i < 11; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

void CMap::Update()
{
	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, 1.f);
	//D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale /** matRotZ*/ * matTrans;

	for (int i = 0; i < 11; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 50.f, 50.f, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	if (m_bLerpFactor)
		Lerp();
}

void CMap::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 11; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
	}
}

void CMap::Release()
{
}


void CMap::Key_Input()
{
	if (GetAsyncKeyState('G') & 0x8000)
	{
		m_bLerpFactor = !m_bLerpFactor;
	}

	if (GetAsyncKeyState('H') & 0x8000)
	{
		m_bPlusLerp = !m_bPlusLerp;
		m_bMinusLerp = !m_bMinusLerp;
	}
}

void CMap::Lerp()
{
	float fInterpolation = 0.001f;

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
