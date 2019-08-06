#ifndef UIBUTTON_H
#define UIBUTTON_H


#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiLabel;

class uiButton : public uiControl
{
protected:
	IDirect3DTexture9* theDefaultImg;
	IDirect3DTexture9* thePressedImg;
	uiLabel* theCaption;
	bool fromFile;

public:
	uiButton(LPDIRECT3DDEVICE9 device);
	~uiButton();

	void Draw();

	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);

	void SetLabel(uiLabel* caption);
	uiLabel* GetLabel(){return theCaption;}

	void SetCaption(std::string caption);
	std::string GetCaption();

	void LoadDefaultImgFromFile(char* file);
	void LoadPressedImgFromFile(char* file);
	void LoadDefaultImg(IDirect3DTexture9* dft);
	void LoadPressedImg(IDirect3DTexture9* psd);

	virtual bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};


#endif