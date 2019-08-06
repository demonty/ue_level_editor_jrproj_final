#include "dxSprite.h"

dxSprite* dxSprite::Instance()
{
	static dxSprite instance;
	return &instance;
}

dxSprite::dxSprite()
{
	//BuildSpritePen();
}

dxSprite::~dxSprite()
{
	ReleaseCOM(pen);
}

void dxSprite::BuildSpritePen(LPDIRECT3DDEVICE9 device)
{
	theDevice = device;

	D3DXCreateSprite(theDevice, &pen);
}

void dxSprite::Begin()
{
	pen->Begin(NULL);
}

void dxSprite::End()
{
	pen->End();
}

void dxSprite::Flush()
{
	pen->Flush();
}

void dxSprite::SetTransform(D3DXMATRIX matrix)
{
	pen->SetTransform(&matrix);
}

void dxSprite::SetAlphaBlend(bool enable)
{
	theDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enable);
}

void dxSprite::SetAlphaTest(bool enable)
{
	theDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enable);
}

void dxSprite::OnLost()
{
	pen->OnLostDevice();
}

void dxSprite::OnReset()
{
	pen->OnResetDevice();
}
