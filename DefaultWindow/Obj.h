#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
	
public:
	INFO		Get_Info() { return m_tInfo; }


public:
	virtual void Initialize()		PURE;
	virtual void Update()			PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;


protected:
	INFO		m_tInfo;

	float		m_fSpeed;
	float		m_fAngle;
};

// 출력 연산의 최소 단위 = vertex
// 출력의 최소 단위 = polygon

// vertex - Polygon - subset - mesh

// 버텍스 프로세싱 = 정점의 변환 + 조명 연산(명암)

// 렌더링 파이프 라인(dx9)
// 로컬 스페이스 - 월드 스페이스 - 뷰 스페이스 - 후면 추려내기 - 조명 - 클리핑 - 투영 - 뷰포트 변환 - 레스터라이즈