#include "uiControl.h"


uiControl::uiControl(LPDIRECT3DDEVICE9 device)
{
	theDevice = device;
	theCanvas = NULL;
	theChildren.clear();
	theParent = NULL;
	theMessageToSend = UIMT_NOTHING;
	myMessage = UIMT_NOTHING;
	SetID();
}

uiControl::~uiControl()
{
	RemoveAllChildren();

	//if(theCanvas == NULL) return;
	//else
	//{
	//	SAFE_DELETE(theCanvas);
	//}
}

int uiControl::nextID = 0;

void uiControl::SetID()
{
	id = nextID;
	nextID++;
}

bool uiControl::operator ==(uiControl &other)
{
	return GetID() == other.GetID() ? true : false;
}

void uiControl::LoadCanvas(char *file)
{
	D3DXCreateTextureFromFile(theDevice, file,
							  &theCanvas);
}

void uiControl::SetXYPos(float x, float y)
{
	thePosition = D3DXVECTOR2(x, y);
}

void uiControl::AddChild(uiControl *child)
{
	child->SetParent(this);
	theChildren.push_back(child);
}

void uiControl::AddChildFront(uiControl* child)
{
	child->SetParent(this);
	theChildren.push_front(child);
}

void uiControl::RemoveChild(uiControl *child)
{
	for(ChildList::iterator it = theChildren.begin();
		it != theChildren.end(); ++it)
	{
		if(*it == child)
		{
			//SAFE_DELETE(*it);
			theChildren.remove(*it);
			return;
		}
			
	}
}

void uiControl::RemoveAsChild(uiControl *child)
{
	for(ChildList::iterator it = theChildren.begin();
		it != theChildren.end(); ++it)
	{
		if(*it == child)
		{
			theChildren.remove(*it);
		}	
	}
}

void uiControl::MoveToFront(uiControl *control)
{
	RemoveAsChild(control);
	AddChildFront(control);
}

void uiControl::RemoveAllChildren()
{
	for(ChildList::iterator it = theChildren.begin();
		it != theChildren.end(); ++it)
	{
		SAFE_DELETE(*it);
		//theChildren.erase(it);
	}

	theChildren.clear();
}

int uiControl::GetChildCount()
{
	return (int)theChildren.size();
}

void uiControl::GetAbsolutePosition(D3DXVECTOR2* pos)
{
	pos->x += thePosition.x;
	pos->y += thePosition.y;

	if(theParent)
		theParent->GetAbsolutePosition(pos);
}

D3DXVECTOR2 uiControl::GetAbsolutePosition()
{
	if(!theParent)
	{
		return D3DXVECTOR2(GetXPos(),GetYPos());
	}
	else
	{
		return D3DXVECTOR2(GetXPos(), GetYPos())
		+ theParent->GetAbsolutePosition();
	}
}

void uiControl::DrawChildren()
{
	if(theChildren.empty()) return;

	for(ChildList::iterator it = theChildren.begin();
		it != theChildren.end(); ++it)
	{
		(*it)->Draw();
		if((*it)->GetChildCount() > 0)
		{
			(*it)->DrawChildren();
		}
	}
}

bool uiControl::CursorIntersect(float x, float y)
{
	D3DXVECTOR2 abs;
	abs = GetAbsolutePosition();

	if( x >= abs.x &&
		x <= (abs.x + theWidth) &&
		y >= abs.y &&
		y <= (abs.y + theHeight))
	{
		return true;
	}

	return false;
}

UserInterfaceMessageType uiControl::GetMessageToSend()
{
	return theMessageToSend;
}

void uiControl::SetMessageToSend(UserInterfaceMessageType msg)
{
	theMessageToSend = msg;
}

void uiControl::SetMyMessage(UserInterfaceMessageType msg)
{
	myMessage = msg;
}

bool uiControl::GiveToAll(GraphicsCoreMessageType msg, MouseResource* mouse, void* data)
{
	for(ChildList::iterator it = theChildren.begin();
		it != theChildren.end(); it++)
	{
		if((*it)->GiveMessage(msg, mouse, data))
			return true;
	}
	theMessageToSend = UIMT_NOTHING;
	return false;
}

bool uiControl::GiveToAllReverse(GraphicsCoreMessageType msg, MouseResource* mouse, void* data)
{ //think this is correct...

	for(ChildList::reverse_iterator it = theChildren.rbegin();
		it != theChildren.rend(); ++it)
	{
		if((*it)->GiveMessage(msg, mouse, data))
			return true;
	}
	theMessageToSend = UIMT_NOTHING;
	return false;
}
