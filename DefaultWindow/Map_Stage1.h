#pragma once
#include "Obj_Stage1.h"
class CMap_Stage1 :
    public CObj_Stage1
{
public:
	CMap_Stage1();
	virtual ~CMap_Stage1();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private:
	D3DXVECTOR3		m_vPoint[100][100];
	D3DXVECTOR3		m_vOriginPoint[100][100];

};

