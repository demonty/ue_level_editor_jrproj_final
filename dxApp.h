#ifndef DXAPP_H
#define DXAPP_H

#include "dxUtil.h"
#include <string>

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance, std::string winCaption,
		   D3DDEVTYPE devType, DWORD requestedVP);
	virtual ~D3DApp();

	HINSTANCE getAppInstance();
	HWND	  getMainWindow();

	virtual bool checkDeviceCaps() {return true;}
	virtual void onLostDevice() {}
	virtual void onResetDevice() {}
	virtual void updateScene(float dt){}
	virtual void drawScene(){}

	virtual void initMainWindow();
	virtual void initDirect3D();
	virtual int run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void enableFullScreen(bool enable);
	bool isDeviceLost();

	D3DPRESENT_PARAMETERS theD3DPP;

protected:
	std::string theWindowCaption;
	D3DDEVTYPE  theDevType;
	DWORD		theRequestedVP;

	HINSTANCE		theAppInstance;
	HWND			theMainWindow;
	IDirect3D9*		theD3DObject;
	bool			isPaused;
};

extern D3DApp* theApp;
extern IDirect3DDevice9* gDevice;

#endif //dxapp.h