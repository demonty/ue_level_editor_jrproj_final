#include "uiLabel.h"
//#include <tchar.h>

uiLabel::uiLabel(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	iBuilt = true;
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = 20;
	fontDesc.Width = 0;
	fontDesc.Weight = FW_BOLD;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, _T("Arial")); //copy name of font into fontDescription
	
	//create font..
	D3DXCreateFontIndirect(theDevice, &fontDesc, &theFont);
	
	theFormat = DT_NOCLIP;
	theColor = D3DCOLOR_XRGB(0, 0, 0);
	theCaption = "";

}

uiLabel::uiLabel(ID3DXFont *font, LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	iBuilt = false;
	theFont = font;
	theFormat = DT_NOCLIP;
	theColor = D3DCOLOR_XRGB(0, 0, 0);
	theCaption = "";
}

uiLabel::~uiLabel()
{
	if(iBuilt)
		ReleaseCOM(theFont);
}

void uiLabel::SetFont(ID3DXFont* font)
{	
	if(iBuilt)
		ReleaseCOM(theFont);

	theFont = font;
	iBuilt = false;
}

void uiLabel::Draw()
{
	D3DXVECTOR2 abs(0.0f, 0.0f);
	GetAbsolutePosition(&abs);

	RECT R = {(long)abs.x, (long)abs.y,
		(long)(abs.x + GetWidth()), (long)(abs.x + GetHeight())};

	if(theCaption != "" && !theCaption.empty())
	{
		theFont->DrawText(0, theCaption.c_str(),
			theCaption.length(), &R, theFormat, theColor);
	}
}

void uiLabel::OnMouseDown(int button, int x, int y)
{
}

void uiLabel::OnMouseUp(int button, int x, int y)
{
}

void uiLabel::OnMouseMove(int x, int y)
{
}

bool uiLabel::GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void *data)
{
	return false;
}