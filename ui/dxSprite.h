#ifndef DXSPRITE_H
#define DXSPRITE_H
#pragma once

#include <d3dx9.h>
#include "../dxUtil.h"

#define theSpritePen dxSprite::Instance()

class dxSprite
{
private:
	ID3DXSprite* pen;
	LPDIRECT3DDEVICE9 theDevice;

	dxSprite();
	dxSprite(const dxSprite&);
	dxSprite* operator=(dxSprite&);
public:
	~dxSprite();
	static dxSprite* dxSprite::Instance();
	ID3DXSprite* Pen(){return pen;}

	void BuildSpritePen(LPDIRECT3DDEVICE9 device);

	void Begin();
	void End();
	void Flush();

	void SetTransform(D3DXMATRIX matrix);
	void SetAlphaBlend(bool enable);
	void SetAlphaTest(bool enable);

	void OnLost();
	void OnReset();
};

#endif