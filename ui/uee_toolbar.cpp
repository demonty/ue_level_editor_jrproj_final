#include "ueeToolBar.h"

void UpButton::DoStuff()
{
	theMessageToSend = UIMT_UP_TOOL;
}

void DownButton::DoStuff()
{
	theMessageToSend = UIMT_DOWN_TOOL;
}

void LeftButton::DoStuff()
{
	theMessageToSend = UIMT_LEFT_TOOL;
}

void RightButton::DoStuff()
{
	theMessageToSend = UIMT_RIGHT_TOOL;
}

void XZCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_XZ_AXIS;
}

void XYCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_XY_AXIS;
}

void YZCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_YZ_AXIS;
}

void MoveToolCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_MOVE_TOOL;
}

void ScaleToolCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_SCALE_TOOL;
}

void UniformScaleButton::DoStuff()
{
	theMessageToSend = UIMT_SCALE_UNIFORM;
}

void RotateToolCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_ROTATE_TOOL;
}

void AmtSpot::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_CHANGE_SPOT;
}

void AmtSpot::SetSpot(int s)
{
	spot = s;
}

void AmtSpot::SetAmt(int a)
{
	amt = a;
}

int AmtSpot::GetSpot()
{
	return spot;
}

int AmtSpot::GetAmt()
{
	return amt;
}

void AmtSpot::AddAmt()
{
	amt++;
	if(amt > 9)
		amt = 0;
}

void AmtSpot::RemAmt()
{
	amt--;
	if(amt < 0)
		amt = 9;
}

void AddToAmt::DoStuff()
{
	theMessageToSend = UIMT_ADD_AMT;
}

void RemoveAmt::DoStuff()
{
	theMessageToSend = UIMT_REM_AMT;
}

void ClearAmtButton::DoStuff()
{
	theMessageToSend = UIMT_CLR_AMT;
}

void AddAssetButton::DoStuff()
{
	theMessageToSend = UIMT_ADD_ASSET;
}

void RemoveAssetButton::DoStuff()
{
	theMessageToSend = UIMT_REMOVE_ASSET;
}

void GoodBadUnitCheckBox::DoStuff()
{
//	theMessageToSend = UIMT_UNIT_FACTION;
} 

void NextAssetButton::DoStuff()
{
	theMessageToSend = UIMT_NEXT_ASSET;
}

void PrevAssetButton::DoStuff()
{
	theMessageToSend = UIMT_PREV_ASSET;
}

void AssetPreviewWindow::LoadAllTextures()
{
	allTextures.resize(20);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/rock01_preview.dds", &allTextures[0]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/rock02_preview.dds", &allTextures[1]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/rock03_preview.dds", &allTextures[2]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/fence_preview.dds", &allTextures[3]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/gate_preview.dds", &allTextures[4]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/dwall_preview.dds", &allTextures[5]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/tombstone01_preview.dds", &allTextures[6]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/tombstone02_preview.dds", &allTextures[7]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/gunit_preview.dds", &allTextures[8]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/sp_base_preview.dds", &allTextures[9]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/sp_base_upgrade_preview.dds", &allTextures[10]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/spgunit_building_preview.dds", &allTextures[11]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/blank_preview.dds", &allTextures[12]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/straight_preview.dds", &allTextures[13]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/elbow_preview.dds", &allTextures[14]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/cross_preview.dds", &allTextures[15]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/zunit_preview.dds", &allTextures[16]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/zbase_preview.dds", &allTextures[17]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/coal_preview.dds", &allTextures[18]);
	D3DXCreateTextureFromFile(theDevice, "art/gui/previews/graveyard_preview.dds", &allTextures[19]);
}

void AssetPreviewWindow::LoadTextures(ToolType type)
{
	switch(type)
	{

	case ASSET_PROP:
		textures.clear();
		textures.resize(11);
		textures[0]  = allTextures[0];
		textures[1]  = allTextures[1];
		textures[2]  = allTextures[2];
		textures[3]  = allTextures[3];
		textures[4]  = allTextures[4];
		textures[5]  = allTextures[5];
		textures[6]  = allTextures[6];
		textures[7]  = allTextures[7];
		textures[8]  = allTextures[13];
		textures[9]  = allTextures[14];
		textures[10] = allTextures[15];
		numPreviews  = 11;
		break;

	case ASSET_UNIT:
		textures.clear();
		textures.resize(4);
		textures[0] = allTextures[8];
		textures[1] = allTextures[9];
		textures[2] = allTextures[16];//blank for now
		textures[3] = allTextures[17];//blank for now
		numPreviews = 4;
		break;

	case ASSET_RESOURCE:
		textures.clear();
		numPreviews = 2;
		textures.resize(2);
		textures[0] = allTextures[18];//blank for now
		textures[1] = allTextures[19];
		break;

	default:
		break;
	};

	currentPreview = 0;
}


void AssetPreviewWindow::SetAssetType(ToolType t)
{
	if(t == assetType) return;

	LoadTextures(t);
	assetType = t;
	Next();
	Prev();
}

PropType AssetPreviewWindow::GetPropType()
{
	return propType;
}

void AssetPreviewWindow::UnloadAllTextures()
{
	textures.clear();

	for(UINT i = 0; i < allTextures.size(); i++)
		ReleaseCOM(allTextures[0]);
	allTextures.clear();
}

void AssetPreviewWindow::Next()
{
	switch(assetType)
	{
	case ASSET_RESOURCE:
	case ASSET_PROP:
	case ASSET_UNIT:
		currentPreview++;
		if(currentPreview > (numPreviews-1))
		{
			currentPreview = 0;
		}
		SetCanvas(textures[currentPreview]);
		propType = GetFromPreview();
		break;

	default:
		break;
	};
}

void AssetPreviewWindow::Prev()
{
	switch(assetType)
	{
	case ASSET_RESOURCE:
	case ASSET_PROP:
	case ASSET_UNIT:
		currentPreview--;
		if(currentPreview < 0)
		{
			currentPreview = numPreviews - 1;
		}
		SetCanvas(textures[currentPreview]);
		propType = GetFromPreview();
		break;

	default:
		break;
	};
}

PropType AssetPreviewWindow::GetFromPreview()
{
	PropType pt;

	switch(assetType)
	{
	case ASSET_PROP:
		switch(currentPreview)
		{
		case 0:
			pt = PROP_ROCK01;
			break;
		case 1:
			pt = PROP_ROCK02;
			break;
		case 2:
			pt = PROP_ROCK03;
			break;
		case 3:
			pt = PROP_FENCE;
			break;
		case 4:
			pt = PROP_GATE;
			break;
		case 5:
			pt = PROP_DESTROYED_WALL_01;
			break;
		case 6:
			pt = PROP_TOMBSTONE01;
			break;
		case 7:
			pt = PROP_TOMBSTONE02;
			break;
		case 8:
			pt = PROP_PIPE_STRAIGHT;
			break;
		case 9:
			pt = PROP_PIPE_ELBOW;
			break;
		case 10:
			pt = PROP_PIPE_CROSS;
			break;
		default:
			pt = INVALID_PROP;
			break;
		};
		break;

	case ASSET_UNIT:
		switch(currentPreview)
		{
		case 0:
			pt = UNIT_SP_GROUND;
			break;

		case 1:
			pt = BUILDING_SP_BASE;
			break;

		case 2:
			pt = UNIT_Z_GROUND;
			break;

		case 3:
			pt = BUILDING_Z_BASE;
			break;

		//case 2:
		//	pt = BUILDING_UPGRAYEDD;
		//	break;
		//case 3:
		//	pt = BUILDING_GUNIT;
		//	break;
		default:
			pt = INVALID_PROP;
			break;
		};
		break;

	case ASSET_RESOURCE:
		switch(currentPreview)
		{
		case 0:
			pt = BUILDING_COAL_MINE;
			break;
		case 1:
			pt = BUILDING_GRAVEYARD;
			break;
		default:
			pt = INVALID_PROP;
			break;
		};

		break;

	default:
		pt = INVALID_PROP;
		break;
	};

	return pt;
}


//============================
// tool bar
//============================

UEE_ToolBar::UEE_ToolBar()
{
	SetType(M_TOOLBAR);
}

UEE_ToolBar::~UEE_ToolBar()
{
	thePreviewWindow->UnloadAllTextures();
	theMsgSendingControls.clear();
	ReleaseCOM(chkUpTex);
	ReleaseCOM(chkDnTex);
	ReleaseCOM(theToolFont);
}

void UEE_ToolBar::Initialize(LPDIRECT3DDEVICE9 device,
		 MouseResource *mresource, uiWindow *desktop)
{
	D3DXCreateTextureFromFile(device, "art/gui/checkboxes/check_no.dds", &chkUpTex);
	D3DXCreateTextureFromFile(device, "art/gui/checkboxes/check_yes.dds", &chkDnTex);
	

	uiWindow* myWin = new uiWindow(false, device);
	myWin->SetWidth(256);
	myWin->SetHeight(256);
	myWin->SetXYPos(1000.0f, 200.0f);
	myWin->LoadCanvasFromFile("art/gui/windows/ue_tool_win.dds");
	myWin->SetDrag(true);
	desktop->AddChild(myWin);
	myWindow = myWin;

	uiWindow* tempWindow;
	tempWindow = new uiWindow(false, device);
	tempWindow->SetWidth(16);
	tempWindow->SetHeight(16);
	tempWindow->SetXYPos(40.0f, 32.0f);
	tempWindow->LoadCanvasFromFile("art/gui/blank.dds");
	tempWindow->SetDrag(false);
	myWindow->AddChild(tempWindow);

	//========================
	// move directional pad
	//========================

	uiButton* tempButton;
	tempButton = new UpButton(device);
	tempButton->SetWidth(16);
	tempButton->SetHeight(16);
	tempButton->SetXYPos(40.0f, 16.0f);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_upButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_upButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new DownButton(device);
	tempButton->SetWidth(16);
	tempButton->SetHeight(16);
	tempButton->SetXYPos(40.0f, 48.0f);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_downButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_downButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new LeftButton(device);
	tempButton->SetWidth(16);
	tempButton->SetHeight(16);
	tempButton->SetXYPos(24.0f, 32.0f);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_leftButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_leftButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new RightButton(device);
	tempButton->SetWidth(16);
	tempButton->SetHeight(16);
	tempButton->SetXYPos(56.0f, 32.0f);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_rightButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_rightButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	//=====================
	// font
	//=====================

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
	D3DXCreateFontIndirect(device, &fontDesc, &theToolFont);

	//=====================
	// axis & tool choice
	//=====================

	theAxis[0] = new XZCheckBox(device);
	theAxis[0]->SetWidth(16);
	theAxis[0]->SetHeight(16);
	theAxis[0]->SetXYPos(104.0f, 16.0f);
	theAxis[0]->LoadDefaultImg(chkUpTex);
	theAxis[0]->LoadCheckedImg(chkDnTex);
	theAxis[0]->SetCaption(":xz");
	theAxis[0]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theAxis[0]->SetCaptionFormat(DT_NOCLIP);
	theAxis[0]->SetCaptionFont(theToolFont);
	
	theAxis[1] = new XYCheckBox(device);
	theAxis[1]->SetWidth(16);
	theAxis[1]->SetHeight(16);
	theAxis[1]->SetXYPos(104.0f, 32.0f);
	theAxis[1]->LoadDefaultImg(chkUpTex);
	theAxis[1]->LoadCheckedImg(chkDnTex);
	theAxis[1]->SetCaption(":xy");
	theAxis[1]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theAxis[1]->SetCaptionFormat(DT_NOCLIP);
	theAxis[1]->SetCaptionFont(theToolFont);

	theAxis[2] = new YZCheckBox(device);
	theAxis[2]->SetWidth(16);
	theAxis[2]->SetHeight(16);
	theAxis[2]->SetXYPos(104.0f, 48.0f);
	theAxis[2]->LoadDefaultImg(chkUpTex);
	theAxis[2]->LoadCheckedImg(chkDnTex);
	theAxis[2]->SetCaption(":yz");
	theAxis[2]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theAxis[2]->SetCaptionFormat(DT_NOCLIP);
	theAxis[2]->SetCaptionFont(theToolFont);

	theTool[0] = new MoveToolCheckBox(device);
	theTool[0]->SetWidth(16);
	theTool[0]->SetHeight(16);
	theTool[0]->SetXYPos(174.0f, 16.0f);
	theTool[0]->LoadDefaultImg(chkUpTex);
	theTool[0]->LoadCheckedImg(chkDnTex);
	theTool[0]->SetCaption(":move");
	theTool[0]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theTool[0]->SetCaptionFormat(DT_NOCLIP);
	theTool[0]->SetCaptionFont(theToolFont);

	theTool[1] = new ScaleToolCheckBox(device);
	theTool[1]->SetWidth(16);
	theTool[1]->SetHeight(16);
	theTool[1]->SetXYPos(174.0f, 32.0f);
	theTool[1]->LoadDefaultImg(chkUpTex);
	theTool[1]->LoadCheckedImg(chkDnTex);
	theTool[1]->SetCaption(":scale");
	theTool[1]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theTool[1]->SetCaptionFormat(DT_NOCLIP);
	theTool[1]->SetCaptionFont(theToolFont);

	theTool[2] = new RotateToolCheckBox(device);
	theTool[2]->SetWidth(16);
	theTool[2]->SetHeight(16);
	theTool[2]->SetXYPos(174.0f, 48.0f);
	theTool[2]->LoadDefaultImg(chkUpTex);
	theTool[2]->LoadCheckedImg(chkDnTex);
	theTool[2]->SetCaption(":rotate");
	theTool[2]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theTool[2]->SetCaptionFormat(DT_NOCLIP);
	theTool[2]->SetCaptionFont(theToolFont);

	for(int i = 0; i < 3; i++)
	{
		theMsgSendingControls.push_back(theAxis[i]);
		theMsgSendingControls.push_back(theTool[i]);
		myWindow->AddChild(theAxis[i]);
		myWindow->AddChild(theTool[i]);
	}

	SetTool(MOVE_TOOL);
	SetAxis(0);

	//==========================
	//  uniform scale button
	//==========================

	uiCheckBox* tempCB = new UniformScaleButton(device);
	tempCB->SetHeight(16);
	tempCB->SetWidth(64);
	tempCB->SetXYPos(170.0f, 76.0f);
	tempCB->LoadDefaultImgFromFile("art/gui/buttons/ue_uniformButton_up.dds");
	tempCB->LoadCheckedImgFromFile("art/gui/buttons/ue_uniformButton_down.dds");
	tempCB->SetCaption("");
	myWindow->AddChild(tempCB);
	theMsgSendingControls.push_back(tempCB);

	//==========================
	// amount to move controls
	//==========================

	tempWindow = new MoveAmtWindow(false, device);
	tempWindow->SetHeight(64);
	tempWindow->SetWidth(256);
	tempWindow->SetXYPos(0.0f, 98.0f);
	tempWindow->SetCanvas(NULL);
	tempWindow->SetDrag(false);
	myWindow->AddChild(tempWindow);

	theSpot[0] = new AmtSpot(device);
	theSpot[0]->SetWidth(16);
	theSpot[0]->SetHeight(16);
	theSpot[0]->SetXYPos(160.0f, 24.0f);
	theSpot[0]->LoadDefaultImg(chkUpTex);
	theSpot[0]->LoadCheckedImg(chkDnTex);
	theSpot[0]->SetCaption("");
	theSpot[0]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theSpot[0]->SetCaptionFormat(DT_NOCLIP);
	theSpot[0]->SetCaptionFont(theToolFont);

	theSpot[1] = new AmtSpot(device);
	theSpot[1]->SetWidth(16);
	theSpot[1]->SetHeight(16);
	theSpot[1]->SetXYPos(180.0f, 24.0f);
	theSpot[1]->LoadDefaultImg(chkUpTex);
	theSpot[1]->LoadCheckedImg(chkDnTex);
	theSpot[1]->SetCaption("");
	theSpot[1]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theSpot[1]->SetCaptionFormat(DT_NOCLIP);
	theSpot[1]->SetCaptionFont(theToolFont);

	theSpot[2] = new AmtSpot(device);
	theSpot[2]->SetWidth(16);
	theSpot[2]->SetHeight(16);
	theSpot[2]->SetXYPos(200.0f, 24.0f);
	theSpot[2]->LoadDefaultImg(chkUpTex);
	theSpot[2]->LoadCheckedImg(chkDnTex);
	theSpot[2]->SetCaption("");
	theSpot[2]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theSpot[2]->SetCaptionFormat(DT_NOCLIP);
	theSpot[2]->SetCaptionFont(theToolFont);

	theSpot[3] = new AmtSpot(device);
	theSpot[3]->SetWidth(16);
	theSpot[3]->SetHeight(16);
	theSpot[3]->SetXYPos(220.0f, 24.0f);
	theSpot[3]->LoadDefaultImg(chkUpTex);
	theSpot[3]->LoadCheckedImg(chkDnTex);
	theSpot[3]->SetCaption("");
	theSpot[3]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	theSpot[3]->SetCaptionFormat(DT_NOCLIP);
	theSpot[3]->SetCaptionFont(theToolFont);

	for(int i = 0; i < 4; i++)
	{
		theSpot[i]->SetSpot(i);
		theSpot[i]->SetAmt(0);
		theMsgSendingControls.push_back(theSpot[i]);
		tempWindow->AddChild(theSpot[i]);
	}
	theSpot[1]->SetAmt(1);

	uiLabel* tempLbl = new uiLabel(device);
	tempLbl->SetHeight(32);
	tempLbl->SetWidth(128);
	tempLbl->SetXYPos(16.0f, 24.0f);
	tempLbl->SetCaption("amt to move:");
	tempLbl->SetFont(theToolFont);
	tempLbl->SetFormat(DT_NOCLIP);
	tempLbl->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	tempWindow->AddChild(tempLbl);
	
	theAmtLbl = new AmtLabel(device);
	theAmtLbl->SetHeight(32);
	theAmtLbl->SetWidth(128);
	theAmtLbl->SetXYPos(108.0f, 24.0f);
	theAmtLbl->SetCaption("01.00");
	theAmtLbl->SetFont(theToolFont);
	theAmtLbl->SetFormat(DT_NOCLIP);
	theAmtLbl->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	tempWindow->AddChild(theAmtLbl);

	tempButton = new ClearAmtButton(device);
	tempButton->SetHeight(16);
	tempButton->SetWidth(64);
	tempButton->SetXYPos(20.0f, 44.0f);
	tempButton->SetCaption("");
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_resetAmtButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_resetAmtButton_down.dds");
	tempWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	theAmtAddBtn = new AddToAmt(device);
	theAmtAddBtn->SetHeight(16);
	theAmtAddBtn->SetWidth(16);
	theAmtAddBtn->SetXYPos(160.0f, 8.0f);
	theAmtAddBtn->SetCaption("");
	theAmtAddBtn->LoadDefaultImgFromFile("art/gui/buttons/ue_upButton_up.dds");
	theAmtAddBtn->LoadPressedImgFromFile("art/gui/buttons/ue_upButton_down.dds");
	tempWindow->AddChild(theAmtAddBtn);
	theMsgSendingControls.push_back(theAmtAddBtn);

	theAmtRemBtn = new RemoveAmt(device);
	theAmtRemBtn->SetHeight(16);
	theAmtRemBtn->SetWidth(16);
	theAmtRemBtn->SetXYPos(160.0f, 40.0f);
	theAmtRemBtn->SetCaption("");
	theAmtRemBtn->LoadDefaultImgFromFile("art/gui/buttons/ue_downButton_up.dds");
	theAmtRemBtn->LoadPressedImgFromFile("art/gui/buttons/ue_downButton_down.dds");
	tempWindow->AddChild(theAmtRemBtn);
	theMsgSendingControls.push_back(theAmtRemBtn);

	theCurrentSpot = 0;
	SetSpot();

	//==========================
	// add/remove asset buttons
	//==========================

	tempButton = new AddAssetButton(device);
	tempButton->SetHeight(16);
	tempButton->SetWidth(32);
	tempButton->SetXYPos(32.0f, 208.0f);
	tempButton->SetCaption("");
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_addButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_addButton_down.dds");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new RemoveAssetButton(device);
	tempButton->SetHeight(16);
	tempButton->SetWidth(32);
	tempButton->SetXYPos(32.0f, 232.0f);
	tempButton->SetCaption("");
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_remButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_remButton_down.dds");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	//=============================
	//   asset preview controls
	//=============================

	tempButton = new NextAssetButton(device);
	tempButton->SetHeight(16);
	tempButton->SetWidth(16);
	tempButton->SetXYPos(50.0f, 184.0f);
	tempButton->SetCaption("");
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_rightButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_rightButton_down.dds");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new PrevAssetButton(device);
	tempButton->SetHeight(16);
	tempButton->SetWidth(16);
	tempButton->SetXYPos(30.0f, 184.0f);
	tempButton->SetCaption("");
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_leftButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_leftButton_down.dds");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	thePreviewWindow = new AssetPreviewWindow(false, device);
	thePreviewWindow->SetWidth(128);
	thePreviewWindow->SetHeight(64);
	thePreviewWindow->SetXYPos(96.0f, 184.0f);
	thePreviewWindow->LoadAllTextures();
	myWindow->AddChild(thePreviewWindow);

	thePreviewLabel = new uiLabel(device);
	thePreviewLabel->SetWidth(128);
	thePreviewLabel->SetHeight(32);
	thePreviewLabel->SetXYPos(96.0f, 164.0f);
	thePreviewLabel->SetCaption("");
	thePreviewLabel->SetFont(theToolFont);
	thePreviewLabel->SetFormat(DT_NOCLIP);
	thePreviewLabel->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	myWindow->AddChild(thePreviewLabel);

}

void UEE_ToolBar::OnLost()
{
	theToolFont->OnLostDevice();
}

void UEE_ToolBar::OnReset()
{
	theToolFont->OnResetDevice();
}

void UEE_ToolBar::SetTool(ToolType tool)
{
	switch(tool)
	{
	case MOVE_TOOL:
		theTool[0]->SetChecked(true);
		theTool[1]->SetChecked(false);
		theTool[2]->SetChecked(false);
		break;
	case SCALE_TOOL:
		theTool[0]->SetChecked(false);
		theTool[1]->SetChecked(true);
		theTool[2]->SetChecked(false);
		break;
	case ROTATE_TOOL:
		theTool[0]->SetChecked(false);
		theTool[1]->SetChecked(false);
		theTool[2]->SetChecked(true);
		break;
	default:
		theTool[0]->SetChecked(true);
		theTool[1]->SetChecked(false);
		theTool[2]->SetChecked(false);
		break;
	};
}

void UEE_ToolBar::SetAxis(int axis)
{
	switch(axis)
	{
	case 0:
		theAxis[0]->SetChecked(true);
		theAxis[1]->SetChecked(false);
		theAxis[2]->SetChecked(false);
		break;
	case 1:
		theAxis[0]->SetChecked(false);
		theAxis[1]->SetChecked(true);
		theAxis[2]->SetChecked(false);
		break;
	case 2:
		theAxis[0]->SetChecked(false);
		theAxis[1]->SetChecked(false);
		theAxis[2]->SetChecked(true);
		break;
	default:
		theAxis[0]->SetChecked(true);
		theAxis[1]->SetChecked(false);
		theAxis[2]->SetChecked(false);
		break;
	};
}

int UEE_ToolBar::GetSpot()
{
	for(int i = 0; i < 4; i++)
	{
		if(theSpot[i]->IsChecked() && i != theCurrentSpot)
		{
			return theCurrentSpot = i;
		}
	}

	return theCurrentSpot = 0;
}

void UEE_ToolBar::SetSpot()
{
	switch(GetSpot())
	{
	case 0:
		theSpot[0]->SetChecked(true);
		theSpot[1]->SetChecked(false);
		theSpot[2]->SetChecked(false);
		theSpot[3]->SetChecked(false);
		break;
	case 1:
		theSpot[0]->SetChecked(false);
		theSpot[1]->SetChecked(true);
		theSpot[2]->SetChecked(false);
		theSpot[3]->SetChecked(false);
		break;
	case 2:
		theSpot[0]->SetChecked(false);
		theSpot[1]->SetChecked(false);
		theSpot[2]->SetChecked(true);
		theSpot[3]->SetChecked(false);
		break;
	case 3:
		theSpot[0]->SetChecked(false);
		theSpot[1]->SetChecked(false);
		theSpot[2]->SetChecked(false);
		theSpot[3]->SetChecked(true);
		break;
	default:
		theSpot[0]->SetChecked(true);
		theSpot[1]->SetChecked(false);
		theSpot[2]->SetChecked(false);
		theSpot[3]->SetChecked(false);
		break;
	};

	theAmtAddBtn->SetXPos(20.0f * theCurrentSpot + 160.0f);
	theAmtRemBtn->SetXPos(20.0f * theCurrentSpot + 160.0f);
}

void UEE_ToolBar::AddSpot()
{
	theSpot[theCurrentSpot]->AddAmt();
}

void UEE_ToolBar::RemSpot()
{
	theSpot[theCurrentSpot]->RemAmt();
}

float UEE_ToolBar::GetAmt()
{
	int temp = 0;
	for(int i = 0; i < 4; i++)
	{
		temp += theSpot[i]->GetAmt();
		temp *= 10;
	}
	
	float f = temp/1000.0f;
	
	char str[10];
	sprintf_s(str, "%.2f", f);
	theAmtLbl->SetCaption(str);

	return f;
}

void UEE_ToolBar::ClearAmt()
{
	for(int i = 0; i < 4; i++)
		theSpot[i]->SetAmt(0);
}

void UEE_ToolBar::SetPreviewLabel()
{
	switch(thePreviewWindow->GetPropType())
	{
	case PROP_ROCK01:
		thePreviewLabel->SetCaption("prop: rock01");
		break;

	case PROP_ROCK02:
		thePreviewLabel->SetCaption("prop: rock02");
		break;

	case PROP_ROCK03:
		thePreviewLabel->SetCaption("prop: rock03");
		break;

	case PROP_TOMBSTONE01:
		thePreviewLabel->SetCaption("prop: tombstone01");
		break;

	case PROP_TOMBSTONE02:
		thePreviewLabel->SetCaption("prop: tombstone02");
		break;

	case PROP_FENCE:
		thePreviewLabel->SetCaption("prop: fence");
		break;

	case PROP_GATE:
		thePreviewLabel->SetCaption("prop: gate");
		break;

	case PROP_DESTROYED_WALL_01:
		thePreviewLabel->SetCaption("prop: destroyed wall");
		break;

	case PROP_PIPE_STRAIGHT:
		thePreviewLabel->SetCaption("prop: straight pipe");
		break;

	case PROP_PIPE_ELBOW:
		thePreviewLabel->SetCaption("prop: elbow pipe");
		break;

	case PROP_PIPE_CROSS:
		thePreviewLabel->SetCaption("prop: cross pipe");
		break;

	case UNIT_SP_GROUND:
		thePreviewLabel->SetCaption("unit: ground unit");
		break;

	case BUILDING_SP_BASE:
		thePreviewLabel->SetCaption("unit: sp base");
		break;

	case UNIT_Z_GROUND:
		thePreviewLabel->SetCaption("unit: z ground unit");
		break;

	case BUILDING_Z_BASE:
		thePreviewLabel->SetCaption("unit: z base");
		break;

	//case BUILDING_UPGRAYEDD:
	//	thePreviewLabel->SetCaption("unit: sp upgrayedd");
	//	break;

	//case BUILDING_GUNIT:
	//	thePreviewLabel->SetCaption("unit: gunit building");
	//	break;

	case BUILDING_COAL_MINE:
		thePreviewLabel->SetCaption("resource: coal mine");
		break;

	case BUILDING_GRAVEYARD:
		thePreviewLabel->SetCaption("resource: graveyard");
		break;

	default:
		thePreviewLabel->SetCaption("invalid asset");
		break;
	};
}
