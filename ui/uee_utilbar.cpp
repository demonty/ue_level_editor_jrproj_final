#include "ueeUtilBar.h"

void PickPropCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_PICK_PROP;
}

void PickUnitCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_PICK_UNIT;
}

void PickTileCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_PICK_TILE;
}

void AssetPropCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_ASSET_PROP;
}

void AssetResourceCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_ASSET_RESOURCE;
}

void AssetUnitCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_ASSET_UNIT;
}




UEE_UtilBar::UEE_UtilBar()
{
	SetType(M_UTILBAR);
}

UEE_UtilBar::~UEE_UtilBar()
{
	theMsgSendingControls.clear();
	ReleaseCOM(theUtilFont);
}

void UEE_UtilBar::OnLost()
{
	theUtilFont->OnLostDevice();
}

void UEE_UtilBar::OnReset()
{
	theUtilFont->OnResetDevice();
}

void UEE_UtilBar::Initialize(LPDIRECT3DDEVICE9 device, MouseResource *mresource, uiWindow *desktop)
{
	theDesktop = desktop;

	myWindow = new uiWindow(false, device);
	myWindow->SetWidth(256);
	myWindow->SetHeight(128);
	myWindow->SetXYPos(1024.0f, 0.0f);
	myWindow->LoadCanvasFromFile("art/gui/windows/ue_util_win.dds");
	myWindow->SetDrag(false);
	theDesktop->AddChild(myWindow);

	D3DXFONT_DESC fontDesc;
	fontDesc.Height = 16;
	fontDesc.Width = 0;
	fontDesc.Weight = FW_NORMAL;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, _T("Arial"));
	D3DXCreateFontIndirect(device, &fontDesc, &theUtilFont);

	uiLabel* tempLbl = new uiLabel(device);
	tempLbl->SetHeight(16);
	tempLbl->SetWidth(32);
	tempLbl->SetXYPos(32.0f, 8.0f);
	tempLbl->SetCaption("pick by:");
	tempLbl->SetFont(theUtilFont);
	tempLbl->SetFormat(DT_NOCLIP);
	tempLbl->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	myWindow->AddChild(tempLbl);

	thePick[0] = new PickPropCheckBox(device);
	thePick[1] = new PickUnitCheckBox(device);
	thePick[2] = new PickTileCheckBox(device);

	for(int i = 0; i < 3; i++)
	{
		thePick[i]->SetWidth(16);
		thePick[i]->SetHeight(16);
		thePick[i]->SetXYPos(42.0f, 32.0f + i*24.0f);
		thePick[i]->LoadDefaultImgFromFile("art/gui/checkboxes/check_no.dds");
		thePick[i]->LoadCheckedImgFromFile("art/gui/checkboxes/check_yes.dds");
		thePick[i]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
		thePick[i]->SetCaptionFormat(DT_NOCLIP);
		thePick[i]->SetCaptionFont(theUtilFont);
		myWindow->AddChild(thePick[i]);
		theMsgSendingControls.push_back(thePick[i]);
	}

	thePick[0]->SetCaption(":prop");
	thePick[1]->SetCaption(":unit");
	thePick[2]->SetCaption(":tile");
	SetPicker(PICK_PROP);

	tempLbl = new uiLabel(device);
	tempLbl->SetHeight(16);
	tempLbl->SetWidth(32);
	tempLbl->SetXYPos(124.0f, 8.0f);
	tempLbl->SetCaption("asset type to add:");
	tempLbl->SetFont(theUtilFont);
	tempLbl->SetFormat(DT_NOCLIP);
	tempLbl->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	myWindow->AddChild(tempLbl);

	theAsset[0] = new AssetPropCheckBox(device);
	theAsset[1] = new AssetUnitCheckBox(device);
	theAsset[2] = new AssetResourceCheckBox(device);

	for(int i = 0; i < 3; i++)
	{
		theAsset[i]->SetWidth(16);
		theAsset[i]->SetHeight(16);
		theAsset[i]->SetXYPos(140.0f, 32.0f + i*24.0f);
		theAsset[i]->LoadDefaultImgFromFile("art/gui/checkboxes/check_no.dds");
		theAsset[i]->LoadCheckedImgFromFile("art/gui/checkboxes/check_yes.dds");
		theAsset[i]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
		theAsset[i]->SetCaptionFormat(DT_NOCLIP);
		theAsset[i]->SetCaptionFont(theUtilFont);
		myWindow->AddChild(theAsset[i]);
		theMsgSendingControls.push_back(theAsset[i]);
	}
	
	theAsset[0]->SetCaption(":props");
	theAsset[1]->SetCaption(":units");
	theAsset[2]->SetCaption(":resources");

	SetAssetType(0);


}

void UEE_UtilBar::SetPicker(ToolType pick)
{
	switch(pick)
	{
	case PICK_PROP:
		thePick[0]->SetChecked(true);
		thePick[1]->SetChecked(false);
		thePick[2]->SetChecked(false);
		break;
	case PICK_UNIT:
		thePick[0]->SetChecked(false);
		thePick[1]->SetChecked(true);
		thePick[2]->SetChecked(false);
		break;
	case PICK_TILE:
		thePick[0]->SetChecked(false);
		thePick[1]->SetChecked(false);
		thePick[2]->SetChecked(true);
		break;
	default:
		break;
	};
}

void UEE_UtilBar::SetAssetType(int asset)
{
	switch(asset)
	{
	case 0:
		theAsset[0]->SetChecked(true);
		theAsset[1]->SetChecked(false);
		theAsset[2]->SetChecked(false);
		break;
	case 1:
		theAsset[0]->SetChecked(false);
		theAsset[1]->SetChecked(true);
		theAsset[2]->SetChecked(false);
		break;
	case 2:
		theAsset[0]->SetChecked(false);
		theAsset[1]->SetChecked(false);
		theAsset[2]->SetChecked(true);
		break;
	default:
		break;
	};
}