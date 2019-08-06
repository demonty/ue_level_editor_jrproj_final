#ifndef UI_LIST_BOX_H
#define UI_LIST_BOX_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiListItem;

class uiListBox : public uiControl
{
protected:
	std::list<uiListItem*> theListItems;
	uiListItem* theSelectedItem;
	IDirect3DTexture9* theDefaultImg;
	IDirect3DTexture9* theSelectedImg;
	ID3DXFont* theFont;

public:
	uiListBox(LPDIRECT3DDEVICE9 device);
	~uiListBox();

	void Draw();
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);
	//void OnKeyDown(WPARAM key, LPARAM ext);
	//void OnKeyUp(WPARAM key, LPARAM ext);

	virtual bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};

#endif