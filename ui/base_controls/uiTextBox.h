//#ifndef UITEXTBOX_H
//#define UITEXTBOX_H
//
//#include <d3dx9.h>
//#include "dxUtil.h"
//
//#include "uiControl.h"
//
//class uiTextBox : public uiControl
//{
//protected:
//	std::string theText;
//	ID3DXFont* theFont;
//
//	ID3DXLine* theCaretLine;
//	D3DXVECTOR2 theCaretPts[2];
//	bool isCaretVisible;
//	int theCaretPosition;
//	float theTextWidth;
//	float theTextHeight;
//public:
//	uiTextBox();
//	uiTextBox(ID3DXFont* font);
//	~uiTextBox();
//
//	void Draw();
//	void OnMouseDown(int button, int x, int y);
//	void OnMouseUp(int button, int x, int y);
//	void OnMouseMove(int x, int y);
//	void OnKeyDown(WPARAM key, LPARAM ext);
//	void OnKeyUp(WPARAM key, LPARAM ext);
//	void OnSysKey(WPARAM key, LPARAM ext);
//
//	const char* GetText()const{return theText.c_str();}
//	void SetText(char* Text);
//	int GetCharAtPos(int x, int y);
//	bool CursorIntersectChar(int x, int y);
//	float GetStringWidth(std::string str);
//	float GetStringHeight(std::string str);
//	int GetCaretPos(){return theCaretPosition;}	
//	bool InsertText(char* text);
//	int RemoveText(int charAmt);
//
//	bool PostMessage(UINT msg, WPARAM wParam, LPARAM lParam, void* Data){return false;}
//};
//
//#endif