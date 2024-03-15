#pragma once
#include "Obj.h"
class CMap :
    public CObj
{
public:
	CMap();
	virtual ~CMap();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
private:
	void		Key_Input();
	void		Lerp();
private:
	D3DXVECTOR3		m_vPoint[100];
	D3DXVECTOR3		m_vOriginPoint[100];
	bool m_bLerpFactor;
	bool m_bPlusLerp;
	bool m_bMinusLerp;
	float m_Scale;
	float m_MaxScale;
	float m_MinScale;
};

