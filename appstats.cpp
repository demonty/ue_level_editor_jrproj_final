#include "dxUtil.h"
#include "dxApp.h"
#include "dxInput.h"
#include "appStats.h"
#include <tchar.h>
#include "dxCamera.h"

AppStats::AppStats()
: theFont(0), theFPS(0.0f), theMSPerFrame(0.0f)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = 18;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, _T("Arial")); //copy name of font into fontDescription
	
	//create font..
	D3DXCreateFontIndirect(gDevice, &fontDesc, &theFont);
}

AppStats::~AppStats()
{
	ReleaseCOM(theFont);
}

void AppStats::onLostDevice()
{
	theFont->OnLostDevice();
}
void AppStats::onResetDevice()
{
	theFont->OnResetDevice();
}

void AppStats::update(float dt)
{
	static float numFrames = 0.0f;
	static float timeElapsed = 0.0f;

	//increment frame count
	numFrames += 1.0f;
	
	//increase time elapsed by delta time
	timeElapsed += dt;

	//if roughly a second has passed, compute the frame stats..
	if( timeElapsed >= 1.0f)
	{
		//fps = numFrames / timeElapsed, 
		//timeElapsed ~1.0, so fps ~ numFrames
		theFPS = numFrames;

		//average time in milliseconds to render a frame
		theMSPerFrame = 1000.0f / theFPS;

		//reset time and frame count..
		numFrames = 0.0f;
		timeElapsed = 0.0f;
	}
}

void AppStats::display()
{
	//make static so memory is not allocated every frame...
	static char buffer[256];

	int x = (int)theGlobalInput->mx();
	int y = (int)theGlobalInput->my();
	//D3DXVECTOR3 c = theCamera->pos();


	sprintf_s(buffer, "fps: %.2f"
		"     x: %d" "     y: %d\n",
		theFPS, x, y);

	RECT R = {5, 720, 0, 0};
	theFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(255,255,255));
}