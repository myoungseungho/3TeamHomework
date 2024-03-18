#pragma once
#include "Obj_Stage1.h"
class CItem_Stage1 :
    public CObj_Stage1
{
public:
	CItem_Stage1();
	virtual ~CItem_Stage1();

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

