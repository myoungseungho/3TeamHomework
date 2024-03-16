#pragma once
#include "Obj.h"
class CItem :
    public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private:
	D3DXVECTOR3		m_vPoint[5];
	D3DXVECTOR3		m_vOriginPoint[5];
	float m_fAngleSpeed;

};

