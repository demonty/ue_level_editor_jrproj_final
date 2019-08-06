#ifndef PROP_H
#define PROP_H

#include "dxUtil.h"
#include "dxVertex.h"

//==================================================================
//MODEL
//==================================================================

struct Model
{
	ID3DXMesh* mesh;
	std::vector<Mtrl> materials;
	std::vector<IDirect3DTexture9*> textures;
	AABB boundingBox;

	Model()
	{
		mesh = 0;
	}
	~Model()
	{
		ReleaseCOM(mesh);
		for(UINT i = 0; i < textures.size(); i++)
			SAFE_RELEASE(textures[i]);
	}

	void buildBoundingBox()
	{
		VertexPNT* v = 0;
		mesh->LockVertexBuffer(0, (void**)&v);
		D3DXComputeBoundingBox(&v->pos,
							   mesh->GetNumVertices(),
							   mesh->GetNumBytesPerVertex(),
							   &boundingBox.minPt,
							   &boundingBox.maxPt);
		mesh->UnlockVertexBuffer();
	}

	void SetMaterials(D3DXCOLOR ambient,
					  D3DXCOLOR diffuse,
					  D3DXCOLOR specular,
					  float specularPower)
	{
		for(UINT i = 0; i < materials.size(); i++)
		{
			materials[i].ambient = ambient;
			materials[i].diffuse = diffuse;
			materials[i].spec = specular;
			materials[i].specPower = specularPower;
		}
	}

	void SetMaterialBySubset(int subset,
							 D3DXCOLOR ambient,
							 D3DXCOLOR diffuse,
							 D3DXCOLOR specular,
							 float specularPower)
	{
		materials[subset].ambient = ambient;
		materials[subset].diffuse = diffuse;
		materials[subset].spec = specular;
		materials[subset].specPower = specularPower;
	}
};


//==================================================================
//PROP SPECIFIC MODELS
//==================================================================
#define theDestWallModel DestWallModel::Instance()

struct DestWallModel : public Model
{
private:
	DestWallModel(){isLoaded = false;}
	DestWallModel(const DestWallModel&);
	DestWallModel* operator=(DestWallModel&);
public:
	static DestWallModel* DestWallModel::Instance();
	
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/destroyed_wall.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theGroundUnitModel GroundUnitModel::Instance()

struct GroundUnitModel : public Model
{
private:
	GroundUnitModel(){isLoaded = false;}
	GroundUnitModel(const GroundUnitModel&);
	GroundUnitModel* operator=(GroundUnitModel&);
public:
	static GroundUnitModel* GroundUnitModel::Instance();
	bool isLoaded;
	void load()
	{
		if(isLoaded) return;
		LoadXFile("art/props/meshes/SP_GroundUnit.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theRock01Model Rock01Model::Instance()

struct Rock01Model : public Model
{
private:
	Rock01Model(){isLoaded = false;}
	Rock01Model(const Rock01Model&);
	Rock01Model* operator=(Rock01Model&);
public:
	static Rock01Model* Rock01Model::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/rock01.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theRock02Model Rock02Model::Instance()

struct Rock02Model : public Model
{
private:
	Rock02Model(){isLoaded = false;}
	Rock02Model(const Rock02Model&);
	Rock02Model* operator=(Rock02Model&);
public:
	static Rock02Model* Rock02Model::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/rock02.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theRock03Model Rock03Model::Instance()

struct Rock03Model : public Model
{
private:
	Rock03Model(){isLoaded = false;}
	Rock03Model(const Rock03Model&);
	Rock03Model* operator=(Rock03Model&);
public:
	static Rock03Model* Rock03Model::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/rock03.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theGraveStone01Model GraveStone01Model::Instance()

struct GraveStone01Model : public Model
{
private:
	GraveStone01Model(){isLoaded = false;}
	GraveStone01Model(const GraveStone01Model&);
	GraveStone01Model* operator=(GraveStone01Model&);
public:
	static GraveStone01Model* GraveStone01Model::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/gravestone01.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theGraveStone02Model GraveStone02Model::Instance()

struct GraveStone02Model : public Model
{
private:
	GraveStone02Model(){isLoaded = false;}
	GraveStone02Model(const GraveStone02Model&);
	GraveStone02Model* operator=(GraveStone02Model&);
public:
	static GraveStone02Model* GraveStone02Model::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/gravestone02.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theGateModel GateModel::Instance()

struct GateModel : public Model
{
private:
	GateModel(){isLoaded = false;}
	GateModel(const GateModel&);
	GateModel* operator=(GateModel&);
public:
	static GateModel* GateModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/gate.x", &mesh, materials, textures);

		buildBoundingBox();

		isLoaded = true;
	}
};

#define theFenceModel FenceModel::Instance()

struct FenceModel : public Model
{
private:
	FenceModel(){isLoaded = false;}
	FenceModel(const FenceModel&);
	FenceModel* operator=(FenceModel&);
public:
	static FenceModel* FenceModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/fence.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theSPBaseModel SPBaseModel::Instance()

struct SPBaseModel : public Model
{
private:
	SPBaseModel(){isLoaded = false;}
	SPBaseModel(const SPBaseModel&);
	SPBaseModel* operator=(SPBaseModel&);
public:
	static SPBaseModel* SPBaseModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/SP_BaseBuilding.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theSPBaseUpgradeModel SPBaseUpgradeModel::Instance()

struct SPBaseUpgradeModel : public Model
{
private:
	SPBaseUpgradeModel(){isLoaded = false;}
	SPBaseUpgradeModel(const SPBaseUpgradeModel&);
	SPBaseUpgradeModel* operator=(SPBaseUpgradeModel&);
public:
	static SPBaseUpgradeModel* SPBaseUpgradeModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/SP_BaseUpgrade.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theSPGroundBuildingModel SPGroundBuildingModel::Instance()

struct SPGroundBuildingModel : public Model
{
private:
	SPGroundBuildingModel(){isLoaded = false;}
	SPGroundBuildingModel(const SPGroundBuildingModel&);
	SPGroundBuildingModel* operator=(SPGroundBuildingModel&);
public:
	static SPGroundBuildingModel* SPGroundBuildingModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/SP_GroundUnitBuilding.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theStraightPipeModel StraightPipeModel::Instance()

struct StraightPipeModel : public Model
{
private:
	StraightPipeModel(){isLoaded = false;}
	StraightPipeModel(const StraightPipeModel&);
	StraightPipeModel* operator=(StraightPipeModel&);
public:
	static StraightPipeModel* StraightPipeModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/straight_pipe.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theElbowPipeModel ElbowPipeModel::Instance()

struct ElbowPipeModel : public Model
{
private:
	ElbowPipeModel(){isLoaded = false;}
	ElbowPipeModel(const ElbowPipeModel&);
	ElbowPipeModel* operator=(ElbowPipeModel&);
public:
	static ElbowPipeModel* ElbowPipeModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/elbow_pipe.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theCrossPipeModel CrossPipeModel::Instance()

struct CrossPipeModel : public Model
{
private:
	CrossPipeModel(){isLoaded = false;}
	CrossPipeModel(const CrossPipeModel&);
	CrossPipeModel* operator=(CrossPipeModel&);
public:
	static CrossPipeModel* CrossPipeModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/cross_pipe.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theZombieGroundModel ZombieGroundModel::Instance()

struct ZombieGroundModel : public Model
{
private:
	ZombieGroundModel(){isLoaded = false;}
	ZombieGroundModel(const ZombieGroundModel&);
	ZombieGroundModel* operator=(ZombieGroundModel&);
public:
	static ZombieGroundModel* ZombieGroundModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/Z_GroundUnit.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theZBaseModel ZBaseModel::Instance()

struct ZBaseModel : public Model
{
private:
	ZBaseModel(){isLoaded = false;}
	ZBaseModel(const ZBaseModel&);
	ZBaseModel* operator=(ZBaseModel&);
public:
	static ZBaseModel* ZBaseModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/plane.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theGraveyardModel GraveyardModel::Instance()

struct GraveyardModel : public Model
{
private:
	GraveyardModel(){isLoaded = false;}
	GraveyardModel(const GraveyardModel&);
	GraveyardModel* operator=(GraveyardModel&);
public:
	static GraveyardModel* GraveyardModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/plane.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

#define theCoalMineModel CoalMineModel::Instance()

struct CoalMineModel : public Model
{
private:
	CoalMineModel(){isLoaded = false;}
	CoalMineModel(const CoalMineModel&);
	CoalMineModel* operator=(CoalMineModel&);
public:
	static CoalMineModel* CoalMineModel::Instance();
	bool isLoaded;
	void load()
	{
		LoadXFile("art/props/meshes/coal_mine.x", &mesh, materials, textures);
		buildBoundingBox();
		isLoaded = true;
	}
};

//==================================================================
//ACTUAL PROP
//==================================================================

//struct effex;

class Prop
{
private:
	int id;

public:
	Prop(int theID)
	{
		id = theID;
		position = VEC3_ZERO;
		scale = VEC3_ZERO;
		rotVec = VEC3_ZERO;
	}
	~Prop(){}

	int ID()const{return id;}
	void init();

	void GetBounds(AABB &box);
	AABB GetAABB();

public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	float rotation;
	D3DXVECTOR3 rotVec;

	Model* myModel;
	PropType type;
	D3DXMATRIX toWorld;
};





//=========================================
// tile stuff...
//
//

#define theTileModel TileModel::Instance()

struct TileModel : Model
{
private:
	TileModel(){isLoaded = false;}
	~TileModel(){textures[0] = whiteTex;}
	TileModel(const TileModel&);
	TileModel* operator=(TileModel&);
public:
	static TileModel* TileModel::Instance();

	IDirect3DTexture9* whiteTex;
	bool isLoaded;
	void load(LPDIRECT3DDEVICE9 device)
	{
		D3DXCreateTextureFromFile(device, "art/props/textures/whitetex.dds", &whiteTex);		

		LoadXFile("art/props/meshes/tile.x", &mesh, materials, textures);
		buildBoundingBox();
		
		for(UINT i = 0; i < textures.size(); i++)
			textures[i] = whiteTex;

		isLoaded = true;
	}
};

class Tile
{
public:
	struct WorldTex
	{
		D3DXMATRIX world;
		IDirect3DTexture9* tex;
		WorldTex(D3DXMATRIX w, IDirect3DTexture9* t)
		{
			world = w;
			tex = t;
		}
	};
	typedef std::vector<WorldTex> WTMap;
	WTMap myMap;
	Model* myModel;

public:
	Tile(){myModel = theTileModel;}
	~Tile(){}

	void GetBounds(AABB& box);

	//position
	int row;
	int col;
	
	D3DXVECTOR3 position;
};

#endif //prop_h