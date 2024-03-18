#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int  Update()		PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release()		PURE;

public:
	INFO		Get_Info() { return m_tInfo; }

	void		Set_Dir(D3DXVECTOR3 _vDir) { m_tInfo.vDir = _vDir; }
	void		Set_Pos(D3DXVECTOR3 _vPos) { m_tInfo.vPos = _vPos; }

	void		Set_Dead() { m_bDead = true; }
	bool		Get_Dead() { return m_bDead; }

	float		Get_Angle() { return m_fAngle; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	RENDERID	Get_RenderID() { return m_eRender; }

protected:
	INFO		m_tInfo;

	RENDERID	m_eRender;

	float		m_fAngle;
	float		m_fSpeed;
	bool		m_bDead;
};

