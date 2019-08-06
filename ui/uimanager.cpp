#include "uimanager.h"
#include "dxSprite.h"
#include "base_controls/uiControl.h"
#include "base_controls/uiWindow.h"
#include "base_controls/uiButton.h"
#include "base_controls/uiLabel.h"
#include "base_controls/uiCheckBox.h"
#include "ueeTopMenu.h"
#include "ueeToolBar.h"
#include "ueeUtilBar.h"
#include "ueeStatusBar.h"
#include "../CShader.h"
#include "../appStats.h"
#include "../prop.h"
#include "../prop_mgr.h"
#include "../dxCamera.h"
#include "../EntityResource.h"
#include "../serial/Deserializer.h"
#include "../serial/Serializer.h"
#include "../serial/BinarySerialSize.h"
#include "../serial/BinarySerializer.h"
#include "../serial/BinaryDeserializer.h"
#include "../NavGraph.h"

GuiMgr::GuiMgr()
{
	theAppStats      = new AppStats();
	theDevice		 = NULL;
	theSpot			 = 0;
	theCurrentTool   = MOVE_TOOL;
	theCurrentPicker = PICK_PROP;
	currentID        = -1;
	theRotAxis       = YAXIS;
	intAxis          = 0;
	theCurrentCam	 = 3;
	theCamera->setFree(true);
	amtToMove		 = 1.0f;
	isFullScreen	 = false;
	isUniformScale   = false;
	er_vec.clear();
}

GuiMgr::~GuiMgr()
{

	theMsgSendingControls.clear();
	UnloadShaders();
	SAFE_DELETE(theToolBar);
	SAFE_DELETE(theUtilBar);
	SAFE_DELETE(theTopMenu);
	SAFE_DELETE(theStatusBar);
	theManagers.clear();

	delete theAppStats;
	delete theDesktop;
}

void GuiMgr::Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop)
{
	SetType(M_PARENT);
	theDevice = device;
	theMouse  = mresource;
	theSpritePen->BuildSpritePen(device);

	BuildShaders();

	theDesktop = new uiWindow(true, device);
	theDesktop->SetWidth(1280);
	theDesktop->SetHeight(800);
	theDesktop->SetXYPos(0.0f, 0.0f);
	theDesktop->SetDrag(false);

	MakeManager(M_TOPMENU);
	MakeManager(M_UTILBAR);
	MakeManager(M_TOOLBAR);
	MakeManager(M_STATUSBAR);

	theToolBar->thePreviewWindow->SetAssetType(ASSET_PROP);
	theToolBar->SetPreviewLabel();

	SetCurrentID(-1);
	thePropMgr->RemoveAllProps();
	hasKilled = true;
}

void GuiMgr::Draw()
{
	theSpritePen->Begin();
	theSpritePen->SetAlphaBlend(true);
	theDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	theDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	theSpritePen->SetAlphaTest(true);

	theDesktop->DrawChildren();

	theSpritePen->Flush();
	theSpritePen->SetAlphaBlend(false);
	theSpritePen->SetAlphaTest(false);
	theSpritePen->End();
}

void GuiMgr::OnLost()
{
	theSpritePen->OnLost();
	//theStatusFont->OnLostDevice();
	theAppStats->onLostDevice();

	for(ManagerMap::iterator it = theManagers.begin();
		it != theManagers.end(); ++it)
	{
		it->second->OnLost();
	}

	for(int i = 0; i < 3; i++)
		theShaders[i]->OnLost();
}

void GuiMgr::OnReset()
{
	theSpritePen->OnReset();
	//theStatusFont->OnResetDevice();
	theAppStats->onResetDevice();

	for(ManagerMap::iterator it = theManagers.begin();
		it != theManagers.end(); ++it)
	{
		it->second->OnReset();
	}

	for(int i = 0; i < 3; i++)
		theShaders[i]->OnReset();
}

void GuiMgr::Update(float dt)
{
	theAppStats->update(dt);

	UserInterfaceMessageType msg;

	if(GetUIMessage(msg))
	{
		switch(msg)
		{

		case UIMT_PICK_PROP:
			if(theCurrentPicker != PICK_PROP)
				theUtilBar->SetPicker(PICK_PROP);
			theCurrentPicker = PICK_PROP;
			break;

		case UIMT_PICK_UNIT:
			if(theCurrentPicker != PICK_UNIT)
				theUtilBar->SetPicker(PICK_UNIT);
			theCurrentPicker = PICK_UNIT;
			break;

		case UIMT_PICK_TILE:
			if(theCurrentPicker != PICK_TILE)
				theUtilBar->SetPicker(PICK_TILE);
			theCurrentPicker = PICK_TILE;
			break;

		case UIMT_ASSET_PROP:
			if(theCurrentAssetType != ASSET_PROP)
				theUtilBar->SetAssetType(0);
			theCurrentAssetType = ASSET_PROP;
			theToolBar->thePreviewWindow->SetAssetType(ASSET_PROP);
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();
			theToolBar->SetPreviewLabel();
			break;

		case UIMT_ASSET_UNIT:
			if(theCurrentAssetType != ASSET_UNIT)
				theUtilBar->SetAssetType(1);
			theCurrentAssetType = ASSET_UNIT;
			theToolBar->thePreviewWindow->SetAssetType(ASSET_UNIT);
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();	
			theToolBar->SetPreviewLabel();
			break;

		case UIMT_ASSET_RESOURCE:
			if(theCurrentAssetType != ASSET_RESOURCE)
				theUtilBar->SetAssetType(2);
			theCurrentAssetType = ASSET_RESOURCE;
			theToolBar->thePreviewWindow->SetAssetType(ASSET_RESOURCE);
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();
			theToolBar->SetPreviewLabel();
			break;

		case UIMT_NEXT_ASSET:
			theToolBar->thePreviewWindow->Next();
			theToolBar->SetPreviewLabel();
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();
			break;

		case UIMT_PREV_ASSET:
			theToolBar->thePreviewWindow->Prev();
			theToolBar->SetPreviewLabel();
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();
			break;

		case UIMT_CAM_NORMAL:
			if(theCurrentCam != 3)
			{
				theCurrentCam = 3;
				theTopMenu->SetCam(3);
				theCamera->setCamera(1);
				theCamera->setFree(true);
			}
			break;

		case UIMT_CAM_XZ:
			if(theCurrentCam != 0)
			{
				theCurrentCam = 0;
				theTopMenu->SetCam(0);
				theCamera->setCamera(2);
				theCamera->setFree(false);
			}
			break;

		case UIMT_CAM_XY:
			if(theCurrentCam != 1)
			{
				theCurrentCam = 1;
				theTopMenu->SetCam(1);
				theCamera->setCamera(3);
				theCamera->setFree(false);
			}
			break;

		case UIMT_CAM_YZ:
			if(theCurrentCam != 2)
			{
				theCurrentCam = 2;
				theTopMenu->SetCam(2);
				theCamera->setCamera(4);
				theCamera->setFree(false);
			}
			break;

		case UIMT_CAM_FLIP:
			theCamera->flipLook();
			break;

		case UIMT_HIDE_TOOL:
			RemoveManager(M_TOOLBAR);
			break;

		case UIMT_SHOW_TOOL:
			MakeManager(M_TOOLBAR);
			break;

		case UIMT_QUIT_GAME:
			theApp->enableFullScreen(false);
			Sleep(200);
			thePropMgr->RemoveAllProps();
			PostQuitMessage(0);
			break;

		case UIMT_FULLSCREEN:
			isFullScreen = !isFullScreen;
			theApp->enableFullScreen(isFullScreen);

		case UIMT_XZ_AXIS:
			if(theRotAxis != YAXIS)
				SetAxis(0);
			break;

		case UIMT_XY_AXIS:
			if(theRotAxis != ZAXIS)
				SetAxis(1);
			break;

		case UIMT_YZ_AXIS:
			if(theRotAxis != XAXIS)
				SetAxis(2);
			break;

		case UIMT_MOVE_TOOL:
			if(theCurrentTool != MOVE_TOOL)
				SetTool(MOVE_TOOL);
			break;

		case UIMT_SCALE_TOOL:
			if(theCurrentTool != SCALE_TOOL)	
				SetTool(SCALE_TOOL);
			break;

		case UIMT_SCALE_UNIFORM:
			isUniformScale = !isUniformScale;
			break;

		case UIMT_ROTATE_TOOL:
			if(theCurrentTool != ROTATE_TOOL)
				SetTool(ROTATE_TOOL);
			break;

		case UIMT_CHANGE_SPOT:
			theToolBar->SetSpot();
			amtToMove = theToolBar->GetAmt();
			break;

		case UIMT_ADD_AMT:
			theToolBar->AddSpot();
			amtToMove = theToolBar->GetAmt();
			break;

		case UIMT_REM_AMT:
			theToolBar->RemSpot();
			amtToMove = theToolBar->GetAmt();
			break;

		case UIMT_CLR_AMT:
			theToolBar->ClearAmt();
			amtToMove = theToolBar->GetAmt();
			break;

		case UIMT_UP_TOOL:
			DoToolAction(0);
			break;

		case UIMT_DOWN_TOOL:
			DoToolAction(1);
			break;

		case UIMT_LEFT_TOOL:
			DoToolAction(2);
			break;

		case UIMT_RIGHT_TOOL:
			DoToolAction(3);
			break;

		case UIMT_ADD_ASSET:
			theCurrentPropType = theToolBar->thePreviewWindow->GetPropType();
			AddProp();
			hasKilled = false;
			break;

		case UIMT_REMOVE_ASSET:
			RemoveProp();
			break;

		case UIMT_SAVE_GAME:
			Save();
			break;

		case UIMT_SAVE_WITH_NAV:
			SaveWithNavGraph();
			break;

		case UIMT_LOAD_GAME:
			Load();
			break;

		case UIMT_NEW_GAME:
			MakeNew();
			break;

		case UIMT_CLEAR_SCENE:
			SetCurrentID(-1);
			thePropMgr->RemoveAllProps();
			hasKilled = true;
			break;

		default:
			break;
		};
	}
	else
	{
		if(shouldPick)
		{
			DoPicking();
			shouldPick = false;
		}
	}


	if(currentID == -1)
	{
		theStatusBar->SetStatus(theAppStats->getFPS(), NULL);
	}
	else
	{
		theStatusBar->SetStatus(theAppStats->getFPS(), thePropMgr->GetProp(currentID));
	}
}

void GuiMgr::SendToGui(GraphicsCoreMessageType msg, void* data)
{
	shouldPick = !theDesktop->GiveToAll(msg, theMouse, data) && msg == GCMT_LBUTTONUP ? true : false;
}

bool GuiMgr::GetUIMessage(UserInterfaceMessageType &re_msg)
{
	for(ManagerMap::iterator it = theManagers.begin();
		it != theManagers.end(); ++it)
	{
		if(it->second->ResponseFromUI(re_msg))
		return true;
	}
	return false;
}

bool GuiMgr::ShowToolBar()
{
	return showTools;
}

void GuiMgr::SetToolBar(bool tools)
{
	showTools = tools;
}

void GuiMgr::AddManager(ManagerBase *mgr)
{	
	theManagers.insert(std::make_pair(mgr->GetType(), mgr));
}

void GuiMgr::RemoveManager(ManagerType type)
{
	theDesktop->RemoveChild(theManagers.find(type)->second->GetMyWindow());
	theManagers.erase(theManagers.find(type));
	SetNULL(type);
}

ManagerBase* GuiMgr::GetManager(ManagerType type)
{
	switch(type)
	{
	case M_TOOLBAR:
		return theToolBar;

	case M_TOPMENU:
		return theTopMenu;
	
	case M_UTILBAR:
		return theUtilBar;

	case M_STATUSBAR:
		return theStatusBar;

	default:
		break;
	};
	return NULL;
}

void GuiMgr::MakeManager(ManagerType type)
{

	switch(type)
	{
	case M_TOPMENU:
		theTopMenu = new UEE_TopMenu();
		theTopMenu->Initialize(theDevice, theMouse, theDesktop);
		theTopMenu->SetParentMgr(this);
		AddManager(theTopMenu);
		break;

	case M_TOOLBAR:
		theToolBar = new UEE_ToolBar();
		theToolBar->Initialize(theDevice, theMouse, theDesktop);
		theToolBar->SetParentMgr(this);
		AddManager(theToolBar);
		break;

	case M_UTILBAR:
		theUtilBar = new UEE_UtilBar();
		theUtilBar->Initialize(theDevice, theMouse, theDesktop);
		theUtilBar->SetParentMgr(this);
		AddManager(theUtilBar);
		break;

	case M_STATUSBAR:
		theStatusBar = new UEE_StatusBar();
		theStatusBar->Initialize(theDevice, theMouse, theDesktop);
		theStatusBar->SetParentMgr(this);
		AddManager(theStatusBar);
		break;

	default:
		break;
	};
}

void GuiMgr::SetNULL(ManagerType type)
{
	switch(type)
	{
	case M_TOOLBAR:
		theToolBar = NULL;
		break;
		
	case M_TOPMENU:
		theTopMenu = NULL;
		break;

	case M_UTILBAR:
		theUtilBar = NULL;
		break;

	case M_STATUSBAR:
		theStatusBar = NULL;
		break;

	default:
		return;
	};
}

void GuiMgr::SetTool(ToolType tool)
{
	theCurrentTool = tool;
	theToolBar->SetTool(tool);
}

void GuiMgr::SetAxis(int axis)
{
	theToolBar->SetAxis(axis);

	switch(axis)
	{
	case 0:
		theRotAxis = YAXIS;
		break;
	case 1:
		theRotAxis = ZAXIS;
		break;
	case 2:
		theRotAxis = XAXIS;
		break;
	default:
		theRotAxis = YAXIS;
		break;
	};

	intAxis = axis;
}

void GuiMgr::DoPicking()
{
	D3DXVECTOR3 orig(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
	thePropMgr->GetRay(orig, dir);

	int id = thePropMgr->GetIDFromRayIntersect(orig, dir);
	SetCurrentID(id);
}

void GuiMgr::SetCurrentID(int id)
{
	static int lastID = -1;
	currentID = id;

	if(id == -1)
	{
		if(lastID == -1) return;

		if(!hasKilled)
		{
			thePropMgr->ChangePropFX(lastID, *thePropMgr->GetDefaultFX());
		}
		hasKilled = false;
	}
	else if(id == lastID && lastID != -1)
	{
		thePropMgr->ChangePropFX(id, *thePropMgr->GetDefaultFX());
		currentID = -1;
	}
	else if(id != lastID)
	{
		if(!hasKilled)
			thePropMgr->ChangePropFX(lastID, *thePropMgr->GetDefaultFX());
		
		thePropMgr->ChangePropFX(id, *thePropMgr->GetSelectFX());
		hasKilled = false;
	}

	lastID = currentID;
}

void GuiMgr::DoToolAction(int dir)
{
	if(currentID == -1) return;

	DoMove(theCurrentTool, MoveAboutAxis(intAxis, dir));
	theStatusBar->AddToCount(); //stats
}

D3DXVECTOR3 GuiMgr::MoveAboutAxis(int axis, int dir)
{
	if(theCurrentTool == ROTATE_TOOL)
	{
		if(dir == 0 || dir == 3)
			return theRotAxis * D3DXToRadian(amtToMove);
		else
			return theRotAxis * D3DXToRadian(-amtToMove);
	}
	else if(theCurrentTool == SCALE_TOOL
			&& isUniformScale)
	{
		if(dir == 0 || dir == 3)
			return D3DXVECTOR3(1.0f, 1.0f, 1.0f) * amtToMove;
		else
			return D3DXVECTOR3(1.0f, 1.0f, 1.0f) * -amtToMove;
	}

	D3DXVECTOR3 temp;
	switch(axis)
	{
	case 0:
		if(dir == 0 || dir == 1)
		{
			temp = ZAXIS * amtToMove;
			if(dir == 1)
				temp *= -1;
		}
		else
		{
			temp = XAXIS * amtToMove;
			if(dir == 2)
				temp *= -1;
		}
		break;
	case 1:
		if(dir == 0 || dir == 1)
		{
			temp = YAXIS * amtToMove;
			if(dir == 1)
				temp *= -1;
		}
		else
		{
			temp = XAXIS * amtToMove;
			if(dir == 2)
				temp *= -1;
		}
		break;
	case 2:
		if(dir == 0 || dir == 1)
		{
			temp = YAXIS * amtToMove;
			if(dir == 1)
				temp *= -1;
		}
		else
		{
			temp = ZAXIS * amtToMove;
			if(dir == 2)
				temp *= -1;
		}
		break;
	default:
		temp = VEC3_ZERO;
		break;
	};

	return temp;
}

void GuiMgr::DoMove(ToolType type, D3DXVECTOR3 vec)
{
	Prop* p = thePropMgr->GetProp(currentID);

	switch(type)
	{
	case MOVE_TOOL:
		p->position += vec;
		break;
	case SCALE_TOOL:
		p->scale += vec;
		break;
	case ROTATE_TOOL:
		p->rotVec += vec;
		break;
	default:
		break;
	};

	p->toWorld = thePropMgr->MakeMatrix(p->position, p->scale, p->rotVec);
}

void GuiMgr::AddProp()
{
	if(theCurrentPropType == INVALID_PROP) return;

	//stats
	theStatusBar->AddToCount();

	int id = thePropMgr->GetNextID();
	D3DXVECTOR3 pos;
	if(currentID >= 0)
		pos = thePropMgr->GetProp(currentID)->position + D3DXVECTOR3(5.0f, 0.0f, 5.0f);
	else if(!hasKilled)
		pos = thePropMgr->GetProp(thePropMgr->GetLastID())->position + D3DXVECTOR3(5.0f, 0.0f, 5.0f); 
	else 
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if(theCurrentPropType == BUILDING_GRAVEYARD || theCurrentPropType == BUILDING_Z_BASE)
		pos.y = .25f;

	thePropMgr->AddProp(id, theCurrentPropType, pos, *thePropMgr->GetDefaultFX());

	//auto select newly added prop
	SetCurrentID(id);
}

void GuiMgr::RemoveProp()
{
	int id = currentID;
	SetCurrentID(-1);
	thePropMgr->RemoveProp(id);
	hasKilled = true;

	//stats
	theStatusBar->AddToCount();
}

void GuiMgr::Save()
{
	if(isFullScreen)
	{
		theApp->enableFullScreen(false);
		Sleep(500);
		isFullScreen = false;
	}

	OPENFILENAME ofn;
	TCHAR szTotalFileName[1024];
	memset(szTotalFileName, 0, sizeof(TCHAR)*1024);
	TCHAR szAbsDirectory[1024];
	memset(szAbsDirectory, 0, sizeof(TCHAR)*1024);
	TCHAR szFileName[1024];
	memset(szFileName, 0, sizeof(TCHAR)*1024);
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = theApp->getMainWindow();
	//ofn.lpstrInitialDir = _T("
	ofn.lpstrFilter = _T("unearthed level file (*.ue0)\0*.ue0\0binary file (*.bin)\0*bin\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szTotalFileName;
	ofn.nMaxFile = 10000;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_EXPLORER;
	ofn.lpstrDefExt = _T("ue0");

	//returns false if the user cancel/closes dialog
	if(!GetSaveFileName((LPOPENFILENAME)&ofn)) return;

	std::string str, str2;
	str = szTotalFileName;
	size_t pos;
	pos = str.rfind("\\");
	str2 = str.substr(pos+1);

	//for stats...
	theStatusBar->ResetCount();
	theStatusBar->SetFileName(str2);


	//do actual save here...
	EntityResource* er;
	int count = 0;
	//first turn props into ERs
	for(std::multimap<int, Prop*>::iterator it = thePropMgr->GetPropMap()->begin();
		it != thePropMgr->GetPropMap()->end(); ++it)
	{
		er = new EntityResource(count, it->second);
		er_vec.push_back(er);
		count++;
	}

	//now all the props are in ER form, stored in er_vec..
	//create first serial object
	BinarySerialSize SSize;

	//let it know the number of ERs you'll be writing..
	SSize.WriteNumberOfElements((int)er_vec.size());

	//then go through all ERs...
	for(std::vector<EntityResource*>::iterator it = er_vec.begin();
		it != er_vec.end(); ++it)
	{
		(*it)->WriteTo(&SSize);
	}

	//also here's the map size..
	std::string blank = "";
	int rows = thePropMgr->GetMaxRows();
	int cols = thePropMgr->GetMaxCols();
	SSize.WriteParameter(blank, rows);
	SSize.WriteParameter(blank, cols);
	


	//now we have the size in bytes, so we can make our buffer..
	int bufferSize = SSize.GetSize();
	_int8* buffer = new _int8[bufferSize];

	//create the -REAL- serializer
	BinarySerializer binary(buffer, bufferSize);

	//let it know the number of ERs...
	binary.WriteNumberOfElements((int)er_vec.size());

	//then go through all the ERs
	for(std::vector<EntityResource*>::iterator it = er_vec.begin();
		it != er_vec.end(); ++it)
	{
		D3DXMatrixRotationYawPitchRoll(&(*it)->m_rotationMtx, (*it)->m_rotationVec.y,
			(*it)->m_rotationVec.x, (*it)->m_rotationVec.z);
		(*it)->WriteTo(&binary);
	}

	//and map size...
	binary.WriteParameter(blank, rows);
	binary.WriteParameter(blank, cols);

	//and tell them there is no navgraph...
	bool navGraph = false;
	binary.WriteParameter(blank, navGraph);

	//finally, put that junk in a file..
	std::ofstream out(szTotalFileName, std::ios::binary);
	out.clear();
	out.write(reinterpret_cast<_int8*>(buffer), bufferSize);
	out.close();

	//clean up...
	delete[] buffer;
	for(UINT i = 0; i < er_vec.size(); i++)
	{
		delete er_vec[i];
	}
	er_vec.clear();
}

void GuiMgr::Load()
{
	if(isFullScreen)
	{
		theApp->enableFullScreen(false);
		isFullScreen = false;
	}


	OPENFILENAME ofn;
	TCHAR szTotalFileName[1024];
	memset(szTotalFileName, 0, sizeof(TCHAR)*1024);
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = theApp->getMainWindow();
	ofn.lpstrFilter = _T("unearthed level file (*.ue0)\0*.ue0\0binary file (*.bin)\0*bin\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szTotalFileName;
	ofn.nMaxFile = 10000;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_EXPLORER|OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = _T("ue0");

	if(!GetOpenFileName((LPOPENFILENAME)&ofn)) return;

	//for stats...
	std::string str, str2;
	str = szTotalFileName;
	size_t pos;
	pos = str.rfind("\\");
	str2 = str.substr(pos+1);

	theStatusBar->ResetCount();
	theStatusBar->SetFileName(str2);

	//do actual load here..
	SetCurrentID(-1);
	thePropMgr->RemoveAllProps();
	thePropMgr->UnloadTileMap();
	hasKilled = true;

	//now to load the file..
	std::ifstream in(szTotalFileName, std::ios::binary);

	//get the size of the file..
	int inSize;
	in.seekg(0, std::ios::end);
	inSize = in.tellg();
	in.seekg(0, std::ios::beg);

	//create the buffer
	_int8* buffer = new _int8[inSize];

	//read the file into the buffer
	in.read(buffer, inSize);
	in.close();

	//create the deserializer object
	BinaryDeserializer binary(buffer, inSize);

	//get number of ERs to expect..
	int numERs = binary.ReadNumberOfElements();
	er_vec.clear();


	//load 'em in
	EntityResource* er;
	for(int i = 0; i < numERs; i++)
	{
		er = new EntityResource(i);
		er->ReadFrom(&binary);
		
		thePropMgr->AddMyProp(i, (PropType)er->m_meshID,
			er->m_position, er->m_scale,
			er->m_rotationVec, *thePropMgr->GetDefaultFX());

		delete er;
	}

	int rows, cols;
	std::string blank = "";
	binary.ReadParameter(blank, rows);
	binary.ReadParameter(blank, cols);

	thePropMgr->BuildTileMap(rows, cols);

	bool navGraph;
	binary.ReadParameter(blank, navGraph);

	//don't care in here, rebuilds every save...

	delete[] buffer;
}

void GuiMgr::MakeNew()
{
}

void GuiMgr::BuildShaders()
{

	D3DXVECTOR3 temp;

	theShaders[0] = new CShader("fx/rim.fx", gDevice);
	theShaders[0]->SetTechnique("RimTech");
	temp = D3DXVECTOR3(BLUE.r, BLUE.g, BLUE.b);
	theShaders[0]->SetFloat3("gColor", temp);
	theShaders[0]->SetFloat("gIntensity", 1.0f);
	theShaders[0]->SetFloat("gSmoothStart", 0.0f);
	theShaders[0]->SetFloat("gSmoothEnd", 0.9f);
	theShaders[0]->SetNumPasses(1);
	theShaders[0]->SetType(SELECT_FX);

	theShaders[1] = new CShader("fx/toon.fx", gDevice);
	theShaders[1]->SetTechnique("ToonTech");
	temp = D3DXVECTOR3(BLACK.r, BLACK.g, BLACK.b);
	theShaders[1]->SetFloat3("gOutlineColor", temp);
	theShaders[1]->SetFloat("gOutlineThickness", 0.1f);
	temp = D3DXVECTOR3(WHITE.r, WHITE.g, WHITE.b);
	theShaders[1]->SetFloat3("gAmbientColor", temp);
	theShaders[1]->SetFloat("gAmbientPower", 0.05f);
	theShaders[1]->SetNumPasses(2);
	temp = D3DXVECTOR3(-100.0f, 1500.0f, -100.0f);
	thePropMgr->SetLightPos(temp);
	theShaders[1]->SetType(TOON_FX);

	theShaders[2] = new CShader("fx/diffuse.fx", gDevice);
	theShaders[2]->SetFloat3("gLightPos", temp);
	theShaders[2]->SetNumPasses(1);

	thePropMgr->SetDefaultFX(theShaders[1]);
	thePropMgr->SetSelectFX(theShaders[0]);
	thePropMgr->SetTileFX(theShaders[2]);
}

void GuiMgr::UnloadShaders()
{
	for(int i = 0; i < 3; i++)
		SAFE_DELETE(theShaders[i]);
}

void GuiMgr::InitGraph()
{
	NavGraph::Instance()->Initialize(525, 525, 2.5f, 2.5f, false);
}

void GuiMgr::FindPositions(int &topL, int &topR, int &botL, int &botR, EntityResource *entity)
{
	int bigZ = -INT_MAX;
	int bigX = -INT_MAX;
	int lilX = INT_MAX;

	int topRight;
	// top right..
	for(int i = 0; i < 4; i++)
	{
		if(entity->m_points[i].z > bigZ && entity->m_points[i].x > bigX)
		{
			topRight = i;
		}
	}

	bigZ = -INT_MAX;
	int topLeft;
	for(int i = 0; i < 4; i++)
	{
		if(i==topRight) continue;

		if(entity->m_points[i].z > bigZ && entity->m_points[i].x < lilX)
		{
			topLeft = i;
		}
	}

	lilX = INT_MAX;
	int botLeft;
	int botRight;
	for(int i = 0; i < 4; i++)
	{
		if(i==topRight || i == topLeft) continue;

		if(entity->m_points[i].x < lilX)
		{
			botLeft = i;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		if(i == topRight)
		{
			topR = NavGraph::Instance()->GetClosestNodeToPosition(entity->m_points[i], true);
		}
		else if(i == topLeft)
		{
			topL = NavGraph::Instance()->GetClosestNodeToPosition(entity->m_points[i], true);
		}
		else if(i == botLeft)
		{
			botL = NavGraph::Instance()->GetClosestNodeToPosition(entity->m_points[i], true);
		}
		else
		{
			botR = NavGraph::Instance()->GetClosestNodeToPosition(entity->m_points[i], true);
		}
	}

	if(botL > botR)
	{
		botRight = botL;
		botL = botR;
		botR = botRight;
	}
}

void GuiMgr::RemoveFromNavGraph(EntityResource *entity)
{
	//find extents for bottom (ground) 4 points
	AABB box;
	thePropMgr->GetUTAABB(entity->GetID());

	entity->m_points[0] = D3DXVECTOR3( box.minPt.x, 0.0f, box.minPt.z);
	entity->m_points[1] = D3DXVECTOR3( box.maxPt.x, 0.0f, box.minPt.z);
	entity->m_points[2] = D3DXVECTOR3( box.minPt.x, 0.0f, box.maxPt.z);
	entity->m_points[3] = D3DXVECTOR3( box.maxPt.x, 0.0f, box.maxPt.z);

	D3DXMATRIX T, S;
	D3DXMatrixTranslation(&T, entity->m_position.x, 1.0f, entity->m_position.z);
	D3DXMatrixScaling(&S, entity->m_scale.x, entity->m_scale.y, entity->m_scale.z);
	D3DXMATRIX toWorld = (S * entity->m_rotationMtx * T);

	for(int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&entity->m_points[i], &entity->m_points[i], &toWorld);
	}
	
	//525 x 525...

	int topL, topR, botL, botR;

	FindPositions(topL, topR, botL, botR, entity);

	//x = col
	//y = row
	int x1, x2, y1, y2;

	int startx = -1;
	int endx   = -1;
	int starty = -1;
	int endy   = -1;
//==============================================================
	{//block: top left -to- top right
		x1 = topL % 525;
		y1 = topL / 525;

		x2 = topR % 525;
		y2 = topR / 525;

		//if the y's are the same, we're good
		if(y1 == y2)
		{
			startx = topL;
			endx   = topR;
		}
		else
		{
			if(y1 < y2) //if they aren't the same height, bring them up to the highest point
			{
				y2 = y1;
				topR = topL + (x2-x1);
			}
			else
			{
				y1 = y2;
				topL = topR - (x2-x1);
			}

			startx = topL;
			endx   = topR;
		}

		while(startx <= endx)//traverse from left to right, removing nodes
		{
			NavGraph::Instance()->RemoveNode(startx);
			startx++;
		}

	}//end block: top left -to- top right
//=============================================================
	{//block: bottom left -to- bottom right
		x1 = botL % 525;
		y1 = botL / 525;

		x2 = botR % 525;
		y2 = botR / 525;

		//if the y's are the same, we're good
		if(y1 == y2)
		{
			startx = botL;
			endx   = botR;
		}
		else
		{
			if(y1 > y2) //if they aren't the same height, bring them down to the highest point, but keep the same distance
			{
				y2 = y1;
				botR = botL + (x2-x1);
			}
			else
			{
				y1 = y2;
				botL = botR - (x2-x1);
			}

			startx = botL;
			endx   = botR;
		}

		while(startx <= endx)
		{
			NavGraph::Instance()->RemoveNode(startx);//traverse left to right removing nodes
			startx++;
		}

	}//end block: bottom left -to- bottom right
//=============================================================
	{//block: top left -to- bottom left
		x1 = topL % 525;
		y1 = topL / 525;

		x2 = botL % 525;
		y2 = botL / 525;

		//if the x's are the same, we're good
		if(x1 == x2)
		{
			starty = topL;
			endy   = botL;
		}
		else
		{
			if(x1 > x2) //if they aren't the same width, bring them over to the leftest point, but keep the same y distance
			{
				x2 = x1;
				topL = botL - ((y2-y1)*525);
			}
			else
			{
				x1 = x2;
				botL = topL + ((y2-y1)*525);
			}

			starty = topL;
			endy   = botL;
		}

		while(starty <= endy)
		{
			NavGraph::Instance()->RemoveNode(starty);//traverse left to right removing nodes
			starty+=525;
		}

	}//end block: top left -to- bottom left
//=============================================================
	{//block: top right -to- bottom right
		x1 = topR % 525;
		y1 = topR / 525;

		x2 = botR % 525;
		y2 = botR / 525;

		//if the x's are the same, we're good
		if(x1 == x2)
		{
			starty = topR;
			endy   = botR;
		}
		else
		{
			if(x1 > x2) //if they aren't the same width, bring them over to the leftest point, but keep the same y distance
			{
				x2 = x1;
				botR = topR + ((y2-y1)*525);
			}
			else
			{
				x1 = x2;
				topR = botR - ((y2-y1)*525);
			}

			starty = topR;
			endy   = botR;
		}

		while(starty <= endy)
		{
			NavGraph::Instance()->RemoveNode(starty);//traverse left to right removing nodes
			starty+=524;
		}

	}//end block: top right -to- bottom right
}

void GuiMgr::SaveWithNavGraph()
{
if(isFullScreen)
	{
		theApp->enableFullScreen(false);
		Sleep(500);
		isFullScreen = false;
	}

	OPENFILENAME ofn;
	TCHAR szTotalFileName[1024];
	memset(szTotalFileName, 0, sizeof(TCHAR)*1024);
	TCHAR szAbsDirectory[1024];
	memset(szAbsDirectory, 0, sizeof(TCHAR)*1024);
	TCHAR szFileName[1024];
	memset(szFileName, 0, sizeof(TCHAR)*1024);
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = theApp->getMainWindow();
	//ofn.lpstrInitialDir = _T("
	ofn.lpstrFilter = _T("unearthed level file (*.ue0)\0*.ue0\0binary file (*.bin)\0*bin\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szTotalFileName;
	ofn.nMaxFile = 10000;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_EXPLORER;
	ofn.lpstrDefExt = _T("ue0");

	//returns false if the user cancel/closes dialog
	if(!GetSaveFileName((LPOPENFILENAME)&ofn)) return;

	//make navgraph...(this will take the longest)
	InitGraph();

	std::string str, str2;
	str = szTotalFileName;
	size_t pos;
	pos = str.rfind("\\");
	str2 = str.substr(pos+1);

	//for stats...
	theStatusBar->ResetCount();
	theStatusBar->SetFileName(str2);


	//do actual save here...
	EntityResource* er;
	int count = 0;
	//first turn props into ERs
	for(std::multimap<int, Prop*>::iterator it = thePropMgr->GetPropMap()->begin();
		it != thePropMgr->GetPropMap()->end(); ++it)
	{
		er = new EntityResource(count, it->second);
		er_vec.push_back(er);
		count++;
	}

	//now all the props are in ER form, stored in er_vec..
	//create first serial object
	BinarySerialSize SSize;

	//let it know the number of ERs you'll be writing..
	SSize.WriteNumberOfElements((int)er_vec.size());

	//then go through all ERs...
	for(std::vector<EntityResource*>::iterator it = er_vec.begin();
		it != er_vec.end(); ++it)
	{
		(*it)->WriteTo(&SSize);
	}

	//also here's the map size..
	std::string blank = "";
	int rows = thePropMgr->GetMaxRows();
	int cols = thePropMgr->GetMaxCols();
	SSize.WriteParameter(blank, rows);
	SSize.WriteParameter(blank, cols);

	bool ng = true;
	SSize.WriteParameter(blank, ng);
	NavGraph::Instance()->WriteTo(&SSize);

	


	//now we have the size in bytes, so we can make our buffer..
	int bufferSize = SSize.GetSize();
	_int8* buffer = new _int8[bufferSize];

	//create the -REAL- serializer
	BinarySerializer binary(buffer, bufferSize);

	//let it know the number of ERs...
	binary.WriteNumberOfElements((int)er_vec.size());

	//then go through all the ERs
	for(std::vector<EntityResource*>::iterator it = er_vec.begin();
		it != er_vec.end(); ++it)
	{
		D3DXMatrixRotationYawPitchRoll(&(*it)->m_rotationMtx, (*it)->m_rotationVec.y,
			(*it)->m_rotationVec.x, (*it)->m_rotationVec.z);
		
		if((*it)->m_entityType == ETYPE_PROP     ||
		   (*it)->m_entityType == ETYPE_RESOURCE ||
		   (*it)->m_entityType == ETYPE_BUILDING  )
		{
			RemoveFromNavGraph((*it));
		}
		(*it)->WriteTo(&binary);
	}

	//and map size...
	binary.WriteParameter(blank, rows);
	binary.WriteParameter(blank, cols);

	//and tell them there is a navgraph...
	bool navGraph = true;
	binary.WriteParameter(blank, navGraph);

	//finally save the navgraph to file.

	NavGraph::Instance()->WriteTo(&binary);

	//finally, put that junk in a file..
	std::ofstream out(szTotalFileName, std::ios::binary);
	out.clear();
	out.write(reinterpret_cast<_int8*>(buffer), bufferSize);
	out.close();

	//clean up...
	delete[] buffer;
	for(UINT i = 0; i < er_vec.size(); i++)
	{
		delete er_vec[i];
	}
	er_vec.clear();
}