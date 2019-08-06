#include "ueeTopMenu.h"

void NewButton::DoStuff()
{
	theMessageToSend = UIMT_NEW_GAME;
}

void SaveButton::DoStuff()
{
	theMessageToSend = UIMT_SAVE_GAME;
}

void SaveNav::DoStuff()
{
	theMessageToSend = UIMT_SAVE_WITH_NAV;
}

void LoadButton::DoStuff()
{
	theMessageToSend = UIMT_LOAD_GAME;
}

void ClearButton::DoStuff()
{
	theMessageToSend = UIMT_CLEAR_SCENE;
}

void QuitButton::DoStuff()
{
	//theMessageToSend = UIMT_QUIT_GAME;
}

void FullScreenButton::DoStuff()
{
	theMessageToSend = UIMT_FULLSCREEN;
}

void MainCamCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_CAM_NORMAL;
}

void CamXZCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_CAM_XZ;
}

void CamXYCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_CAM_XY;
}

void CamYZCheckBox::DoStuff()
{
	if(!IsChecked())
		theMessageToSend = UIMT_CAM_YZ;
}

void CamToggleLookCheckBox::DoStuff()
{
	theMessageToSend = UIMT_CAM_FLIP;
}

UEE_TopMenu::UEE_TopMenu()
{
	SetType(M_TOPMENU);
}

UEE_TopMenu::~UEE_TopMenu()
{
	ReleaseCOM(chkUp);
	ReleaseCOM(chkDn);
	theMsgSendingControls.clear();
	ReleaseCOM(theMenuFont);
}

void UEE_TopMenu::Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop)
{
	D3DXCreateTextureFromFile(device, "art/gui/checkboxes/check_no.dds", &chkUp);
	D3DXCreateTextureFromFile(device, "art/gui/checkboxes/check_yes.dds", &chkDn);

	theDesktop = desktop;

	uiWindow* myWin = new uiWindow(false, device);
	myWin->SetWidth(1024);
	myWin->SetHeight(128);
	myWin->SetXYPos(0.0f, 0.0f);
	myWin->LoadCanvasFromFile("art/gui/windows/ue_win.dds");
	myWin->SetDrag(false);
	theDesktop->AddChild(myWin);
	myWindow = myWin;


	uiButton* tempButton = new QuitButton(device);
	tempButton->SetXYPos(256.0f, 8.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_quitButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_quitButton_down.dds");
	tempButton->SetCaption("");
	tempButton->SetMyMessage(UIMT_QUIT_GAME);
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new FullScreenButton(device);
	tempButton->SetXYPos(328.0f, 8.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_fsButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_fsButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new NewButton(device);
	tempButton->SetXYPos(878.0f, 8.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_newButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_newButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new SaveButton(device);
	tempButton->SetXYPos(950.0f, 8.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_saveButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_saveButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new LoadButton(device);
	tempButton->SetXYPos(950.0f, 48.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_loadButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_loadButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	tempButton = new ClearButton(device);
	tempButton->SetXYPos(878.0f, 48.0f);
	tempButton->SetWidth(64);
	tempButton->SetHeight(32);
	tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_clearButton_up.dds");
	tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_clearButton_down.dds");
	tempButton->SetCaption("");
	myWindow->AddChild(tempButton);
	theMsgSendingControls.push_back(tempButton);

	//tempButton = new SaveNav(device);
	//tempButton->SetXYPos(882.0f, 98.0f);
	//tempButton->SetWidth(128);
	//tempButton->SetHeight(16);
	//tempButton->LoadDefaultImgFromFile("art/gui/buttons/ue_savewButton_up.dds");
	//tempButton->LoadPressedImgFromFile("art/gui/buttons/ue_savewButton_down.dds");
	//tempButton->SetCaption("");
	//myWindow->AddChild(tempButton);
	//theMsgSendingControls.push_back(tempButton);

	//font
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
	D3DXCreateFontIndirect(device, &fontDesc, &theMenuFont);
	//end font

	uiCheckBox* tempCB;
	theCam[0] = new CamXZCheckBox(device);
	theCam[1] = new CamXYCheckBox(device);
	theCam[2] = new CamYZCheckBox(device);
	theCam[3] = new MainCamCheckBox(device);

	for(int i = 0; i < 4; i++)
	{
		theCam[i]->SetXYPos(780.0f, 8.0f + (i+1)*24.0f);

		theCam[i]->SetWidth(16);
		theCam[i]->SetHeight(16);
		theCam[i]->LoadDefaultImg(chkUp);
		theCam[i]->LoadCheckedImg(chkDn);
		theCam[i]->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
		
		theCam[i]->SetCaptionFormat(DT_NOCLIP);
		theCam[i]->SetCaptionFont(theMenuFont);

		theMsgSendingControls.push_back(theCam[i]);
		myWindow->AddChild(theCam[i]);
	}

	theCam[0]->SetCaption(":xz");
	theCam[1]->SetCaption(":xy");
	theCam[2]->SetCaption(":yz");
	theCam[3]->SetCaption(":rts");
	
	SetCam(3);

	tempCB = new CamToggleLookCheckBox(device);
	tempCB->SetXYPos(780.0f, 8.0f);
	tempCB->SetWidth(16);
	tempCB->SetHeight(16);
	tempCB->LoadDefaultImg(chkUp);
	tempCB->LoadCheckedImg(chkDn);
	tempCB->SetCaption("<-flip cam");
	tempCB->SetCaptionColor(D3DCOLOR_XRGB(250, 250, 250));
	tempCB->SetCaptionFormat(DT_NOCLIP);
	tempCB->SetCaptionFont(theMenuFont);
	tempCB->SetChecked(false);
	theMsgSendingControls.push_back(tempCB);
	myWindow->AddChild(tempCB);

	uiLabel* tempLbl = new uiLabel(device);
	tempLbl->SetHeight(128);
	tempLbl->SetWidth(128);
	tempLbl->SetXYPos(640.0f, 8.0f);
	tempLbl->SetFont(theMenuFont);
	tempLbl->SetFormat(DT_NOCLIP);
	tempLbl->SetColor(D3DCOLOR_XRGB(250, 250, 250));
	std::string str = " camera controls:\n";
	str += " w: up     s: down\n a: left";
	str += "     d: right\n     q: zoom+\n     e: zoom-";
	str += "\n r_mb: change-\n     -perspective";
	tempLbl->SetCaption(str);
	myWindow->AddChild(tempLbl);

}

void UEE_TopMenu::OnLost()
{
	theMenuFont->OnLostDevice();
}

void UEE_TopMenu::OnReset()
{
	theMenuFont->OnResetDevice();
}

void UEE_TopMenu::SetCam(int cam)
{
	switch(cam)
	{
	case 0:
		theCam[0]->SetChecked(true);
		theCam[1]->SetChecked(false);
		theCam[2]->SetChecked(false);
		theCam[3]->SetChecked(false);
		break;
	case 1:
		theCam[0]->SetChecked(false);
		theCam[1]->SetChecked(true);
		theCam[2]->SetChecked(false);
		theCam[3]->SetChecked(false);
		break;
	case 2:
		theCam[0]->SetChecked(false);
		theCam[1]->SetChecked(false);
		theCam[2]->SetChecked(true);
		theCam[3]->SetChecked(false);
		break;
	case 3:
		theCam[0]->SetChecked(false);
		theCam[1]->SetChecked(false);
		theCam[2]->SetChecked(false);
		theCam[3]->SetChecked(true);
		break;
	default:
		theCam[0]->SetChecked(false);
		theCam[1]->SetChecked(false);
		theCam[2]->SetChecked(false);
		theCam[3]->SetChecked(true);
		break;
	};
}