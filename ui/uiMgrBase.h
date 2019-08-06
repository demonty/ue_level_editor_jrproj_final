#ifndef UI_MANAGER_BASE_H
#define UI_MANAGER_BASE_H

#include <d3dx9.h>
#include "../dxUtil.h"

class uiControl;
class uiWindow;

class ManagerBase
{
public:
				  ManagerBase();
	virtual		 ~ManagerBase();

	virtual void Initialize(
					LPDIRECT3DDEVICE9 device, 
					MouseResource* mresource,
					uiWindow* desktop);

	virtual void OnLost();
	virtual void OnReset();
	
	bool		 ResponseFromUI(UserInterfaceMessageType& re_msg);

	void		 SetType(ManagerType type);
	ManagerType  GetType();

	void		 SetLoaded(bool loaded);
	bool		 GetLoaded();

	uiWindow*    GetMyWindow();

	void		 SetParentMgr(ManagerBase* mgr);
	ManagerBase* GetParentMgr();


protected:
	ManagerType				 theType;
	uiWindow*				 theDesktop;
	uiWindow*				 myWindow;
	ManagerBase*			 theParentMgr;
	std::vector<uiControl*>  theMsgSendingControls;
	bool					 isLoaded;
};

#endif