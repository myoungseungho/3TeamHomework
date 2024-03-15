#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	ZeroMemory(m_vPoint, sizeof(m_vPoint));
	ZeroMemory(m_vOriginPoint, sizeof(m_vOriginPoint));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_vGunPoint = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y, 0.f };
	m_vOriginGunPoint = m_vGunPoint;

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 2.f;
}

void CPlayer::Update()
{
#pragma region 복습
	//m_tInfo.vLook = Get_Mouse() - m_tInfo.vPos;

	//float fLength = sqrt(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	//m_tInfo.vDir.x /= fLength;
	//m_tInfo.vDir.y /= fLength;
	//m_tInfo.vDir.z = 0.f;

	//float fLength2 = sqrt(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);

	//m_tInfo.vLook.x /= fLength2;
	//m_tInfo.vLook.y /= fLength2;
	//m_tInfo.vLook.z = 0.f;

	//float	fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	//float	fAngle = acos(fDot);

	//if (m_tInfo.vPos.y < Get_Mouse().y)
	//	fAngle = 2 * D3DX_PI - fAngle;

	//m_tInfo.vPos.x += m_fSpeed * cos(fAngle);
	//m_tInfo.vPos.y -= m_fSpeed * sin(fAngle);
#pragma endregion 복습

#pragma region 복습 2

	//m_tInfo.vLook = Get_Mouse() - m_tInfo.vPos;

	////float	fLength = D3DXVec3Length(&m_tInfo.vLook);

	//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	//float fDot = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);

	//// D3DXVECTOR3	vAxis;
	//// D3DXVec3Cross(&vAxis, 먼저 연산할 벡터1, 나중 연산할 벡터2)

	//float	fAngle = acos(fDot);

	//if (m_tInfo.vPos.y < Get_Mouse().y)
	//	fAngle = 2 * D3DX_PI - fAngle;

	//m_tInfo.vPos.x += m_fSpeed * cos(fAngle);
	//m_tInfo.vPos.y -= m_fSpeed * sin(fAngle);

#pragma endregion 복습 2

#pragma region 복습 3
	//for (int i = 0; i < 4; ++i)
	//{
	//	D3DXVECTOR3	vTemp = m_vOriginPoint[i];

	//	vTemp -= { 400.f, 300.f, 0.f};

	//	m_vPoint[i].x = vTemp.x * cos(m_fAngle) - vTemp.y * sin(m_fAngle);
	//	m_vPoint[i].y = vTemp.x * sin(m_fAngle) + vTemp.y * cos(m_fAngle);

	//	m_vPoint[i] += m_tInfo.vPos;
	//}

	//// 포신 회전 적용

	//D3DXVECTOR3	vTemp = m_vOriginGunPoint;

	//vTemp -= { 400.f, 300.f, 0.f};

	//m_vGunPoint.x = vTemp.x * cos(m_fAngle) - vTemp.y * sin(m_fAngle);
	//m_vGunPoint.y = vTemp.x * sin(m_fAngle) + vTemp.y * cos(m_fAngle);

	//m_vGunPoint += m_tInfo.vPos;
#pragma endregion 복습 3

	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 100.f, 100.f, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	// 포신

	m_vGunPoint = m_vOriginGunPoint;

	m_vGunPoint -= { 100.f, 100.f, 0.f};

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);
}

void CPlayer::Render(HDC hDC)
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

	// 포신 그리기

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle += D3DXToRadian(1.f);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_fAngle += D3DXToRadian(3.f);
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle += D3DXToRadian(-1.f);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_fAngle += D3DXToRadian(-3.f);
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cos(m_fAngle) - m_tInfo.vLook.y * sin(m_fAngle);
		//m_tInfo.vDir.y= m_tInfo.vLook.x * sin(m_fAngle) + m_tInfo.vLook.y * cos(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cos(m_fAngle) - m_tInfo.vLook.y * sin(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sin(m_fAngle) + m_tInfo.vLook.y * cos(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}


}
