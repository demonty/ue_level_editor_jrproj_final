#include "dxUtil.h"
#include "dxVertex.h"

void ::LoadXFile(const std::string& filename,
				 ID3DXMesh** meshOut,
				 std::vector<Mtrl>& materials,
				 std::vector<IDirect3DTexture9*>& textures)
{
	ID3DXMesh* meshSys = 0;
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	D3DXLoadMeshFromX(filename.c_str(), D3DXMESH_SYSTEMMEM, gDevice,
					  &adjBuffer, &mtrlBuffer, 0, &numMtrls, &meshSys);


	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	meshSys->GetDeclaration(elems);

	bool hasNormal = false;
	D3DVERTEXELEMENT9 term = D3DDECL_END();
	for(int i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if(elems[i].Stream == 0xff)
			break;
		if(elems[i].Type == D3DDECLTYPE_FLOAT3 &&
			elems[i].Usage == D3DDECLUSAGE_NORMAL &&
			elems[i].UsageIndex == 0)
		{
			hasNormal = true;
			break;
		}
	}


	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexPNT::Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh* temp = 0;
	meshSys->CloneMesh(D3DXMESH_SYSTEMMEM,
		elements, gDevice, &temp);
	ReleaseCOM(meshSys);
	meshSys = temp;

	
	if(!hasNormal)
		D3DXComputeNormals(meshSys, 0);

	
	meshSys->Optimize(D3DXMESH_MANAGED | D3DXMESHOPT_COMPACT |
					  D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
					  (DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0, meshOut);
	ReleaseCOM(meshSys);
	ReleaseCOM(adjBuffer);


	if(mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* dxMtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(DWORD i = 0; i < numMtrls; ++i)
		{
			Mtrl m;
			m.ambient = dxMtrls[i].MatD3D.Diffuse;
			m.diffuse = dxMtrls[i].MatD3D.Diffuse;
			m.spec = dxMtrls[i].MatD3D.Specular;
			m.specPower = dxMtrls[i].MatD3D.Power;
			materials.push_back(m);

			if(dxMtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				char texFN[64];
				strcpy_s(texFN, "art/props/textures/");
				strcat_s(texFN, dxMtrls[i].pTextureFilename);
				D3DXCreateTextureFromFile(gDevice, texFN, &tex);

				textures.push_back(tex);
			}
			else
			{
				textures.push_back(0);
			}
		}
	}
	ReleaseCOM(mtrlBuffer);
}