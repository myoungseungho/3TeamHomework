#pragma once
#include "Obj_Stage1.h"
#include "Stage1.h"
class CStage1;
class CPlayer_Stage1 : public CObj_Stage1
{
public:
	CPlayer_Stage1(CStage1* stage1);
	virtual ~CPlayer_Stage1();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
	pair<bool, int>		Collision_Item();
	void		Collision_Check();
	void		flipVertical();
	void		ExecuteDrift();
	void		TransformLocalToWorld();
	bool		GameOver_Check();

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3		m_vGunPoint;
	D3DXVECTOR3		m_vOriginGunPoint;

	list<D3DXVECTOR3>		m_ListSkidMark;

	int m_lastSkidFrame = 0;
	int m_skidInterval = 65 / 30;
	bool m_bShift;
	bool m_IsItemCollision = false;
	bool m_bIsFlip = false;

	CStage1* m_pMainGame;
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