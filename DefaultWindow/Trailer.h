#pragma once
#include "Obj.h"
class CTrailer :
    public CObj
{
public:
	CTrailer(CObj*);
	virtual ~CTrailer();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
private:
	void flipVertical();
private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
	bool m_bIsFlip = false;
	CObj* m_pPlayerCopy;
};

