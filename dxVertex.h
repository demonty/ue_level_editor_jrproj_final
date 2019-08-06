#include <d3dx9.h>

#ifndef DXVERTEX_H
#define DXVERTEX_H

void InitVertexDeclarations();
void DestroyVertexDeclarations();

//vertex - position
struct VertexPos
{
	D3DXVECTOR3 pos;
	static IDirect3DVertexDeclaration9* Decl;

	VertexPos()
		:pos(0.0f, 0.0f, 0.0f)
	{
	}
	VertexPos(float ex, float why, float zee)
		:pos(ex, why, zee)
	{
	}
	VertexPos(const D3DXVECTOR3& v)
		:pos(v)
	{
	}
};

//vertex - postion, color
struct VertexCol
{
	D3DXVECTOR3 pos;
	D3DCOLOR col;
	static IDirect3DVertexDeclaration9* Decl;

	VertexCol()
		:pos(0.0f, 0.0f, 0.0f), col(0x00000000)
	{
	}
	VertexCol(float ex, float why, float zee, D3DCOLOR color)
		: pos(ex, why, zee), col(color)
	{
	}
	VertexCol(const D3DXVECTOR3& v, D3DCOLOR color)
		: pos(v), col(color)
	{
	}
};

//vertex - position, normal
struct VertexPN
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	static IDirect3DVertexDeclaration9* Decl;

	VertexPN()
		: pos(0.0f, 0.0f, 0.0f), norm(0.0f, 0.0f, 0.0f)
	{
	}
	VertexPN(float ex, float why, float zee,
			float nx, float ny, float nz)
		: pos(ex, why, zee), norm(nx, ny, nz)
	{
	}
	VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
		:pos(v), norm(n)
	{
	}
};

//vertex - position, normal, texture
struct VertexPNT
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	D3DXVECTOR2 tex0;
	static IDirect3DVertexDeclaration9* Decl;
	
	VertexPNT()
		:pos(0.0f, 0.0f, 0.0f), norm(0.0f, 0.0f, 0.0f), tex0(0.0f, 0.0f)
	{
	}
	VertexPNT(float ex, float why, float zee,
			  float nx, float ny, float nz,
			  float u, float v)
			  :pos(ex, why, zee), norm(nx, ny, nz), tex0(u, v)
	{
	}
	VertexPNT(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
		:pos(v), norm(n), tex0(uv)
	{
	}
};

#endif //dxvertex_h