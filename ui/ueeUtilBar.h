#ifndef UEE_UTIL_BAR
#define UEE_UTIL_BAR

#include <d3dx9.h>
#include "../dxApp.h"
#include "../dxUtil.h"

#include "base_controls/uiWindow.h"
#include "base_controls/uiLabel.h"
#include "base_controls/uiButton.h"
#include "base_controls/uiCheckBox.h"

#include "uiMgrBase.h"


class PickPropCheckBox : public uiCheckBox
{
protected:
public:
	PickPropCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class PickUnitCheckBox : public uiCheckBox
{
protected:
public:
	PickUnitCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class PickTileCheckBox : public uiCheckBox
{
protected:
public:
	PickTileCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class AssetPropCheckBox : public uiCheckBox
{
protected:
public:
	AssetPropCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class AssetResourceCheckBox : public uiCheckBox
{
protected:
public:
	AssetResourceCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class AssetUnitCheckBox : public uiCheckBox
{
protected:
public:
	AssetUnitCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};



class UEE_UtilBar : public ManagerBase
{
public:
	 UEE_UtilBar();
	~UEE_UtilBar();

	void Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop);

	void OnLost();
	void OnReset();

	void SetPicker(ToolType pick);
	void SetAssetType(int asset);

private:
							// picking by:
	uiCheckBox* thePick[3]; // tile, prop, goal

							// add/edit type:
	uiCheckBox* theAsset[3]; // prop, goal, unit

	ID3DXFont* theUtilFont;
};

#endif