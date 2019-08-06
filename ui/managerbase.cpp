#include "uiMgrBase.h"
#include "base_controls/uiControl.h"
#include "base_controls/uiWindow.h"

ManagerBase::ManagerBase()
{
	theParentMgr = NULL;
	isLoaded = false;
}

ManagerBase::~ManagerBase()
{
	theMsgSendingControls.clear();
}

void ManagerBase::Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop)
{
	theDesktop = desktop;
}

void ManagerBase::OnLost()
{
}

void ManagerBase::OnReset()
{
}

bool ManagerBase::ResponseFromUI(UserInterfaceMessageType& re_msg)
{
	for(std::vector<uiControl*>::iterator it = theMsgSendingControls.begin();
		it != theMsgSendingControls.end(); ++it)
	{
		if((*it)->GetMessageToSend() == UIMT_NOTHING)
		{
			continue;
		}
		else
		{
			re_msg = (*it)->GetMessageToSend();
			(*it)->SetMessageToSend(UIMT_NOTHING);
			return true;
		}
	}

	return false;
}

void ManagerBase::SetType(ManagerType type)
{
	theType = type;
}

ManagerType ManagerBase::GetType()
{
	return theType;
}

void ManagerBase::SetLoaded(bool loaded)
{
	isLoaded = loaded;
}

bool ManagerBase::GetLoaded()
{
	return isLoaded;
}

uiWindow* ManagerBase::GetMyWindow()
{
	return myWindow;
}

void ManagerBase::SetParentMgr(ManagerBase* mgr)
{
	theParentMgr = mgr;
}

ManagerBase* ManagerBase::GetParentMgr()
{
	return theParentMgr;
}