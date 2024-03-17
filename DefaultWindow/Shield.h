#pragma once
#include "Obj.h"
class CShield :
	public CObj
{
public:
	CShield(CObj*);
	virtual ~CShield();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private:
	CObj* m_pPlayerCopy;
	float m_OrbitRadius = 0.f;
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
};

