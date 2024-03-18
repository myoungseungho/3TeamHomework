#pragma once

#include "Obj_Stage1.h"

class CMonster :	public CObj_Stage1
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

public:
	void		Set_Player(CObj_Stage1* pPlayer) {	m_pPlayer = pPlayer; }

private:
	CObj_Stage1*		m_pPlayer;

};

// 행렬 : 여러 숫자를 행과 열의 상태로 표현해 놓은 것
// 행렬의 사용 목적 : 객체의 여러 상태 표현하기 위함(크기, 회전, 위치)

//	로컬 스페이스 Vtx		*	월드 Matrix	->    월드 스페이스 Vtx
/*
						11	12	13	14
	X, Y, Z, W		*	21	22	23	24		-> (X`, Y`, Z`, W`)
						31	32	33	34
						41	42	43	44

크기 값을 저장하는 원소(배율) : 11, 22, 33
위치 값을 저장하는 원소 : 41, 42, 43

X축 회전 값을 저장하는 원소 : 22, 23, 32, 33
Y축 회전 값을 저장하는 원소 : 11, 13, 31, 33
Z축 회전 값을 저장하는 원소 : 11, 12, 21, 22

// 크 자 이 공 부
월드 행렬 = 크기 행렬 * 자전 행렬 * 이동 행렬 * 공전 행렬 * 부모 행렬

*/

// 월드 행렬 = 크기 행렬 * 이동 행렬
// 월드 행렬 = 자전 행렬 * 부모 행렬
// 월드 행렬 = 이동 행렬

// 행의 개수 x 열의 개수
// 4 X 4

// 정방 행렬 : 행과 열의 값이 일치하는 행렬
// 항등 행렬(단위 행렬) : 행렬의 값이 1인 상태


//1 2  +  5 6		=   6	8
//3 4     7 8			10	12
//
//1 2 *	  5 6  =	1 * 5 + 2 * 7  , 1 * 6 + 2 * 8	->	19	22
//3 4     7 8		3 * 5 + 4 * 7  , 3 * 6 + 4 * 8		43	50
//
//5 6 *	  1 2 = 	5 * 1 + 6 * 3  , 5 * 2 + 6 * 4  ->	23  34
//7 8		3 4		7 * 1 + 8 * 3  , 7 * 2 + 8 * 4 	 	31  46 	
//
//행렬의 곱셈 규칙
//
//1. 곱셈을 하기 위해선 반드시 앞의 행렬의 열의 값과 뒤의 행렬의 행의 값이 일치해야 곱셈이 성립된다.
// EX) 곱셈이 성립되는 예    (2 * 4) * (4 * 4)
// EX) 곱셈이 성립되지 않는 예(2 * 3) * (4 * 4)
//
//2. 행렬의 곱셈의 결과 값은 앞의 행렬의 행과 뒤의 행렬의 열 상태의 조합으로 이뤄진다.
//EX) (1 * 4) * (4 * 2) -결과 행렬 > (1 * 2)
//
//3. 행렬의 곱셈은 항상 교환 법칙이 성립하지는 않는다.
//// A * B /= B * A
//
//4. 어떤 행렬과 항등 행렬을 곱할 경우에는 교환 법칙이 성립한다.
//
//1 2  * 1 0  ->	1 * 1 + 2 * 0,  1 * 0 + 2 * 1	->	1	2 
//3 4	   0 1		3 * 1 + 4 * 0,  3 * 0 + 4 * 1		3	4
//
//5. 어떤 행렬과 그 행렬의 역행렬을 곱할 경우 결과 값은 항등 행렬이 된다.
//ex) A * A^-1 = I		-> A / A 



// 단위 벡터를 만들어주는 함수
// D3DXVec3Normalize(단위벡터의 결과 값을 저장할 벡터의 주소, 단위벡터로 만들고자 하는 벡터의 주소)

// 벡터의 크기를 계산해주는 함수
// D3DXVec3Length(크기를 구하고자 하는 벡터의 주소)

// 벡터의 내적을 수행하는 함수
// D3DXVec3Dot(방향벡터1의 주소, 방향벡터2의 주소)

// 벡터의 외적을 수행하는 함수
// D3DXVec3Cross(결과 값을 저장할 벡터의 주소, 방향벡터 1의 주소, 방향벡터 2의 주소)

// 항등 행렬을 만들어주는 함수
// D3DXMatrixIdentity(결과 값을 저장할 행렬의 주소)

// 크기 변환 행렬을 만들어주는 함수
// D3DXMatrixScaling(결과 값을 저장할 행렬의 주소, x배율, y배율, z배율)

// 이동 변환 행렬을 만들어주는 함수
// D3DXMatrixTranslation(결과 값을 저장할 행렬의 주소, x위치, y위치, z위치)

// 회전 변환 행렬을 만들어주는 함수
// D3DXMatrixRotationZ(결과 값을 저장할 행렬의 주소, 회전 각도(라디안))

// 벡터와 행렬을 곱셈해주는 함수
// 위치 벡터 = D3DXVec3TransformCoord(결과 벡터, 위치 벡터, 행렬)
// 방향 벡터 = D3DXVec3TransformNormal(결과 벡터, 방향 벡터, 행렬)