#ifndef UIWINDOW_H
#define UIWINDOW_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiWindow : public uiControl
{
protected:
	bool isParentWindow;
	bool isDraggable;
	bool isDragging;

	D3DXVECTOR2 dragOffset;

public:
	uiWindow(bool isParent, LPDIRECT3DDEVICE9 device);
	~uiWindow();

	void Draw();
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);

	bool GetWindowType(){return isParentWindow;}
	void SetWindowType(bool isParent){isParentWindow = isParent;}

	bool CanDrag(){return isDraggable;}
	void SetDrag(bool draggable){isDraggable = draggable;}

	void LoadCanvasFromFile(char* file);

	bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
	
};

#endif