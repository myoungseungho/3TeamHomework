#pragma once

#define WINCX		800
#define WINCY		600

#define PURE		= 0

extern HWND g_hWnd;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// À§Ä¡ º¤ÅÍ

	D3DXVECTOR3		vDir;		// ¹æÇâ º¤ÅÍ
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vNormal;	// ¹ý¼± º¤ÅÍ

	D3DXMATRIX		matWorld;
	
}INFO;

static D3DXVECTOR3		Get_Mouse()
{
	POINT		Pt;

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}
