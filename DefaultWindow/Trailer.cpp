#include "stdafx.h"
#include "Trailer.h"

CTrailer::CTrailer(CObj_Stage1* _pPlayer) : m_pPlayerCopy(_pPlayer)
{
	ZeroMemory(m_vPoint, sizeof(m_vPoint));
	ZeroMemory(m_vOriginPoint, sizeof(m_vOriginPoint));
}

CTrailer::~CTrailer()
{
}

void CTrailer::Initialize()
{
	m_InitX = 50.f;
	m_InitY = 20.f;
	m_Scale = m_MinScale;
	m_ScaleY = m_MinScale;
	m_tInfo.vPos = { m_InitX, m_InitY, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.f;
}

void CTrailer::Update()
{
	D3DXMATRIX playerMatWorld = m_pPlayerCopy->Get_Info().matWorld;
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale, m_bIsFlip ? -m_ScaleY : m_ScaleY, 1.f);
	D3DXMatrixTranslation(&matTrans, -50.f, 0, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans * playerMatWorld;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { m_InitX, m_InitY, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	flipVertical();
}

void CTrailer::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i < 2)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f));
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CTrailer::Release()
{
}

void CTrailer::flipVertical()
{
	if ((m_tInfo.vPos.y >= 80.f) && (m_tInfo.vPos.y <= 180.f)
		|| (m_tInfo.vPos.y >= 280.f) && (m_tInfo.vPos.y <= 380.f)
		|| (m_tInfo.vPos.y >= 480.f) && (m_tInfo.vPos.y <= 580.f))
		m_bIsFlip = true;
	else
		m_bIsFlip = false;
}
