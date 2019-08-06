#include "../dxSprite.h"
#include "uiLabel.h"
#include "uiButton.h"

uiButton::uiButton(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	theDefaultImg = NULL;
	thePressedImg = NULL;
	theCaption = new uiLabel(device);
	SetPressed(false);
	fromFile = false;
}

uiButton::~uiButton()
{
	if(fromFile)
	{
		ReleaseCOM(theDefaultImg);
		ReleaseCOM(thePressedImg);
	}
	SAFE_DELETE(theCaption);
}

void uiButton::Draw()
{
	D3DXVECTOR3 c(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 abs;
	abs = GetAbsolutePosition();
	D3DXVECTOR3 p(abs.x, abs.y, 0.0f);

	if(IsPressed())
	{
		theSpritePen->Pen()->Draw(
			thePressedImg, 0, &c, &p,
			D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		theSpritePen->Pen()->Draw(
			theDefaultImg, 0, &c, &p,
			D3DCOLOR_XRGB(255, 255, 255));
	}

	if(theCaption)
	{
		theCaption->SetXYPos(abs.x, abs.y);
		theCaption->SetWidth(GetWidth());
		theCaption->SetHeight(GetHeight());
		theCaption->Draw();
	}

	theSpritePen->Flush();
}

void uiButton::OnMouseDown(int button, int x, int y)
{
	SetPressed(true);
	theMessageToSend = myMessage;
}

void uiButton::OnMouseUp(int button, int x, int y)
{
	SetPressed(false);
	DoStuff();
}

void uiButton::OnMouseMove(int x, int y)
{
	theMessageToSend = UIMT_NOTHING;
	return;
}

void uiButton::SetLabel(uiLabel* caption)
{
	if(theCaption)
		delete theCaption;
	theCaption = caption;
}

void uiButton::SetCaption(std::string caption)
{
	theCaption->SetCaption(caption);
}

std::string uiButton::GetCaption()
{
	return theCaption->GetCaption();
}

void uiButton::LoadDefaultImgFromFile(char *file)
{
	fromFile = true;
	D3DXCreateTextureFromFile(theDevice, file,
							  &theDefaultImg);
}

void uiButton::LoadPressedImgFromFile(char *file)
{
	D3DXCreateTextureFromFile(theDevice, file,
							  &thePressedImg);
}

void uiButton::LoadDefaultImg(IDirect3DTexture9* dft)
{
	fromFile = false;
	theDefaultImg = dft;
}

void uiButton::LoadPressedImg(IDirect3DTexture9* psd)
{
	thePressedImg = psd;
}

bool uiButton::GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void *data)
{
	switch(msg)
	{

	case GCMT_LBUTTONDOWN:
		if(CursorIntersect(mouse->m_absoluteXY.x, mouse->m_absoluteXY.y))
		{
			if(!GiveToAllReverse(msg, mouse, data))
				OnMouseDown(msg, (int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
			return true;
		}
		break;

	case GCMT_LBUTTONUP:
		if(CursorIntersect(mouse->m_absoluteXY.x, mouse->m_absoluteXY.y))
		{
			if(!GiveToAllReverse(msg, mouse, data))
				OnMouseUp(msg, (int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
			return true;
		}
		else if(IsPressed())
		{ //they started to press, but backed out

			SetPressed(false);
		}
		break;

	default:
		break;
	};

	return false;
}

