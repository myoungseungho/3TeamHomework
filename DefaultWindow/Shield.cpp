#include "stdafx.h"
#include "Shield.h"

CShield::CShield(CObj_Stage1* m_pPlayer) : m_pPlayerCopy(m_pPlayer)
{
}

CShield::~CShield()
{
}

void CShield::Initialize()
{
	m_InitX = 50.f;
	m_InitY = 20.f;
	m_Scale = m_MinScale;
	m_OrbitRadius = 50.f;
	m_tInfo.vPos = { m_InitX, m_InitY, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y + 5.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y + 5.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 2.f;
}

void CShield::Update()
{
	D3DXVECTOR3 playerPos = m_pPlayerCopy->Get_Info().vPos;
	D3DXMATRIX		matScale, matRotZ, matTrans, matTransCircle;

	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, 1.f);
	D3DXMatrixTranslation(&matTransCircle, 0, m_OrbitRadius, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, playerPos.x * m_Scale, playerPos.y * m_Scale, 0);

	m_tInfo.matWorld = matScale * matTransCircle * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { m_InitX, m_InitY, 0.f};
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	m_fAngle += D3DXToRadian(3.f);
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_vPoint[0].x),
		int(m_vPoint[1].y),
		int(m_vPoint[2].x),
		int(m_vPoint[3].y));
}

void CShield::Release()
{
}
