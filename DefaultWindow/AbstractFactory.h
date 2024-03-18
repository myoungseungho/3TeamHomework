#pragma once

#include "Obj.h"


template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create_Obj()
	{
		CObj*		pObj = new T;

		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create_Obj(float fX, float fY)
	{
		CObj*		pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		
		return pObj;
	}

	static CObj*		Create_Obj(float fX, float fY, float fAngle)
	{
		CObj*		pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		pObj->Set_Angle(fAngle);

		return pObj;
	}

	static CObj* Create_Obj_LTH(D3DXVECTOR3 _vPos)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_vPos);

		return pObj;
	}


};

