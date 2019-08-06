#ifndef UICONTROL_H
#define UICONTROL_H
#pragma once

#include <d3dx9.h>
#include "../../dxUtil.h"

#include <list>

class uiControl
{ //base for all ui controls..
private:
	int id;
	static int nextID;
	void SetID();

protected:
	LPDIRECT3DDEVICE9 theDevice;

	int theWidth;
	int theHeight;

	D3DXVECTOR2 thePosition;
	
	bool isVisible;
	bool isFocus;
	bool isTypeable;
	bool isPressed;

	IDirect3DTexture9* theCanvas;

	typedef std::list<uiControl*> ChildList;
	ChildList theChildren;
	uiControl* theParent;

	UserInterfaceMessageType theMessageToSend;
	UserInterfaceMessageType myMessage;

public:
	uiControl(LPDIRECT3DDEVICE9 device);
	~uiControl();
	bool operator==(uiControl&);

	int GetID(){return id;}

	int GetWidth(){return theWidth;}
	int GetHeight(){return theHeight;}
	void SetWidth(int width){theWidth = width;}
	void SetHeight(int height){theHeight = height;}

	D3DXVECTOR2* GetPosition(){return &thePosition;}
	void SetPosition(D3DXVECTOR2 pos){thePosition = pos;}
	float GetXPos(){return thePosition.x;}
	float GetYPos(){return thePosition.y;}
	void SetXPos(float x){thePosition.x = x;}
	void SetYPos(float y){thePosition.y = y;}
	void SetXYPos(float x, float y);

	bool IsVisible(){return isVisible;}
	void SetVisible(bool visible){isVisible = visible;}
	bool IsFocus(){return isFocus;}
	void SetFocus(bool focus){isFocus = focus;}
	bool IsTypeable(){return isTypeable;}
	void SetTypeable(bool typeable){isTypeable = typeable;}
	bool IsPressed(){return isPressed;}
	void SetPressed(bool pressed){isPressed = pressed;}

	IDirect3DTexture9* GetCanvas(){return theCanvas;}
	void SetCanvas(IDirect3DTexture9* canvas){theCanvas=canvas;}
	void LoadCanvas(char* file);

	uiControl* GetParent(){return theParent;}
	void SetParent(uiControl* parent){theParent = parent;}
	ChildList* GetChildList(){return &theChildren;}
	uiControl* GetLastChild(){return theChildren.back();}
	
	void AddChild(uiControl* child);
	void AddChildFront(uiControl* child);
	void RemoveChild(uiControl* child);
	void RemoveAsChild(uiControl* child);
	void MoveToFront(uiControl* control);
	void RemoveAllChildren();
	int GetChildCount();
	void GetAbsolutePosition(D3DXVECTOR2* pos);
	D3DXVECTOR2 GetAbsolutePosition();

	virtual void DoStuff(){}
	UserInterfaceMessageType GetMessageToSend();
	void SetMessageToSend(UserInterfaceMessageType msg);
	void SetMyMessage(UserInterfaceMessageType msg);

	virtual void Draw() = 0;
	void DrawChildren();

	virtual void OnMouseDown(int button, int x, int y) = 0;
	virtual void OnMouseUp(int button, int x, int y) = 0;
	virtual void OnMouseMove(int x, int y) = 0;

	bool CursorIntersect(float x, float y);

	//========================================
	// until messaging is completely figured out
	// then key presses won't be supported in
	// the ui =P
	//
	//virtual void OnKeyDown(WPARAM key, LPARAM ext) = 0;
	//virtual void OnKeyUp(WPARAM key, LPARAM ext) = 0;

	virtual bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data) = 0;
	bool GiveToAll(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
	bool GiveToAllReverse(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};

#endif