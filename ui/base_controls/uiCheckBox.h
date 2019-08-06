#ifndef UICHECKBOX_H
#define UICHECKBOX_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiButton;
class uiLabel;

class uiCheckBox : public uiControl
{
protected:
	bool isChecked;
	uiButton* theButton;
	uiLabel* theLabel;

public:
	uiCheckBox(LPDIRECT3DDEVICE9 device);
	~uiCheckBox();

	bool IsChecked(){return isChecked;}
	void SetChecked(bool checked){isChecked = checked;}
	void LoadCheckedImgFromFile(char* file);
	void LoadDefaultImgFromFile(char* file);
	void LoadCheckedImg(IDirect3DTexture9* tex);
	void LoadDefaultImg(IDirect3DTexture9* tex);
	void SetCaption(std::string caption);
	std::string GetCaption();
	void SetCaptionFont(ID3DXFont* font);
	void SetCaptionColor(D3DCOLOR color);
	void SetCaptionFormat(DWORD format);

	void Draw();
	virtual void OnMouseDown(int button, int x, int y);
	virtual void OnMouseUp(int button, int x, int y);
	virtual void OnMouseMove(int x, int y);
	//virtual void OnKeyDown(WPARAM key, LPARAM ext);
	//virtual void OnKeyUp(WPARAM key, LPARAM ext);

	virtual bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};

#endif