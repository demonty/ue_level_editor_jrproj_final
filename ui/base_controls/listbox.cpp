#include "../dxSprite.h"
#include "uiListBox.h"
#include "uiListItem.h"

uiListBox::uiListBox(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
}

uiListBox::~uiListBox()
{
}

void uiListBox::Draw()
{
}

void uiListBox::OnMouseDown(int button, int x, int y)
{
}

void uiListBox::OnMouseUp(int button, int x, int y)
{
}

void uiListBox::OnMouseMove(int x, int y)
{
}

bool uiListBox::GiveMessage(GraphicsCoreMessageType msg, MouseResource *mouse, void *data)
{
	return false;
}