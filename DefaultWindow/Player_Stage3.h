#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void Late_Update() override;



private:
	void		Key_Input();


private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3		m_vGunPoint;
	D3DXVECTOR3		m_vOriginGunPoint;

	/// 새로 추가
	float m_fVel;
	float m_fAcc;

	bool m_bDrift;




};

//A(x, y, z) 

//B(x`, y`, z`)
//
//A X B  -> (x*x`, y*y`, z*z`)

// 내적과 외적 (벡터의 곱셈) : 반드시 두 방향 벡터여야 한다.

// 내적(스칼라 곱) : 결과 값이 스칼라(상수), x * x` + y * y` + z * z`, 두 방향 벡터가 반드시 단위 벡터여야 한다.
// A • B

// 외적(벡터 곱) : 결과 값이 방향 벡터, (y * z` - z * y`, x * z` - z * x`, x * y` - y * x`), 두 방향 벡터만 있으면 된다.
// A X B


// 내적을 이용하여 마우스 포인터를 따라 다니는 플레이어를 만들어라.