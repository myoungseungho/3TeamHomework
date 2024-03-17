#include "stdafx.h"
#include "Map.h"

CMap::CMap()
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
	m_InitX = 50.f;
	m_InitY = 50.f;

	m_tInfo.vPos = { m_InitX, m_InitY, 0.f };
	m_Scale = m_MinScale;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (i == 0 && j == 0)
			{
				m_vPoint[i][j] = { 0,50.f,0 };
				continue;
			}

			m_vPoint[i][j].x = { m_tInfo.vPos.x };
			m_vPoint[i][j].y = { m_tInfo.vPos.y + i * 100.f };

			if (j == 1 || j == 2)
				m_vPoint[i][j].x = { m_tInfo.vPos.x + 700.f };

			if (j == 2 || j == 3)
				m_vPoint[i][j].y += 25.f;
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		for (size_t j = 0; j < 5; j++)
		{
			m_vOriginPoint[i][j] = m_vPoint[i][j];
		}
	}
}

void CMap::Update()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x * m_Scale, m_tInfo.vPos.y * m_Scale, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 8; ++i)
	{
		for (size_t j = 0; j < 5; j++)
		{
			m_vPoint[i][j] = m_vOriginPoint[i][j];
			m_vPoint[i][j] -= { m_InitX, m_InitY, 0.f};
			D3DXVec3TransformCoord(&m_vPoint[i][j], &m_vPoint[i][j], &m_tInfo.matWorld);
		}
	}
}

void CMap::Render(HDC hDC)
{
	for (int i = 0; i < 8; ++i)
	{
		MoveToEx(hDC, (int)m_vPoint[i][0].x, (int)m_vPoint[i][0].y, nullptr);

		for (size_t j = 0; j < 5; j++)
		{
			if ((int)m_vPoint[i][j].x == 0)
				continue;

			LineTo(hDC, (int)m_vPoint[i][j].x, (int)m_vPoint[i][j].y);
		}
	}
}

void CMap::Release()
{
}

//
//void CMap::Key_Input()
//{
//	if (GetAsyncKeyState('G') & 0x8000)
//	{
//		m_bLerpFactor = !m_bLerpFactor;
//	}
//
//	if (GetAsyncKeyState('H') & 0x8000)
//	{
//		m_bPlusLerp = !m_bPlusLerp;
//		m_bMinusLerp = !m_bMinusLerp;
//	}
//}
