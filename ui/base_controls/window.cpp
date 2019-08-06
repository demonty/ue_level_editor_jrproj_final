#include "../dxSprite.h"
#include "uiWindow.h"

uiWindow::uiWindow(bool isParent, LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	SetWindowType(isParent);
	if(!isParent)
		theParent = NULL;
	isDraggable = false;
	isDragging = false;
	SetPressed(false);
}

uiWindow::~uiWindow()
{
}

void uiWindow::Draw()
{
	if(!isParentWindow)
	{
		D3DXVECTOR3 c(0.0f, 0.0f, 0.0f);
		D3DXVECTOR2 abs;
		abs = GetAbsolutePosition();
		D3DXVECTOR3 p(abs.x, abs.y, 0.0f);
		theSpritePen->Pen()->Draw(
			theCanvas, 0, &c, &p,
			D3DCOLOR_XRGB(255, 255, 255));
		theSpritePen->Pen()->Flush();
	}
}

void uiWindow::OnMouseDown(int button, int x, int y)
{
	if(!isParentWindow && isDraggable)
	{
		SetFocus(true);
		//theParent->MoveToFront(this);
		D3DXVECTOR2 abs;
		abs = GetAbsolutePosition();

		dragOffset.x = x - abs.x;
		dragOffset.y = y - abs.y;
		isDragging = true;
	}
}

void uiWindow::OnMouseUp(int button, int x, int y)
{
	if(!isParentWindow && isDraggable)
	{
		isDragging = false;
	}
}

void uiWindow::OnMouseMove(int x, int y)
{
	if(!isParentWindow && isDragging)
	{
		//SetFocus(false);
		//theParent->MoveToFront((uiControl*)&(*this));
		D3DXVECTOR2 abs;
		abs = GetAbsolutePosition();

		SetXPos(GetXPos() + (x - abs.x) - dragOffset.x);
		SetYPos(GetYPos() + (y - abs.y) - dragOffset.y);
	}
}

void uiWindow::LoadCanvasFromFile(char *file)
{
	D3DXCreateTextureFromFile(theDevice, file, &theCanvas);
}

bool uiWindow::GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data)
{
	switch(msg)
	{

	case GCMT_LBUTTONDOWN:
		if(CursorIntersect(mouse->m_absoluteXY.x, mouse->m_absoluteXY.y))
		{
			//SetFocus(true);
			if(!GiveToAll(msg, mouse, data))
				OnMouseDown(msg, (int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
			return true;
		}
		break;

	case GCMT_LBUTTONUP:
		if(CursorIntersect(mouse->m_absoluteXY.x, mouse->m_absoluteXY.y))
		{
			if(!GiveToAll(msg, mouse, data))
				OnMouseUp(msg, (int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
			return true;
		}
		//else if(IsFocus())
		//{
		//	OnMouseUp(msg, (int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
		//	return true;
		//}
		//break;

	case GCMT_MOUSEMOVE:
		if(isDragging)
		{
			OnMouseMove((int)mouse->m_absoluteXY.x, (int)mouse->m_absoluteXY.y);
			return true;
		}

	default:
		break;
	};

	return false;
}