#include "ueeStatusBar.h"
#include "../prop.h"
#include "../prop_mgr.h"

UEE_StatusBar::UEE_StatusBar()
{
	SetType(M_STATUSBAR);
	theFileName = "Untitled.ue0";
	theLastSaveCnt = 0;
}

UEE_StatusBar::~UEE_StatusBar()
{
	theMsgSendingControls.clear();
	ReleaseCOM(theBar);
	ReleaseCOM(theStatusFont);
}

void UEE_StatusBar::OnLost()
{
	theStatusFont->OnLostDevice();
}

void UEE_StatusBar::OnReset()
{
	theStatusFont->OnResetDevice();
}

void UEE_StatusBar::Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop)
{
	theDesktop = desktop;

	D3DXCreateTextureFromFile(device, "art/gui/windows/ue_status_bar.dds", &theBar);

	myWindow = new uiWindow(false, device);
	myWindow->SetWidth(1280);
	myWindow->SetHeight(32);
	myWindow->SetXYPos(0.0f, 742.0f);
	myWindow->SetDrag(false);
	myWindow->SetCanvas(theBar);
	theDesktop->AddChild(myWindow);

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
	D3DXCreateFontIndirect(device, &fontDesc, &theStatusFont);
	//end font

	for(int i = 0; i < 7; i++)
	{
		std::string str;
		std::stringstream out;

		theStatus[i] = new uiLabel(device);
		theStatus[i]->SetWidth(64);
		theStatus[i]->SetHeight(20);
		theStatus[i]->SetYPos(10.0f); //x needs to be fiddled with..
		theStatus[i]->SetFont(theStatusFont);
		theStatus[i]->SetFormat(DT_NOCLIP);
		theStatus[i]->SetColor(D3DCOLOR_XRGB(250, 250, 250));
		out << "blah: ";
		out << i;
		str = out.str();
		theStatus[i]->SetCaption(str);
		myWindow->AddChild(theStatus[i]);
	}

	theStatus[0]->SetXPos(0.0f);
	theStatus[1]->SetXPos(100.0f);
	theStatus[2]->SetXPos(368.0f);
	theStatus[3]->SetXPos(168.0f);
	theStatus[4]->SetXPos(650.0f);
	theStatus[5]->SetXPos(1050.0f);
	theStatus[6]->SetXPos(850.0f);
}

void UEE_StatusBar::AddToCount()
{
	theLastSaveCnt++;
}

void UEE_StatusBar::ResetCount()
{
	theLastSaveCnt = 0;
}

void UEE_StatusBar::SetFileName(std::string file)
{
	theFileName = file;
}

void UEE_StatusBar::SetStatus(float fps, Prop *prop)
{
	std::string str;
	std::stringstream out;
	out << "fps: ";
	out << fps;
	str = out.str();
	theStatus[0]->SetCaption(str);

	out.clear();
	out.str("");
	out << "num assets: ";
	out << thePropMgr->GetNumProps();
	str = out.str();
	theStatus[6]->SetCaption(str);

	if(prop == NULL)
	{
		theStatus[1]->SetCaption("ID: -1");
		theStatus[2]->SetCaption("pos:     x:   ---    y:   ---    z:   ---    ");
		theStatus[3]->SetCaption("type: none selected");
		str = "file: ";
		str += theFileName;
		theStatus[4]->SetCaption(str);
		out.clear();
		out.str("");

		out << "moves since last save: ";
		out << theLastSaveCnt;
		str = out.str();
		theStatus[5]->SetCaption(str);
	}
	else
	{
		out.clear();
		out.str("");

		out << "ID: ";
		out << prop->ID();
		str = out.str();
		theStatus[1]->SetCaption(str);

		out.clear();
		out.str("");
		out << "pos:     ";
		out << "x:  ";
		out << prop->position.x;
		out << "   y:   ";
		out << prop->position.y;
		out << "   z:   ";
		out << prop->position.z;
		str = out.str();
		theStatus[2]->SetCaption(str);

		out.clear();
		out.str("");
		out << "type: ";
		out << TypeToString(prop->type);
		str = out.str();
		theStatus[3]->SetCaption(str);

		out.clear();
		out.str("");
		out << "file: ";
		out << theFileName;
		str = out.str();
		theStatus[4]->SetCaption(str);

		out.clear();
		out.str("");
		out << "moves since last save: ";
		out << theLastSaveCnt;
		str = out.str();
		theStatus[5]->SetCaption(str);
	}
}

std::string UEE_StatusBar::TypeToString(PropType type)
{
	std::string str;

	switch(type)
	{
	case PROP_ROCK01:
		str = "rock 01";
		break;

	case PROP_ROCK02:
		str = "rock 02";
		break;

	case PROP_ROCK03:
		str = "rock 03";
		break;

	case PROP_TOMBSTONE01:
		str = "tombstone 01";
		break;

	case PROP_TOMBSTONE02:
		str = "tombstone 02";
		break;

	case PROP_FENCE:
		str = "fence";
		break;

	case PROP_GATE:
		str = "gate";
		break;

	case PROP_DESTROYED_WALL_01:
		str = "destroyed wall";
		break;

	case PROP_PIPE_STRAIGHT:
		str = "straight pipe";
		break;

	case PROP_PIPE_ELBOW:
		str = "elbow pipe";
		break;

	case PROP_PIPE_CROSS:
		str = "cross pipe";
		break;

	case UNIT_SP_GROUND:
		str = "sp ground unit";
		break;

	case UNIT_Z_GROUND:
		str = "zombie ground unit";
		break;

	case BUILDING_SP_BASE:
		str = "sp base building";
		break;

	case BUILDING_Z_BASE:
		str = "zombie base building";
		break;

	case BUILDING_COAL_MINE:
		str = "coal mine resource";
		break;

	case BUILDING_GRAVEYARD:
		str = "graveyard resource";
		break;

	//case BUILDING_UPGRAYEDD:
	//	str = "sp base upgrayedd";
	//	break;

	//case BUILDING_GUNIT:
	//	str = "sp gunit building";
	//	break;

	default:
		str = "invalid type";
		break;
	};

	return str;
}