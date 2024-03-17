#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(CStage1* maingame) : m_bShift(false), m_pMainGame(maingame)
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
	m_InitX = 50.f;
	m_InitY = 20.f;
	m_Scale = m_MinScale;
	m_ScaleY = m_MinScale;
	m_tInfo.vPos = { m_InitX, m_InitY, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 2.f;
}

void CPlayer::Update()
{
	Key_Input();
	TransformLocalToWorld();
	ExecuteDrift();
	Collision_Check();
	flipVertical();
	GameOver_Check();
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


	if (m_ListSkidMark.size() != 0)
	{
		MoveToEx(hDC, (int)m_ListSkidMark.front().x, (int)m_ListSkidMark.front().y, nullptr);

		for (auto& iter : m_ListSkidMark)
		{
			LineTo(hDC, (int)iter.x, (int)iter.y);
		}
	}
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	static int frameCount = 0; // 정적 변수로 프레임 카운트를 유지
	frameCount++; // 매 호출마다 프레임 카운트 증가

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle += D3DXToRadian(1.f);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_fAngle += D3DXToRadian(3.f);
			// 마지막 스키드 마크 추가 후 충분한 프레임이 경과했는지 확인
			if (frameCount - m_lastSkidFrame >= m_skidInterval)
			{
				m_bShift = true;
				m_ListSkidMark.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y + 10.f, 0.f));
				m_lastSkidFrame = frameCount; // 마지막 스키드 마크 추가 시점 업데이트
			}
		}
	}


	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle += D3DXToRadian(-1.f);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_fAngle += D3DXToRadian(-3.f);

			// 마지막 스키드 마크 추가 후 충분한 프레임이 경과했는지 확인
			if (frameCount - m_lastSkidFrame >= m_skidInterval)
			{
				m_bShift = true;
				m_ListSkidMark.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y + 10.f, 0.f));
				m_lastSkidFrame = frameCount; // 마지막 스키드 마크 추가 시점 업데이트
			}
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
}

pair< bool, int> CPlayer::Collision_Item()
{
	if (m_tInfo.vPos.x >= 140.f && m_tInfo.vPos.x <= 160.f)
	{
		if ((m_tInfo.vPos.y >= 15.f && m_tInfo.vPos.y <= 35.f))
		{
			return pair<bool, int>{ true, 0 };
		}
		else if ((m_tInfo.vPos.y >= 215.f && m_tInfo.vPos.y <= 235.f))
		{
			return pair<bool, int>{ true, 1 };
		}
		else if ((m_tInfo.vPos.y >= 415.f && m_tInfo.vPos.y <= 435.f))
		{
			return pair<bool, int>{ true, 2 };
		}
	}
	return pair<bool, int>{ false, -1 };
}

void CPlayer::Collision_Check()
{
	pair<bool, int> pairBoolInt = Collision_Item();
	if (pairBoolInt.first == true)
	{
		if (!m_IsItemCollision)
			m_IsItemCollision = true;

		m_pMainGame->ObserverPlayer(pairBoolInt);
	}
}

void CPlayer::flipVertical()
{
	if ((m_tInfo.vPos.y >= 80.f) && (m_tInfo.vPos.y <= 180.f)
		|| (m_tInfo.vPos.y >= 280.f) && (m_tInfo.vPos.y <= 380.f)
		|| (m_tInfo.vPos.y >= 480.f) && (m_tInfo.vPos.y <= 580.f))
		m_bIsFlip = true;
	else
		m_bIsFlip = false;
}

void CPlayer::ExecuteDrift()
{
	if (m_bShift)
	{
		static int frameCount = 0;
		frameCount++;

		if (frameCount > 65 / 15.f)
		{
			if (m_ListSkidMark.size() == 0)
			{
				m_bShift = false;
			}
			else
			{
				m_ListSkidMark.pop_front();
				frameCount = 0;
			}
		}
	}
}

void CPlayer::TransformLocalToWorld()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_Scale, m_bIsFlip ? -m_ScaleY : m_ScaleY, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { m_InitX, m_InitY, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
}

bool CPlayer::GameOver_Check()
{
	if (m_tInfo.vPos.x < -50.f)
		return true;
	else
		return false;
}
