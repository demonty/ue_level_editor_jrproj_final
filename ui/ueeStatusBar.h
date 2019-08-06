#ifndef UEE_STATUS_BAR
#define UEE_STATUS_BAR

#include <d3dx9.h>
#include "../dxApp.h"
#include "../dxUtil.h"

#include "base_controls/uiWindow.h"
#include "base_controls/uiLabel.h"
#include "base_controls/uiButton.h"
#include "base_controls/uiCheckBox.h"

#include "uiMgrBase.h"

class Prop;

class UEE_StatusBar : public ManagerBase
{
private:
	std::string         theFileName;
	int					theLastSaveCnt;
	ID3DXFont*          theStatusFont;
	IDirect3DTexture9*  theBar;
	uiLabel*            theStatus[7];
	//fps,
	//ID,
	//xyz,
	//type,
	//filename,
	//since last,
	//num assets,

public:
	UEE_StatusBar();
	~UEE_StatusBar();

	void Initialize(LPDIRECT3DDEVICE9 device, MouseResource* mresource, uiWindow* desktop);

	void OnLost();
	void OnReset();

	void SetStatus(float fps, Prop* prop);
	std::string TypeToString(PropType type);
	void SetFileName(std::string file);

	void AddToCount();
	void ResetCount();
};

#endif