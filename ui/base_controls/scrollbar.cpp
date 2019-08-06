#include "../dxSprite.h"
#include "uiScrollBar.h"
#include "uiButton.h"

uiScrollBar::uiScrollBar(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	theThumb = new uiButton(device);
	theTopArrow = new uiButton(device);
	theBottomArrow = new uiButton(device);

	theThumbIndexPos = 0;
	theThumbHeight = 0.0f;
	theChange = 1;
	SetMinMax(0, 10);
	isDragMode = false;

	theThumbPos = D3DXVECTOR2(0.0f, 0.0f);
	theThumbScale = D3DXVECTOR2(0.0f, 0.0f);
}

uiScrollBar::~uiScrollBar()
{
	delete theThumb;
	delete theTopArrow;
	delete theBottomArrow;
}

float uiScrollBar::AutoSizeThumb()
{
	float range = (GetHeight() -
		theBottomArrow->GetHeight() -
		theTopArrow->GetHeight()) * 1.0f;

	float increment = range / theMax;

	return (increment / theThumb->GetHeight());
}

float uiScrollBar::AutoSizeBackground()
{
	float range = (GetHeight() -
		theBottomArrow->GetHeight() -
		theTopArrow->GetHeight()) * 1.0f;

	float increment = range / theMax;

	return (increment / theBackgroundHeight);
}

void uiScrollBar::LoadBackground(char *file)
{
	LoadCanvas(file);

	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(D3DXIMAGE_INFO));
	D3DXGetImageInfoFromFile(file, &info);
	theBackgroundHeight = info.Height * 1.0f;
}

void uiScrollBar::LoadThumb(char *upFile, char *downFile)
{
	theThumb->LoadDefaultImgFromFile(upFile);
	theThumb->LoadPressedImgFromFile(downFile);

	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(D3DXIMAGE_INFO));
	D3DXGetImageInfoFromFile(upFile, &info);
	theThumbHeight = info.Height * 1.0f;
}

void uiScrollBar::LoadTopArrow(char *upFile, char *downFile)
{
	theTopArrow->LoadDefaultImgFromFile(upFile);
	theTopArrow->LoadPressedImgFromFile(downFile);
}

void uiScrollBar::LoadBottomArrow(char *upFile, char *downFile)
{
	theBottomArrow->LoadDefaultImgFromFile(upFile);
	theBottomArrow->LoadPressedImgFromFile(downFile);
}

void uiScrollBar::SetMinMax(int min, int max)
{
	theMin = min;
	theMax = max;

	if(theThumbIndexPos > theMax)
	{
		theThumbIndexPos = theMax;
	}

	if(theThumbIndexPos < theMin)
	{
		theThumbIndexPos = theMin;
	}
}

int uiScrollBar::GetPositionValue(float pos)
{//pos is either x or y, depending on vertical/horizontal bar

	//evetually this will be the method that
	//allows for you to click on the track
	//and have the thumb move there, rather
	//than having to use up/down buttons...
	return 0;
}

void uiScrollBar::SetThumbIndex(int value)
{
	int newValue = value;

	if(value < theMin)
	{
		newValue = theMin;
	}
	else if(value >= theMax)
	{
		newValue = theMax - 1;
	}

	float range = (GetHeight() -
		theBottomArrow->GetHeight() -
		theTopArrow->GetHeight()) * 1.0f;

	float increment = range / theMax;

	theThumbPos.y = theTopArrow->GetHeight() + (increment * newValue);
	theThumbIndexPos = newValue;
}

void uiScrollBar::Draw()
{
	D3DXVECTOR2 abs;
	GetAbsolutePosition(&abs);

	D3DXVECTOR2 scale;
	D3DXVECTOR2 trans;

	scale.x = 1.0f;
	scale.y = AutoSizeBackground();
	trans.x = abs.x;
	trans.y = abs.y + theTopArrow->GetHeight();
	
	//transform for this
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scale, NULL, 0.0f, &trans);
	theSpritePen->SetTransform(matrix);




	//set back to normal when done
	D3DXMatrixIdentity(&matrix);
	theSpritePen->SetTransform(matrix);
}

void uiScrollBar::OnMouseDown(int button, int x, int y)
{
}

void uiScrollBar::OnMouseUp(int button, int x, int y)
{
}

void uiScrollBar::OnMouseMove(int x, int y)
{
}

void uiScrollBar::OnKeyDown(WPARAM key, LPARAM ext)
{
}

void uiScrollBar::OnKeyUp(WPARAM key, LPARAM ext)
{
}

bool uiScrollBar::PostMessage(UINT msg, WPARAM wParam, LPARAM lParam, void *Data)
{
	return false;
}