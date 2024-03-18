#include "stdafx.h"
#include "Star.h"

CStar::CStar() :
	m_dwLifeTime(GetTickCount())
{
	ZeroMemory(&m_vPoint, sizeof(m_vPoint));
	ZeroMemory(&m_vOriginPoint, sizeof(m_vPoint));
	ZeroMemory(&m_vUp, sizeof(m_vUp));
	ZeroMemory(&m_vRight, sizeof(m_vRight));
	ZeroMemory(&m_vOriginUp, sizeof(m_vUp));
	ZeroMemory(&m_vOriginRight, sizeof(m_vRight));
}

void CStar::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vUp = { 0.f, -STAR_CY * 0.5f,0.f };
	m_vRight = { STAR_CX * 0.5f, 0.f,0.f };
	m_vOriginUp = m_vUp;
	m_vOriginRight = m_vRight;

	m_vPoint[0] = { m_tInfo.vPos.x - STAR_CX * 0.5f, m_tInfo.vPos.y - STAR_CY * 0.5f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + STAR_CX * 0.5f, m_tInfo.vPos.y - STAR_CY * 0.5f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + STAR_CX * 0.5f, m_tInfo.vPos.y + STAR_CY * 0.5f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - STAR_CX * 0.5f, m_tInfo.vPos.y + STAR_CY * 0.5f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fSpeed = 0.f;

	m_dwLifeTime = GetTickCount() + STAR_LIFETIME; //오브젝트가 살아있는 시간.

	m_eRender = RENDER_GAMEOBJECT;
}

int CStar::Update()
{

	if (m_bDead)
		return OBJ_DEAD;
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_vUp, &m_vOriginUp, &m_tInfo.matWorld);
	D3DXVec3TransformNormal(&m_vRight, &m_vOriginRight, &m_tInfo.matWorld);


	return OBJ_NOEVENT;
}

void CStar::Late_Update()
{
	if (m_dwLifeTime < GetTickCount()) //살아있는 시간이 다 되면 죽음.
		m_bDead = true;
}

void CStar::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CStar::Release()
{
}
