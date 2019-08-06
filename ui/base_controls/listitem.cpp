#include "../dxSprite.h"
#include "uiListItem.h"
#include "uiListBox.h"

uiListItem::uiListItem(LPDIRECT3DDEVICE9 device)
: uiControl(device)
{
	theStretchWidth = 1.0f;
	theStretchHeight = 1.0f;
	SetCaption("");
	SetSelect(false);
}

uiListItem::~uiListItem()
{
}

void uiListItem::SetSelect(bool select)
{
	isSelected = select;
}

void uiListItem::SetItemSize(float width, float height)
{
	theStretchWidth = width;
	theStretchHeight = height;
}

void uiListItem::SetCaption(std::string caption)
{
	theCaption = caption;
}

const char* uiListItem::GetCaption()
{
	return theCaption.c_str();
}

void uiListItem::OnSetFocus()
{
}

void uiListItem::OnLostFocus()
{
}

void uiListItem::Draw()
{
}

void uiListItem::OnMouseDown(int button, int x, int y)
{
}

void uiListItem::OnMouseUp(int button, int x, int y)
{
}

void uiListItem::OnMouseMove(int x, int y)
{
}

bool uiListItem::GiveMessage(GraphicsCoreMessageType msg, MouseResource *mouse, void *data)
{
	return false;
}