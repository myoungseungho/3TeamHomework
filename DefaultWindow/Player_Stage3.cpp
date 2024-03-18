#include "stdafx.h"
#include "Player_Stage3.h"
#include "ScrollMgr.h"

CPlayer::CPlayer() : m_fVel(0.f), m_fAcc(0.f)
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
	m_tInfo.vPos = { 400.f, 300.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	m_vOriginGunPoint = m_vGunPoint;
	
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 2.f;
}

void CPlayer::Update()
{

	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 400.f, 300.f, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}



	// ����

	m_vGunPoint = m_vOriginGunPoint;

	m_vGunPoint -= { 400.f, 300.f, 0.f};

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);

	////////////////////
	// �߰� + KeyInput ���� + ������� 3�� ����
	///////////////////////////////////////////////////////////////////////////
	if (m_fVel > 0.f)
	{
		float fDeceleration = 0.05f; // ���ӵ� �� ����
		m_fVel -= fDeceleration;
		if (m_fVel < 0.f)
			m_fVel = 0.f;
	}
	// �ӵ��� 0���� ������ �ݴ� �������� ����
	else if (m_fVel < 0.f)
	{
		float fDeceleration = 0.05f; // ���ӵ� �� ����
		m_fVel += fDeceleration;
		if (m_fVel > 0.f)
			m_fVel = 0.f;
	}

	D3DXVECTOR3 vMoveDir = m_tInfo.vDir * m_fVel; // ���� �ӵ��� ���� �̵� ���� ���
	m_tInfo.vPos += vMoveDir;
	///////////////////////////////////////////////////////////////////////////
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if(i > 0)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f ),
			int(m_vPoint[i].y - 5.f ),
			int(m_vPoint[i].x + 5.f ),
			int(m_vPoint[i].y + 5.f));
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);

	// ���� �׸���

	MoveToEx(hDC, (int)m_tInfo.vPos.x , (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);

}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	float fAcceleration = 0.1f;  // ���ӵ� �� ����
	float fMaxSpeed = 5.0f;  // �ִ� �ӵ� �� ����
	float fTurnAngle = 1.f;  // ������ ȸ�� ����


	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !m_bDrift && m_fVel != 0.f)
		m_fAngle += D3DXToRadian(fTurnAngle);  // ������ ������ ȸ��

	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !m_bDrift && m_fVel != 0.f)
		m_fAngle += D3DXToRadian(-fTurnAngle);  // ������ ������ ȸ��


	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fVel += fAcceleration;  // ���ӵ� ����
		if (m_fVel > fMaxSpeed)  // �ִ� �ӵ� ����
			m_fVel = fMaxSpeed;

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fVel;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fVel -= fAcceleration;  // ���ӵ� ����
		if (m_fVel < -5.f)  // �ּ� �ӵ� ����
			m_fVel = -5.f;

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * (-m_fVel); // �ӵ��� ������ �����Ͽ� ����
	}

	// �帮��Ʈ ����
	if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState(VK_LEFT) & 0x8000))
	{
		// ���� �帮��Ʈ ���� ����
		m_fAngle += D3DXToRadian(-fTurnAngle * m_fVel); // �帮��Ʈ ���� ����

		m_bDrift = true;
	}
	else if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState(VK_RIGHT) & 0x8000))
	{
		// ������ �帮��Ʈ ���� ����
		m_fAngle += D3DXToRadian(fTurnAngle * m_fVel); // �帮��Ʈ ���� ����
		m_bDrift = true;
	}
	else
		m_bDrift = false;
}