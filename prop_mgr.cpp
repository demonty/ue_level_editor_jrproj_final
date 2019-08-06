#include "prop_mgr.h"
#include "prop.h"
#include "dxApp.h"
#include "dxCamera.h"
#include "dxInput.h"
#include "CShader.h"

PropMgr* PropMgr::Instance()
{
	static PropMgr instance;
	return &instance;
}

void PropMgr::Initialize(LPDIRECT3DDEVICE9 device)
{
	m_NextID = 0;
	theDevice = device;

	LoadTextures();

	theFenceModel->load();
	theGateModel->load();
	theRock01Model->load();
	theRock02Model->load();
	theRock03Model->load();
	theGraveStone01Model->load();
	theGraveStone02Model->load();
	theSPBaseModel->load();
	//theSPBaseUpgradeModel->load();
	//theSPGroundBuildingModel->load();
	theDestWallModel->load();
	theGroundUnitModel->load();
	theStraightPipeModel->load();
	theElbowPipeModel->load();
	theCrossPipeModel->load();
	theZombieGroundModel->load();
	theCoalMineModel->load();
	theZBaseModel->load();
	theGraveyardModel->load();
}

Model* PropMgr::GetPropModel(PropType type)
{
	switch(type)
	{
	case PROP_FENCE:
		return theFenceModel;

	case PROP_GATE:
		return theGateModel;

	case PROP_ROCK01:
		return theRock01Model;

	case PROP_ROCK02:
		return theRock02Model;

	case PROP_ROCK03:
		return theRock03Model;

	case PROP_TOMBSTONE01:
		return theGraveStone01Model;

	case PROP_TOMBSTONE02:
		return theGraveStone02Model;

	case PROP_PIPE_STRAIGHT:
		return theStraightPipeModel;

	case PROP_PIPE_ELBOW:
		return theElbowPipeModel;

	case PROP_PIPE_CROSS:
		return theCrossPipeModel;

	case BUILDING_SP_BASE:
		return theSPBaseModel;

	//case BUILDING_UPGRAYEDD:
	//	return theSPBaseUpgradeModel;

	//case BUILDING_GUNIT:
	//	return theSPGroundBuildingModel;

	case PROP_DESTROYED_WALL_01:
		return theDestWallModel;

	case UNIT_SP_GROUND:
		return theGroundUnitModel;

	case UNIT_Z_GROUND:
		return theZombieGroundModel;

	case BUILDING_Z_BASE:
		theZBaseModel->textures[0] = zbase_tex;
		return theZBaseModel;

	case BUILDING_GRAVEYARD:
		theGraveyardModel->textures[0] = graveyard_tex;
		return theGraveyardModel;

	case BUILDING_COAL_MINE:
		return theCoalMineModel;

	default:
		return NULL; //need to replace with some sort of error..
	};
}

IDirect3DTexture9* PropMgr::GetTileTex(TileType type)
{
	switch(type)
	{
	case DEFAULT:
		return default_tex;

	case SELECT:
		return select_tex;

	default:
		return default_tex;
	};
}

PropMgr::~PropMgr()
{
	UnloadTextures();
	UnloadTileMap();
	RemoveAllProps();
}

D3DXVECTOR3 PropMgr::TileToWorld(int row, int col)
{
	return D3DXVECTOR3(((float)row - m_maxRows/2.0f)*64.0f,
				0.0f, ((float)col - m_maxCols/2.0f)*64.0f);
}

void PropMgr::LoadTextures()
{
	//load the textures
	D3DXCreateTextureFromFile(theDevice, "art/tiles/ground.bmp", &default_tex);
	D3DXCreateTextureFromFile(theDevice, "art/tiles/select_tex.dds", &select_tex);

	//populate the texture map
	m_texMap.insert(std::make_pair(DEFAULT, default_tex));
	m_texMap.insert(std::make_pair(SELECT, select_tex));

	//and the reverse tex map
	m_revTexMap.insert(std::make_pair(default_tex, DEFAULT));
	m_revTexMap.insert(std::make_pair(select_tex, SELECT));

	D3DXCreateTextureFromFile(theDevice, "art/props/textures/groundcracked_base.bmp", &zbase_tex);
	D3DXCreateTextureFromFile(theDevice, "art/props/textures/groundcracked.bmp", &graveyard_tex);
	
}

void PropMgr::UnloadTextures()
{
	m_texMap.clear();
	m_revTexMap.clear();

	ReleaseCOM(default_tex);
	ReleaseCOM(select_tex);
}

Prop* PropMgr::GetProp(int id)
{
	PropMap::const_iterator cit = m_propMap.find(id);
	return cit->second;
}

CShader* PropMgr::GetFX(int id)
{
	FXMap::const_iterator cit = m_fxMap.find(id);
	return cit->second;
}

int PropMgr::GetMaxRows()
{
	return m_maxRows;
}

int PropMgr::GetMaxCols()
{
	return m_maxCols;
}

AABB PropMgr::GetAABB(int id)
{
	PropMap::const_iterator cit = m_propMap.find(id);
	AABB box;
	cit->second->GetAABB().xform(cit->second->toWorld, box);
	return box;
}

AABB PropMgr::GetUTAABB(int id)
{
	PropMap::const_iterator cit = m_propMap.find(id);
	AABB box;
	box = cit->second->GetAABB();
	return box;
}

void PropMgr::AddTile(int row, int col, D3DXMATRIX toWorld, TileType type)
{
	m_tileMap[row][col]->myMap.push_back(Tile::WorldTex(toWorld, GetTileTex(type)));
}

void PropMgr::AddTile(int row, int col, float rot, TileType type)
{
	D3DXMATRIX T, R;
	D3DXVECTOR3 ax(0.0f, 1.0f, 0.0f);
	D3DXMatrixTranslation(&T, m_tileMap[row][col]->position.x,
		0.01f, m_tileMap[row][col]->position.z);
	D3DXMatrixRotationAxis(&R, &ax, rot);

	m_tileMap[row][col]->myMap.push_back(Tile::WorldTex(R*T, GetTileTex(type)));
}

void PropMgr::AddTile(int row, int col, TileType type)
{
	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, m_tileMap[row][col]->position.x,
		0.01f, m_tileMap[row][col]->position.z);
	
	m_tileMap[row][col]->myMap.push_back(Tile::WorldTex(T, GetTileTex(type)));
}

void PropMgr::RemoveTile(int row, int col, TileType type)
{//the problem is that the corresponding "toWorld" matrix has to be
	//removed as well, incase any rotation has been applied...
	if(m_tileMap[row][col]->myMap.empty()) return;
	TileType tt;
	for(std::vector<Tile::WorldTex>::iterator it = m_tileMap[row][col]->myMap.begin();
		it != m_tileMap[row][col]->myMap.end(); ++it)
	{
		tt = m_revTexMap.find(it->tex)->second;
		if(tt == type)
		{
			m_tileMap[row][col]->myMap.erase(it);
			return;
		}
	}
}

void PropMgr::RemoveAllTilesTyped(TileType type)
{
	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			RemoveTile(i, j, type);
		}
	}
}

void PropMgr::RemoveLastTile(int row, int col)
{
	if(m_tileMap[row][col]->myMap.size() >= 1)
	{
		m_tileMap[row][col]->myMap.pop_back();
	}
}

void PropMgr::SetBaseTile(TileType type)
{
	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			if(!m_tileMap[i][j]->myMap.empty())
				m_tileMap[i][j]->myMap[0].tex = GetTileTex(type);
			else
				AddTile(i,j,type);
		}
	}
}

void PropMgr::RotateLastTile(int row, int col, float rot)
{
	UINT i = m_tileMap[row][col]->myMap.size() - 1;
	D3DXVECTOR3 p = m_tileMap[row][col]->position;
	D3DXVECTOR3 axis(0.0f, 1.0f, 0.0f);
	D3DXMATRIX R, T;
	D3DXMatrixTranslation(&T, p.x, p.y, p.z);
	D3DXMatrixRotationAxis(&R, &axis, rot);
	m_tileMap[row][col]->myMap[i].world = R * T;
}

void PropMgr::RemoveAllThisTile(int row, int col)
{
	m_tileMap[row][col]->myMap.clear();
}

void PropMgr::ChangePropFX(int id, CShader &fx)
{
	if(id == -1) return;

	FXMap::iterator it = m_fxMap.find(id);
	m_fxMap.erase(it);
	m_fxMap.insert(std::make_pair(id, &fx));
}

void PropMgr::ChangePropFX(Prop* p, CShader &fx)
{
	FXMap::iterator it = m_fxMap.find(p->ID());
	m_fxMap.erase(it);
	m_fxMap.insert(std::make_pair(p->ID(), &fx));
}

D3DXMATRIX* PropMgr::GetPropWorld(int id)
{
	return &GetProp(id)->toWorld;
}

D3DXMATRIX* PropMgr::GetPropWorld(Prop* p)
{
	return &p->toWorld;
}

void PropMgr::AddProp(int id, PropType type, D3DXVECTOR3 position, CShader &fx)
{
	Prop* p = new Prop(id);
	p->type = type;
	p->position = position;
	p->rotation = 0.0f;
	p->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	p->toWorld = T;

	p->myModel = GetPropModel(type);
	m_propMap.insert(std::make_pair(p->ID(), p));

	m_fxMap.insert(std::make_pair(p->ID(), &fx));
	m_NextID++;
}

void PropMgr::AddProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, CShader &fx)
{
	Prop* p = new Prop(id);
	p->type = type;
	p->position = position;
	p->scale = scale;

	D3DXMATRIX T, S;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	p->toWorld = S * T;

	p->myModel = GetPropModel(type);
	m_propMap.insert(std::make_pair(p->ID(), p));

	m_fxMap.insert(std::make_pair(p->ID(), &fx));
	m_NextID++;
}

void PropMgr::AddMyProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 XYZrotation, CShader &fx)
{
	Prop* p = new Prop(id);
	p->type = type;
	p->position = position;
	p->scale = scale;
	p->rotVec = XYZrotation;
	p->toWorld = MakeMatrix(position, scale, XYZrotation);

	p->myModel = GetPropModel(type);
	m_propMap.insert(std::make_pair(p->ID(), p));

	m_fxMap.insert(std::make_pair(p->ID(), &fx));
	m_NextID++;
}

void PropMgr::AddProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 rotationVec, float rotationAmt, CShader &fx)
{
	Prop* p = new Prop(id);
	p->type = type;
	p->position = position;
	p->scale = scale;
	p->rotation = rotationAmt;

	D3DXMATRIX T, S, R;
	D3DXMatrixRotationAxis(&R, &rotationVec, rotationAmt);
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	p->toWorld = R * S * T;

	p->myModel = GetPropModel(type);
	m_propMap.insert(std::make_pair(p->ID(), p));

	m_fxMap.insert(std::make_pair(p->ID(), &fx));
	m_NextID++;
}

void PropMgr::RemoveProp(int id)
{
	if(id == -1) return;

	PropMap::iterator it = m_propMap.find(id);
	delete it->second;
	m_propMap.erase(it);

	m_fxMap.erase(m_fxMap.find(id));
}

void PropMgr::RemoveProp(Prop* p)
{
	m_fxMap.erase(m_fxMap.find(p->ID()));

	PropMap::iterator it = m_propMap.find(p->ID());
	delete it->second;
	m_propMap.erase(it);
}

void PropMgr::RemoveAllProps()
{
	for(PropMap::iterator it = m_propMap.begin(); it != m_propMap.end(); ++it)
		delete it->second;

	m_propMap.clear();

	m_fxMap.clear();
	m_NextID = 0;
}

void PropMgr::TransformProp(int id, D3DXMATRIX toWorld)
{
	GetProp(id)->toWorld = toWorld;
}

void PropMgr::TransformProp(Prop* p, D3DXMATRIX toWorld)
{
	p->toWorld = toWorld;
}

void PropMgr::RotateProp(int id, float angle)
{
	Prop* p = GetProp(id);
	p->rotation = angle;

	D3DXVECTOR3 ax(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 pos = p->position;
	D3DXVECTOR3 scl = p->scale;
	D3DXMATRIX W, R, S, T;
	D3DXMatrixTranslation(&T, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&S, scl.x, scl.y, scl.z);
	D3DXMatrixRotationAxis(&R, &ax, angle);
	W = R * S * T;
	TransformProp(p, W);
}

void PropMgr::TranslateProp(int id, D3DXVECTOR3 position)
{
	Prop* p = GetProp(id);

	D3DXVECTOR3 ax(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 pos = position;
	p->position = position;
	D3DXVECTOR3 scl = p->scale;
	float angle = p->rotation;

	D3DXMATRIX W, R, S, T;
	D3DXMatrixTranslation(&T, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&S, scl.x, scl.y, scl.z);
	D3DXMatrixRotationAxis(&R, &ax, angle);
	W = R * S * T;
	TransformProp(p, W);
}

D3DXMATRIX PropMgr::MakeMatrix(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 rotation)
{
	D3DXMATRIX W, R, S, T;
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	//to make relative.. W = T*R*S
	W = S * R * T;
	return W;
}

void PropMgr::DrawProp(Prop* prop)
{
	FXMap::iterator FXM = m_fxMap.find(prop->ID());
	CShader* fx = FXM->second;

	fx->SetMatrix("gWVP", prop->toWorld*theCamera->viewProj());
	fx->SetMatrix("gWorld", prop->toWorld);
	
	if(!SetUniqueFXVariables(prop, fx)) return; //wasn't able to, so don't draw

	fx->Begin(0);
	for(UINT j = 0; j < fx->GetNumPasses(); j++)
	{
		fx->BeginPass(j);
		for(UINT i = 0; i < prop->myModel->textures.size(); i++)
		{
			fx->SetTexture("gTex", prop->myModel->textures[i]);
			fx->CommitChanges();
			prop->myModel->mesh->DrawSubset(i);
		}

		fx->EndPass();
	}
	fx->End();
}

bool PropMgr::SetUniqueFXVariables(Prop *prop, CShader *fx)
{
	D3DXVECTOR3 temp;

	switch(fx->GetType())
	{
	case TOON_FX:
		temp = GetLightPos() - prop->position;
		fx->SetFloat3("gLightDir", temp);
		return true;
		break;
	case SELECT_FX:
		fx->SetFloat3("gPlayerPos", theCamera->pos());
		/*temp = GetLightPos() - prop->position;
		fx->SetFloat3("gLightDir", temp);*/
		return true;
		break;
	case DEFAULT_FX:

		break;
	default:
		return false;
	};
	//fx->CommitChanges();
	return true;
}

void PropMgr::Draw()
{
	DrawTiles();

	for(PropMap::iterator it = m_propMap.begin(); it != m_propMap.end(); ++it)
	{
		DrawProp(it->second);
	}
}

void PropMgr::GetRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{
	POINT s;
	GetCursorPos(&s);
	ScreenToClient(theApp->getMainWindow(), &s);

	float w = (float)theApp->theD3DPP.BackBufferWidth;
	float h = (float)theApp->theD3DPP.BackBufferHeight;

	D3DXMATRIX proj = theCamera->proj();

	float x = (2.0f*s.x/w - 1.0f) / proj(0,0);
	float y = -(2.0f*s.y/h - 1.0f) / proj(1,1);

	//float x = (2.0f*theGlobalInput->mx()/w - 1.0f) / proj(0,0);
	//float y = -(2.0f*theGlobalInput->my()/h - 1.0f) / proj(1,1);

	D3DXVECTOR3 origin(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 direction(x, y, 1.0f);

	D3DXMATRIX inverseView;
	D3DXMatrixInverse(&inverseView, 0, &theCamera->view());

	D3DXVec3TransformCoord(&orig, &origin, &inverseView);
	D3DXVec3TransformNormal(&dir, &direction, &inverseView);
	D3DXVec3Normalize(&dir, &dir);
}

int PropMgr::GetIDFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{
	int id = -1;
	float distance = INFIN;

	for(PropMap::iterator it = m_propMap.begin();
		it != m_propMap.end(); ++it)
	{
		AABB box;
		it->second->GetBounds(box);
		if(D3DXBoxBoundProbe(&box.minPt, &box.maxPt, &orig, &dir))
		{
			D3DXMATRIX world = it->second->toWorld;
			float d = D3DXVec3Length(&(theCamera->pos() - D3DXVECTOR3(world._41, world._42, world._43)));
			
			if(d < distance)
			{
				distance = d;
				id = it->second->ID();
			}
		}
	}
	return id;
}

int PropMgr::GetIDFromRayIntersect(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{
	int id = -1;
	float distance = INFIN;
	ID3DXMesh* mesh;

	for(PropMap::iterator it = m_propMap.begin();
		it != m_propMap.end(); ++it)
	{
		AABB box;
		it->second->GetBounds(box);
		if(D3DXBoxBoundProbe(&box.minPt, &box.maxPt, &orig, &dir))
		{
			D3DXMATRIX inv = it->second->toWorld;
			D3DXMatrixInverse(&inv, NULL, &inv);

			D3DXVECTOR3 objOrig, objDir;

			D3DXVec3TransformCoord(&objOrig, &orig, &inv);
			D3DXVec3TransformNormal(&objDir, &dir, &inv);
			D3DXVec3Normalize(&objDir, &objDir);

			BOOL hit;
			float d;
			mesh = it->second->myModel->mesh;

			D3DXIntersect(mesh, &objOrig, &objDir, &hit, NULL, NULL, NULL, &d, NULL, NULL);
			if(hit)
			{
				if(d < distance)
				{
					distance = d;
					id = it->second->ID();
				}
			}
		}
	}
	return id;
}

Prop* PropMgr::GetPropFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{
	for(PropMap::iterator it = m_propMap.begin();
	it != m_propMap.end(); ++it)
	{
		AABB box;
		it->second->GetBounds(box);
		if(D3DXBoxBoundProbe(&box.minPt, &box.maxPt, &orig, &dir))
		{
			return it->second;
		}
	}
	return NULL;
}

D3DXVECTOR3 PropMgr::GetPosFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{	//doesn't actually do anything

	for(int i = -50; i < 50; i++)
	{
		for(int j = -50; j < 50; j++)
		{
			if(D3DXBoxBoundProbe(&D3DXVECTOR3((float)i, 0.0f, float(i)),
								 &D3DXVECTOR3((float)j, 0.0f, float(j)),
								 &orig, &dir))
			{
				return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Tile* PropMgr::GetTileFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir)
{
	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			AABB box;
			m_tileMap[i][j]->GetBounds(box);
			if(D3DXBoxBoundProbe(&box.minPt, &box.maxPt, &orig, &dir))
			{
				return m_tileMap[i][j];
			}
		}
	}
	return NULL;
}

void PropMgr::GetIDFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir, int &row, int &col)
{
	row = -1;
	col = -1;
	float distance = INFIN;

	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			AABB box;
			m_tileMap[i][j]->GetBounds(box);
			if(D3DXBoxBoundProbe(&box.minPt, &box.maxPt, &orig, &dir))
			{
				D3DXMATRIX world = MakeMatrix(TileToWorld(i, j), VEC3_ZERO, VEC3_ZERO);
				float d = D3DXVec3Length(&(theCamera->pos() - D3DXVECTOR3(world._41, world._42, world._43)));

				if(d < distance)
				{
					distance = d;
					row = i;
					col = j;
				}
			}
		}
	}
}


//stuff for the tile map

void PropMgr::BuildTileMap(int maxrow, int maxcol)
{
	if(!theTileModel->isLoaded)
		theTileModel->load(theDevice);

	m_maxRows = maxrow;
	m_maxCols = maxcol;

	//resize the map to the size requested
	m_tileMap.resize(maxrow); //height
	for(int i = 0; i < maxrow; i++)
	{
		m_tileMap[i].resize(maxcol); //width
	}



	//set the base layer while initializing tile map
	for(int i = 0; i < maxrow; i++)
	{
		for(int j = 0; j < maxcol; j++)
		{
			Tile* t = new Tile();
			t->row = i;
			t->col = j;
			t->position = D3DXVECTOR3(((float)i - maxrow/2.0f)*128.0f,
								0.0f, ((float)j - maxcol/2.0f)*128.0f);

			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, t->position.x,
						t->position.y, t->position.z);
			
			t->myMap.push_back(Tile::WorldTex(T, default_tex));

			m_tileMap[i][j] = t;
		}
	}
}

void PropMgr::BuildTileMap(int maxrow, int maxcol, IDirect3DTexture9* baseTex)
{
	m_maxRows = maxrow;
	m_maxCols = maxcol;

	//resize the map to the size requested
	m_tileMap.resize(maxrow); //height
	for(int i = 0; i < maxrow; i++)
	{
		m_tileMap[i].resize(maxcol); //width
	}



	//set the base layer while initializing tile map
	for(int i = 0; i < maxrow; i++)
	{
		for(int j = 0; j < maxcol; j++)
		{
			Tile* t = new Tile();
			t->row = i;
			t->col = j;
			t->position = D3DXVECTOR3(((float)i - maxrow/2.0f)*128.0f,
								0.0f, ((float)j - maxcol/2.0f)*128.0f);

			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, t->position.x,
						t->position.y, t->position.z);
			
			t->myMap.push_back(Tile::WorldTex(T, baseTex));

			m_tileMap[i][j] = t;
		}
	}
}

void PropMgr::UnloadTileMap()
{
	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			delete m_tileMap[i][j];
		}
		m_tileMap[i].clear();
	}

	m_tileMap.clear();
}

void PropMgr::DrawTiles()
{
	theDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	theDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	theDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	theDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	for(int i = 0; i < m_maxRows; i++)
	{
		for(int j = 0; j < m_maxCols; j++)
		{
			DrawTile(m_tileMap[i][j]);
		}
	}
	theDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	theDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void PropMgr::DrawTile(Tile *t)
{
	for(Tile::WTMap::iterator it = t->myMap.begin();
		it != t->myMap.end(); ++it)
	{
		m_tileFX->SetMatrix("gWVP", it->world * theCamera->viewProj());
		m_tileFX->SetMatrix("gWorld", it->world);

		m_tileFX->Begin(0);
		for(UINT i = 0; i < m_tileFX->GetNumPasses(); i++)
		{
			m_tileFX->BeginPass(i);

			m_tileFX->SetTexture("gTex", it->tex);
			m_tileFX->CommitChanges();
			t->myModel->mesh->DrawSubset(0);

			m_tileFX->EndPass();
		}
		m_tileFX->End();
	}
}

void PropMgr::SetDefaultFX(CShader* defaultFX)
{
	m_defaultFX = defaultFX;
}

CShader* PropMgr::GetDefaultFX()
{
	return m_defaultFX;
}

void PropMgr::SetSelectFX(CShader *selectFX)
{
	m_selectFX = selectFX;
}

CShader* PropMgr::GetSelectFX()
{
	return m_selectFX;
}

void PropMgr::SetTileFX(CShader *tileFX)
{
	m_tileFX = tileFX;
}

CShader* PropMgr::GetTileFX()
{
	return m_tileFX;
}

void PropMgr::SetLightPos(D3DXVECTOR3 light)
{
	m_lightPos = light;
}

D3DXVECTOR3 PropMgr::GetLightPos()
{
	return m_lightPos;
}

int PropMgr::GetNumProps()
{
	return m_propMap.size();
}