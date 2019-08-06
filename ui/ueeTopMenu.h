#ifndef TOP_MENU_CONTROLS_H
#define TOP_MENU_CONTROLS_H

#include <d3dx9.h>
#include "../dxApp.h"
#include "../dxUtil.h"

#include "base_controls/uiWindow.h"
#include "base_controls/uiLabel.h"
#include "base_controls/uiButton.h"
#include "base_controls/uiCheckBox.h"

#include "uiMgrBase.h"

class NewButton : public uiButton
{
protected:
public:
	NewButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class SaveButton : public uiButton
{
protected:
public:
	SaveButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class SaveNav : public uiButton
{
protected:
public:
	SaveNav(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class LoadButton : public uiButton
{
protected:
public:
	LoadButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class ClearButton : public uiButton
{
protected:
public:
	ClearButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class QuitButton : public uiButton
{
protected:
public:
	QuitButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class FullScreenButton : public uiButton
{
protected:
public:
	FullScreenButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class MainCamCheckBox : public uiCheckBox
{
protected:
public:
	MainCamCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class CamXZCheckBox : public uiCheckBox
{
protected:
public:
	CamXZCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class CamXYCheckBox : public uiCheckBox
{
protected:
public:
	CamXYCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class CamYZCheckBox : public uiCheckBox
{
protected:
public:
	CamYZCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class CamToggleLookCheckBox : public uiCheckBox
{
protected:
public:
	CamToggleLookCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};


class UEE_TopMenu : public ManagerBase
{
public:
	 UEE_TopMenu();
	~UEE_TopMenu();

	void Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop);
	
	void  OnLost();
	void  OnReset();

	void  SetCam(int cam);
	int   GetCam();
private:
	uiCheckBox* theCam[4];

	IDirect3DTexture9* chkUp;
	IDirect3DTexture9* chkDn;
	ID3DXFont*	theMenuFont;
};

#endif