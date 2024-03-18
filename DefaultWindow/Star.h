
#pragma once
#include "Obj.h"

#define STAR_CX 50.f
#define STAR_CY 50.f
#define STAR_LIFETIME 5000


class CStar :
    public CObj
{
public:
    CStar();
    virtual ~CStar() { Release(); }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    D3DXVECTOR3 Get_Up_Vector() { return m_vUp; }
    D3DXVECTOR3 Get_Right_Vector() { return m_vRight; }

    D3DXVECTOR3* Get_Point() { return m_vPoint; }

private:
    D3DXVECTOR3		m_vPoint[4];
    D3DXVECTOR3		m_vOriginPoint[4];

    D3DXVECTOR3     m_vUp;
    D3DXVECTOR3     m_vRight;
    D3DXVECTOR3     m_vOriginUp;
    D3DXVECTOR3     m_vOriginRight;

    DWORD           m_dwLifeTime;

};

