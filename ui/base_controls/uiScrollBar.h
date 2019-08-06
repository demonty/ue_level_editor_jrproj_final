#ifndef UISCROLLBAR_H
#define UISCROLLBAR_H

#include <d3dx9.h>
#include "../../dxUtil.h"

#include "uiControl.h"

class uiButton;

class uiScrollBar : public uiControl
{
protected:
	float AutoSizeThumb();
	float AutoSizeBackground();
	void  UpdateScaling();
	
	int theMin;
	int theMax;
	int theThumbIndexPos;
	int theChange;
	float theBackgroundHeight;
	bool isDragMode;

	D3DXVECTOR2 theThumbPos;
	D3DXVECTOR2 theThumbScale;
	float theThumbHeight;
	
	uiButton* theThumb;
	uiButton* theTopArrow;
	uiButton* theBottomArrow;

public:
	uiScrollBar(LPDIRECT3DDEVICE9 device);
	~uiScrollBar();

	void LoadThumb(char* upFile, char* downFile);
	void LoadTopArrow(char* upFile, char* downFile);
	void LoadBottomArrow(char* upFile, char* downFile);
	void LoadBackground(char* file);

	void SetThumbIndex(int value);
	int  GetThumbIndex();
	int  GetPositionValue(float pos);
	void SetMinMax(int min, int max);
	void SetChange(int change);

	void Draw();
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y);
	void OnKeyDown(WPARAM key, LPARAM ext);
	void OnKeyUp(WPARAM key, LPARAM ext);

	bool PostMessage(UINT msg, WPARAM wParam, LPARAM lParam, void* Data);
};

#endif