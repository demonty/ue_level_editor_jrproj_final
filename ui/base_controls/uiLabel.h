#ifndef UILABEL_H
#define UILABEL_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiLabel : public uiControl
{
protected:
	std::string theCaption;
	ID3DXFont* theFont;
	D3DCOLOR theColor;
	DWORD theFormat;
	bool iBuilt;
public:
	uiLabel(LPDIRECT3DDEVICE9 device); //build from scratch
	uiLabel(ID3DXFont* font, LPDIRECT3DDEVICE9 device); //supply built font
	~uiLabel();

	void Draw();
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);
	
	void SetCaption(std::string caption){theCaption = caption;}
	std::string GetCaption(){return theCaption;}

	D3DCOLOR GetColor(){return theColor;}
	void SetColor(D3DCOLOR color){theColor = color;}

	DWORD GetFormat() {return theFormat;}
	void SetFormat(DWORD format){theFormat = format;}

	void SetFont(ID3DXFont* font);
	ID3DXFont* GetFont(){return theFont;}

	bool GiveMessage(GraphicsCoreMessageType msg, MouseResource* mouse, void* data);
};

#endif