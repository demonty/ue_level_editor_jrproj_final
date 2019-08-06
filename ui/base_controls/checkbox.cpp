#include "../dxSprite.h"
#include "uiCheckBox.h"
#include "uiButton.h"
#include "uiLabel.h"

uiCheckBox::uiCheckBox(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	isChecked = false;
	theButton = new uiButton(device);
	theLabel = new uiLabel(device);
}

uiCheckBox::~uiCheckBox()
{
	delete theButton;
	delete theLabel;
}

void uiCheckBox::LoadCheckedImgFromFile(char *file)
{
	theButton->LoadPressedImgFromFile(file);
}

void uiCheckBox::LoadDefaultImgFromFile(char* file)
{
	theButton->LoadDefaultImgFromFile(file);
}

void uiCheckBox::LoadCheckedImg(IDirect3DTexture9* tex)
{
	theButton->LoadPressedImg(tex);
}

void uiCheckBox::LoadDefaultImg(IDirect3DTexture9* tex)
{
	theButton->LoadDefaultImg(tex);
}

void uiCheckBox::SetCaption(std::string caption)
{
	theLabel->SetCaption(caption);
}

void uiCheckBox::SetCaptionFont(ID3DXFont* font)
{
	theLabel->SetFont(font);
}

void uiCheckBox::SetCaptionColor(D3DCOLOR color)
{
	theLabel->SetColor(color);
}

void uiCheckBox::SetCaptionFormat(DWORD format)
{
	theLabel->SetFormat(format);
}

std::string uiCheckBox::GetCaption()
{
	return theLabel->GetCaption();
}

void uiCheckBox::Draw()
{
	D3DXVECTOR2 abs;
	abs = GetAbsolutePosition();

	if(isChecked)
	{
		theButton->SetPressed(true);
	}
	else
	{
		theButton->SetPressed(false);
	}
	theButton->SetXYPos(abs.x, abs.y);
	theButton->Draw();

	theLabel->SetXYPos(abs.x + this->GetWidth(), abs.y);
	theLabel->Draw();
}

void uiCheckBox::OnMouseDown(int button, int x, int y)
{
	theMessageToSend = UIMT_NOTHING;
	return;
}

void uiCheckBox::OnMouseUp(int button, int x, int y)
{
	if(isChecked)
	{
		theButton->SetPressed(false);
	}
	else
	{
		theButton->SetPressed(true);
		theMessageToSend = myMessage;
	}

	DoStuff();
	isChecked = !isChecked;
}

void uiCheckBox::OnMouseMove(int x, int y)
{
	theMessageToSend = UIMT_NOTHING;
	return;
}

bool uiCheckBox::GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void *data)
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
		break;

	default:
		break;
	};

	return false;
}