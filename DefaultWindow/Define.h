#pragma once

#define WINCX		800
#define WINCY		600

#define PURE		= 0

#define		VK_MAX			0xff

#define		OBJ_NOEVENT	0
#define		OBJ_DEAD	1

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_STAGE2, SC_END };
enum OBJID { OBJ_PLAYER, OBJ_ITEM, OBJ_END };
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_END };

extern HWND g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// À§Ä¡ º¤ÅÍ

	D3DXVECTOR3		vDir;		// ¹æÇâ º¤ÅÍ
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vNormal;	// ¹ý¼± º¤ÅÍ

	D3DXMATRIX		matWorld;

	
}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct CDeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};




