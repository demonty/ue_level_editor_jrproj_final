#ifndef UEE_TOOL_BAR_H
#define UEE_TOOL_BAR_H

#include <d3dx9.h>
#include "../dxApp.h"
#include "../dxUtil.h"

#include "base_controls/uiWindow.h"
#include "base_controls/uiLabel.h"
#include "base_controls/uiButton.h"
#include "base_controls/uiCheckBox.h"

#include "uiMgrBase.h"

class UpButton : public uiButton
{
protected:
public:
	UpButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class DownButton : public uiButton
{
protected:
public:
	DownButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class LeftButton : public uiButton
{
protected:
public:
	LeftButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class RightButton : public uiButton
{
protected:
public:
	RightButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class XZCheckBox : public uiCheckBox
{
protected:
public:
	XZCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class XYCheckBox : public uiCheckBox
{
protected:
public:
	XYCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class YZCheckBox : public uiCheckBox
{
protected:
public:
	YZCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class MoveToolCheckBox : public uiCheckBox
{
protected:
public:
	MoveToolCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class ScaleToolCheckBox : public uiCheckBox
{
protected:
public:
	ScaleToolCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class UniformScaleButton : public uiCheckBox
{
protected:
public:
	UniformScaleButton(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class RotateToolCheckBox : public uiCheckBox
{
protected:
public:
	RotateToolCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class MoveAmtWindow : public uiWindow
{
protected:
public:
	MoveAmtWindow(bool isParent, LPDIRECT3DDEVICE9 device)
		: uiWindow(isParent, device) {}
};

class AmtLabel : public uiLabel
{
protected:
public:
	AmtLabel(LPDIRECT3DDEVICE9 device)
		: uiLabel(device) {}
};

class AmtSpot : public uiCheckBox
{
protected:
	int spot;
	int amt;

public:
	AmtSpot(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();

	void SetSpot(int s);
	void SetAmt(int a);
	int  GetSpot();
	int  GetAmt();
	void AddAmt();
	void RemAmt();
};

class AddToAmt : public uiButton
{
protected:
public:
	AddToAmt(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class RemoveAmt : public uiButton
{
protected:
public:
	RemoveAmt(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class ClearAmtButton : public uiButton
{
protected:
public:
	ClearAmtButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class AddAssetButton : public uiButton
{
protected:
public:
	AddAssetButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class RemoveAssetButton : public uiButton
{
protected:
public:
	RemoveAssetButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};

class GoodBadUnitCheckBox : public uiCheckBox
{
protected:
public:
	GoodBadUnitCheckBox(LPDIRECT3DDEVICE9 device)
		: uiCheckBox(device) {}
	void DoStuff();
};

class AssetPreviewWindow : public uiWindow
{
protected:
	ToolType assetType;
	PropType propType;

	int currentPreview;
	int numPreviews;
	std::vector<IDirect3DTexture9*> allTextures;
	std::vector<IDirect3DTexture9*> textures;

public:
	AssetPreviewWindow(bool isParent, LPDIRECT3DDEVICE9 device)
		: uiWindow(isParent, device) {}

	void	  SetAssetType(ToolType t);
	PropType  GetPropType();
	void	  Next();
	void	  Prev();
	void      LoadAllTextures();
	void	  LoadTextures(ToolType type);
	void	  UnloadAllTextures();
	PropType  GetFromPreview();
};

class NextAssetButton : public uiButton
{
protected:
public:
	NextAssetButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};
class PrevAssetButton : public uiButton
{
protected:
public:
	PrevAssetButton(LPDIRECT3DDEVICE9 device)
		: uiButton(device) {}
	void DoStuff();
};




class UEE_ToolBar : public ManagerBase
{
public:
	AssetPreviewWindow*   thePreviewWindow;

	 UEE_ToolBar();
	~UEE_ToolBar();

	void Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop);

	void OnLost();
	void OnReset();

	void  SetTool(ToolType tool);
	void  SetAxis(int axis);
	void  SetSpot();
	void  AddSpot();
	void  RemSpot();
	int   GetSpot();
	float GetAmt();
	void  ClearAmt();
	void  SetAssetType(ToolType asset);
	void  SetPreviewLabel();

private:
	uiCheckBox* theAxis[3];
	uiCheckBox* theTool[3];

	uiLabel*    thePreviewLabel;
	
	AmtSpot*    theSpot[4];
	int         theCurrentSpot;
	AmtLabel*   theAmtLbl;
	AddToAmt*   theAmtAddBtn;
	RemoveAmt*  theAmtRemBtn;

	IDirect3DTexture9* chkUpTex;
	IDirect3DTexture9* chkDnTex;
	ID3DXFont* theToolFont;
};


#endif