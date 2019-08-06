#ifndef GUI_MGR_H
#define GUI_MGR_H

#include <d3dx9.h>
#include "../dxUtil.h"
#include "uiMgrBase.h"

class AppStats;

class uiControl;
class uiWindow;
class uiButton;
class uiLabel;
class uiCheckBox;
class UEE_ToolBar;
class UEE_UtilBar;
class UEE_TopMenu;
class UEE_StatusBar;

class Prop;
class CShader;
class EntityResource;


class GuiMgr : public ManagerBase
{ //factory for all things gui..
	typedef std::map<ManagerType, ManagerBase*> ManagerMap;
private:
	LPDIRECT3DDEVICE9	theDevice;
	MouseResource*		theMouse;

	ManagerMap			theManagers;
	UEE_ToolBar*		theToolBar;
	UEE_TopMenu*		theTopMenu;
	UEE_UtilBar*        theUtilBar;
	UEE_StatusBar*		theStatusBar;

	//top menu
	int                 theCurrentCam;

	//tool bar
	bool				showTools;
	D3DXVECTOR3         theRotAxis;
	int                 intAxis;
	ToolType            theCurrentTool;
	ToolType            theCurrentPicker;
	ToolType            theCurrentAssetType;
	PropType			theCurrentPropType;
	
	int                 theSpot;
	float				amtToMove;
	int					currentID;
	bool				hasKilled;
	bool                shouldPick;
	bool				isFullScreen;
	bool                isUniformScale;

	CShader*            theShaders[3];	
	std::vector<EntityResource*> er_vec;

	AppStats*			theAppStats;

public:
	 GuiMgr();
	~GuiMgr();

	void Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop);
	
	void Draw();
	
	void OnLost();
	void OnReset();

	void Update(float dt);

	void SendToGui(GraphicsCoreMessageType msg, void* data);
	bool GetUIMessage(UserInterfaceMessageType& re_msg);

	bool ShowToolBar();
	void SetToolBar(bool tools);

	void AddManager(ManagerBase* mgr);
	void RemoveManager(ManagerType type);
	ManagerBase* GetManager(ManagerType type);
	void MakeManager(ManagerType type);
	void SetNULL(ManagerType type);
	void SetTool(ToolType tool);
	void SetAxis(int axis);
	
	void DoPicking();
	void SetCurrentID(int id);
	void DoToolAction(int dir);
	D3DXVECTOR3 MoveAboutAxis(int axis, int dir);
	void DoMove(ToolType type, D3DXVECTOR3 vec);

	void AddProp();
	void RemoveProp();
	void ClearProps();

	void Save();
	void Load();
	void MakeNew();

	void SaveWithNavGraph();
	void InitGraph();
	void FindPositions(int &topL, int &topR, int &botL, int &botR, EntityResource* entity);
	void RemoveFromNavGraph(EntityResource* entity);


	void BuildShaders();
	void UnloadShaders();
};

#endif