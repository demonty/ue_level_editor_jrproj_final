#ifndef UI_LIST_ITEM_H
#define UI_LIST_ITEM_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiListItem : public uiControl
{
protected:
	float theStretchWidth;
	float theStretchHeight;
	bool isSelected;
	std::string theCaption;

public:
	uiListItem(LPDIRECT3DDEVICE9 device);
	~uiListItem();

	void Draw();
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);
	//void OnKeyDown(WPARAM key, LPARAM ext);
	//void OnKeyUp(WPARAM key, LPARAM ext);

	void OnSetFocus();
	void OnLostFocus();
	void SetSelect(bool select);
	void SetItemSize(float width, float height);
	void SetCaption(std::string caption);
	const char* GetCaption();

	virtual bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};

#endif