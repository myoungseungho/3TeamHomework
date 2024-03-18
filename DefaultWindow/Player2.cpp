#include "stdafx.h"
#include "Player2.h"
#include "KeyMgr.h"

CPlayer2::CPlayer2() :
	m_fAcceleration(0.f),
	m_eDrift(DRIFT_STATE_END)
{
	ZeroMemory(&m_vBodyPoint, sizeof(m_vBodyPoint));
	ZeroMemory(&m_vOriginBodyPoint, sizeof(m_vBodyPoint));

	ZeroMemory(&m_vFrontGlassPoint, sizeof(m_vFrontGlassPoint));
	ZeroMemory(&m_vOriginFrontGlassPoint, sizeof(m_vFrontGlassPoint));

	ZeroMemory(&m_vLeftGlassPoint, sizeof(m_vLeftGlassPoint));
	ZeroMemory(&m_vOriginLeftGlassPoint, sizeof(m_vLeftGlassPoint));

	ZeroMemory(&m_vRightGlassPoint, sizeof(m_vRightGlassPoint));
	ZeroMemory(&m_vOriginRightGlassPoint, sizeof(m_vRightGlassPoint));

	ZeroMemory(&m_vBackGlassPoint, sizeof(m_vBackGlassPoint));
	ZeroMemory(&m_vOriginBackGlassPoint, sizeof(m_vBackGlassPoint));

	ZeroMemory(&m_vUp, sizeof(m_vUp));
	ZeroMemory(&m_vRight, sizeof(m_vRight));
	ZeroMemory(&m_vOriginUp, sizeof(m_vUp));
	ZeroMemory(&m_vOriginRight, sizeof(m_vRight));
}

void CPlayer2::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vUp = { 0.f, -PLAYER2_CY * 0.5f,0.f };
	m_vRight = { PLAYER2_CX * 0.5f, 0.f,0.f };
	m_vOriginUp = m_vUp;
	m_vOriginRight = m_vRight;

	//차체
	m_vBodyPoint[0] = { m_tInfo.vPos.x - PLAYER2_CX * 0.35f, m_tInfo.vPos.y - PLAYER2_CY * 0.5f, 0.f };
	m_vBodyPoint[1] = { m_tInfo.vPos.x - PLAYER2_CX * 0.5f, m_tInfo.vPos.y - PLAYER2_CY * 0.2f, 0.f };
	m_vBodyPoint[2] = { m_tInfo.vPos.x - PLAYER2_CX * 0.5f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };
	m_vBodyPoint[3] = { m_tInfo.vPos.x - PLAYER2_CX * 0.4f, m_tInfo.vPos.y + PLAYER2_CY * 0.5f, 0.f };
	m_vBodyPoint[4] = { m_tInfo.vPos.x + PLAYER2_CX * 0.4f, m_tInfo.vPos.y + PLAYER2_CY * 0.5f, 0.f };
	m_vBodyPoint[5] = { m_tInfo.vPos.x + PLAYER2_CX * 0.5f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };
	m_vBodyPoint[6] = { m_tInfo.vPos.x + PLAYER2_CX * 0.5f, m_tInfo.vPos.y - PLAYER2_CY * 0.2f, 0.f };
	m_vBodyPoint[7] = { m_tInfo.vPos.x + PLAYER2_CX * 0.35f, m_tInfo.vPos.y - PLAYER2_CY * 0.5f, 0.f };

	for (int i = 0; i < 8; ++i)
		m_vOriginBodyPoint[i] = m_vBodyPoint[i];

	//차 앞 유리
	m_vFrontGlassPoint[0] = { m_tInfo.vPos.x - PLAYER2_CX * 0.4f, m_tInfo.vPos.y - PLAYER2_CY * 0.2f, 0.f };
	m_vFrontGlassPoint[1] = { m_tInfo.vPos.x - PLAYER2_CX * 0.3f, m_tInfo.vPos.y - PLAYER2_CY * 0.05f, 0.f };
	m_vFrontGlassPoint[2] = { m_tInfo.vPos.x + PLAYER2_CX * 0.3f, m_tInfo.vPos.y - PLAYER2_CY * 0.05f, 0.f };
	m_vFrontGlassPoint[3] = { m_tInfo.vPos.x + PLAYER2_CX * 0.4f, m_tInfo.vPos.y - PLAYER2_CY * 0.2f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginFrontGlassPoint[i] = m_vFrontGlassPoint[i];


	//차 왼 유리
	m_vLeftGlassPoint[0] = { m_tInfo.vPos.x - PLAYER2_CX * 0.4f, m_tInfo.vPos.y - PLAYER2_CY * 0.15f, 0.f };
	m_vLeftGlassPoint[1] = { m_tInfo.vPos.x - PLAYER2_CX * 0.4f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };
	m_vLeftGlassPoint[2] = { m_tInfo.vPos.x - PLAYER2_CX * 0.3f, m_tInfo.vPos.y + PLAYER2_CY * 0.3f, 0.f };
	m_vLeftGlassPoint[3] = { m_tInfo.vPos.x - PLAYER2_CX * 0.3f, m_tInfo.vPos.y + PLAYER2_CY * 0.05f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginLeftGlassPoint[i] = m_vLeftGlassPoint[i];

	//차 오른 유리
	m_vRightGlassPoint[0] = { m_tInfo.vPos.x + PLAYER2_CX * 0.4f, m_tInfo.vPos.y - PLAYER2_CY * 0.15f, 0.f };
	m_vRightGlassPoint[1] = { m_tInfo.vPos.x + PLAYER2_CX * 0.4f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };
	m_vRightGlassPoint[2] = { m_tInfo.vPos.x + PLAYER2_CX * 0.3f, m_tInfo.vPos.y + PLAYER2_CY * 0.3f, 0.f };
	m_vRightGlassPoint[3] = { m_tInfo.vPos.x + PLAYER2_CX * 0.3f, m_tInfo.vPos.y + PLAYER2_CY * 0.05f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginRightGlassPoint[i] = m_vRightGlassPoint[i];

	//차 뒷 유리
	m_vBackGlassPoint[0] = { m_tInfo.vPos.x - PLAYER2_CX * 0.35f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };
	m_vBackGlassPoint[1] = { m_tInfo.vPos.x - PLAYER2_CX * 0.25f, m_tInfo.vPos.y + PLAYER2_CY * 0.3f, 0.f };
	m_vBackGlassPoint[2] = { m_tInfo.vPos.x + PLAYER2_CX * 0.25f, m_tInfo.vPos.y + PLAYER2_CY * 0.3f, 0.f };
	m_vBackGlassPoint[3] = { m_tInfo.vPos.x + PLAYER2_CX * 0.35f, m_tInfo.vPos.y + PLAYER2_CY * 0.4f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginBackGlassPoint[i] = m_vBackGlassPoint[i];


	m_fSpeed = 0.f;
	m_fAcceleration = 0.1f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CPlayer2::Update()
{
	m_eDrift = NOT_DRIFT;
	Key_Input();


	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	switch (m_eDrift)
	{
	case NOT_DRIFT:
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		break;
	case DRIFT_LEFT:
		D3DXMatrixRotationZ(&matRotZ, m_fAngle - 50.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &matRotZ);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		break;
	case DRIFT_RIGHT:
		D3DXMatrixRotationZ(&matRotZ, m_fAngle + 50.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &matRotZ);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		break;
	case DRIFT_STATE_END:
		break;
	default:
		break;
	}




	for (int i = 0; i < 8; ++i)
	{
		m_vBodyPoint[i] = m_vOriginBodyPoint[i];
		m_vBodyPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vBodyPoint[i], &m_vBodyPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vFrontGlassPoint[i] = m_vOriginFrontGlassPoint[i];
		m_vFrontGlassPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vFrontGlassPoint[i], &m_vFrontGlassPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vLeftGlassPoint[i] = m_vOriginLeftGlassPoint[i];
		m_vLeftGlassPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vLeftGlassPoint[i], &m_vLeftGlassPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vRightGlassPoint[i] = m_vOriginRightGlassPoint[i];
		m_vRightGlassPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vRightGlassPoint[i], &m_vRightGlassPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vBackGlassPoint[i] = m_vOriginBackGlassPoint[i];
		m_vBackGlassPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vBackGlassPoint[i], &m_vBackGlassPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_vUp, &m_vOriginUp, &m_tInfo.matWorld);
	D3DXVec3TransformNormal(&m_vRight, &m_vOriginRight, &m_tInfo.matWorld);


	return OBJ_NOEVENT;
}

void CPlayer2::Late_Update()
{
}

void CPlayer2::Render(HDC hDC)
{
	
	MoveToEx(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y, nullptr);

	for (int i = 0; i < 8; ++i)
	{
		LineTo(hDC, (int)m_vBodyPoint[i].x, (int)m_vBodyPoint[i].y);

		if (i == 0 || i == 3 || i == 4 || i == 7 || i == 8)
			continue;

		Ellipse(hDC,
			int(m_vBodyPoint[i].x - 5.f),
			int(m_vBodyPoint[i].y - 5.f),
			int(m_vBodyPoint[i].x + 5.f),
			int(m_vBodyPoint[i].y + 5.f));
	}

	LineTo(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y);

	//차 앞 유리
	MoveToEx(hDC, (int)m_vFrontGlassPoint[0].x, (int)m_vFrontGlassPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vFrontGlassPoint[i].x, (int)m_vFrontGlassPoint[i].y);
	}
	LineTo(hDC, (int)m_vFrontGlassPoint[0].x, (int)m_vFrontGlassPoint[0].y);

	//차 왼 유리
	MoveToEx(hDC, (int)m_vLeftGlassPoint[0].x, (int)m_vLeftGlassPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vLeftGlassPoint[i].x, (int)m_vLeftGlassPoint[i].y);
	}
	LineTo(hDC, (int)m_vLeftGlassPoint[0].x, (int)m_vLeftGlassPoint[0].y);

	//차 오른 유리
	MoveToEx(hDC, (int)m_vRightGlassPoint[0].x, (int)m_vRightGlassPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vRightGlassPoint[i].x, (int)m_vRightGlassPoint[i].y);
	}
	LineTo(hDC, (int)m_vRightGlassPoint[0].x, (int)m_vRightGlassPoint[0].y);

	//차 뒷 유리
	MoveToEx(hDC, (int)m_vBackGlassPoint[0].x, (int)m_vBackGlassPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vBackGlassPoint[i].x, (int)m_vBackGlassPoint[i].y);
	}
	LineTo(hDC, (int)m_vBackGlassPoint[0].x, (int)m_vBackGlassPoint[0].y);


}

void CPlayer2::Release()
{
}

void CPlayer2::Acceleration(float _fDir)
{
	if (0 < m_fSpeed + _fDir * m_fAcceleration)
		m_fSpeed += _fDir * m_fAcceleration;
	else
		m_fSpeed = 0;
}

void CPlayer2::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Get_KeyState('A') == PRESSING && CKeyMgr::Get_Instance()->Get_KeyState(VK_SPACE) == NONE)
		m_fAngle -= D3DXToRadian(3.f);
	else if (CKeyMgr::Get_Instance()->Get_KeyState('A') == PRESSING && CKeyMgr::Get_Instance()->Get_KeyState(VK_SPACE) == PRESSING)
	{
		m_fAngle -= D3DXToRadian(5.f);
		m_eDrift = DRIFT_LEFT;
		Acceleration(1.5f);
	}

	if (CKeyMgr::Get_Instance()->Get_KeyState('D') == PRESSING && CKeyMgr::Get_Instance()->Get_KeyState(VK_SPACE) == NONE)
		m_fAngle += D3DXToRadian(3.f);
	else if (CKeyMgr::Get_Instance()->Get_KeyState('D') == PRESSING && CKeyMgr::Get_Instance()->Get_KeyState(VK_SPACE) == PRESSING)
	{
		m_fAngle += D3DXToRadian(5.f);
		m_eDrift = DRIFT_RIGHT;
		Acceleration(1.5f);
	}

	if (CKeyMgr::Get_Instance()->Get_KeyState('W') == PRESSING)
	{
		Acceleration(1.f);
	}
	else
		Acceleration(-0.5f);



	if (CKeyMgr::Get_Instance()->Get_KeyState('S') == PRESSING)
	{
		m_tInfo.vDir.x = m_tInfo.vLook.x * cos(m_fAngle) - m_tInfo.vLook.y * sin(m_fAngle);
		m_tInfo.vDir.y = m_tInfo.vLook.x * sin(m_fAngle) + m_tInfo.vLook.y * cos(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Get_KeyState(VK_SPACE) == PRESSING)
	{
		Acceleration(-3.f);
	}
}