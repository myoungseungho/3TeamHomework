

#pragma once
#include "Obj.h"

#define PLAYER2_CX 50.f
#define PLAYER2_CY 100.f

enum DRIFT_STATE { NOT_DRIFT, DRIFT_LEFT, DRIFT_RIGHT, DRIFT_STATE_END };

class CPlayer2 :
    public CObj
{
public:
    CPlayer2();
    virtual ~CPlayer2() { Release(); }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    D3DXVECTOR3 Get_Up_Vector() { return m_vUp; }
    D3DXVECTOR3 Get_Right_Vector() { return m_vRight; }

    D3DXVECTOR3* Get_Body() { return m_vBodyPoint; }


private:
    void    Acceleration(float _fDir);
    void	Key_Input();

private:
    D3DXVECTOR3		m_vBodyPoint[8];
    D3DXVECTOR3		m_vOriginBodyPoint[8];

    D3DXVECTOR3		m_vFrontGlassPoint[4];
    D3DXVECTOR3		m_vOriginFrontGlassPoint[4];

    D3DXVECTOR3		m_vLeftGlassPoint[4];
    D3DXVECTOR3		m_vOriginLeftGlassPoint[4];

    D3DXVECTOR3		m_vRightGlassPoint[4];
    D3DXVECTOR3		m_vOriginRightGlassPoint[4];

    D3DXVECTOR3		m_vBackGlassPoint[4];
    D3DXVECTOR3		m_vOriginBackGlassPoint[4];

    D3DXVECTOR3     m_vUp;
    D3DXVECTOR3     m_vRight;
    D3DXVECTOR3     m_vOriginUp;
    D3DXVECTOR3     m_vOriginRight;

    float m_fAcceleration;

    DRIFT_STATE m_eDrift;



};

