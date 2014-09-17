#include "Includes.h"
#include "DirectX.h"

// display a message box with arbitrary parameter list and then terminate the program
void quit(const char * title, const char * message, ...) {
	if(message != NULL) {
		char buffer[256];
		va_list parameters;
		va_start(parameters, message);
		vsprintf_s(buffer, 256, message, parameters);
		va_end(parameters);
		MessageBoxA(NULL, buffer, title, MB_OK);
	}
	exit(1);
}

// display a message box with arbitrary parameter list
void prompt(const char * message, ...) {
	if(message != NULL) {
		char buffer[256];
		va_list parameters;
		va_start(parameters, message);
		vsprintf_s(buffer, 256, message, parameters);
		va_end(parameters);
		MessageBoxA(NULL, buffer, "Message", MB_OK);
	}
}

#if _DEBUG
	struct testDrawPointVertex {
		float x, y, z, rhw;
		DWORD colour;
	};

	// test draw a single point (small box) at given coordinates
	void testDrawPoint(LPDIRECT3DDEVICE9 d3dDevice, float x, float y) {
		float r = 2;
		testDrawPointVertex vertex[] = {
			{x-r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+r, y+r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-r, y+r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)}
		};

		d3dDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
		d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, &vertex, sizeof(testDrawPointVertex));
	}

	// draw an empty box at given coordinates with a set radius
	void testDrawEmptyBox(LPDIRECT3DDEVICE9 d3dDevice, float x, float y, float r) {
		testDrawPointVertex vertex[] = {
			{x-r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+r, y+r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-r, y+r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-r, y-r, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)}
		};

		d3dDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
		d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vertex, sizeof(testDrawPointVertex));
	}

	// draw an empty box at given coordinates with a specified x and y radius
	void testDrawEmptyBox(LPDIRECT3DDEVICE9 d3dDevice, float x, float y, float xr, float yr) {
		testDrawPointVertex vertex[] = {
			{x-xr, y-yr, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+xr, y-yr, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x+xr, y+yr, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-xr, y+yr, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-xr, y-yr, 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)}
		};

		d3dDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
		d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vertex, sizeof(testDrawPointVertex));
	}

	// draw an empty circle at given coordinates with a specified x and y radius
	void testDrawEmptyCircle(LPDIRECT3DDEVICE9 d3dDevice, float x, float y, float xr, float yr) {
		float c = 16;
		float a = 0;
		float i = 360.0f / c;
		testDrawPointVertex vertex[] = {
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)},
			{x-(sin(D3DXToRadian(a+=i))*xr), y-(cos(D3DXToRadian(a))*yr), 0, 0.5, D3DCOLOR_XRGB(0, 255, 0)}
		};

		d3dDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
		d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, (unsigned int) (c), &vertex, sizeof(testDrawPointVertex));
	}

#endif
