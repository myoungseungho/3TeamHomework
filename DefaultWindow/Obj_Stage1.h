#pragma once

#include "Define.h"

class CObj_Stage1
{
public:
	CObj_Stage1();
	virtual ~CObj_Stage1();

public:
	INFO		Get_Info() { return m_tInfo; }
	void		Set_Pos(float _x, float _y) { m_InitX = _x, m_InitY = _y; }

public:
	virtual void Initialize()		PURE;
	virtual void Update()			PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

public:
	bool Lerp(int);
	void SetSpeed(float _speed) { m_fSpeed = _speed; }

protected:
	INFO		m_tInfo;

	float		m_fSpeed;
	float		m_fAngle;

	float m_InitX = 0.f;
	float m_InitY = 0.f;

	bool m_bPlusLerp = false;
	bool m_bMinusLerp = false;
	float m_Scale = 0.f;
	float m_ScaleY = 0.f;
	float m_MaxScale = 0.f;
	float m_MinScale = 0.f;
};
