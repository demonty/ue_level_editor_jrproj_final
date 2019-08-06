#ifndef PROP_MGR_H
#define PROP_MGR_H

#include <d3dx9.h>
#include "dxUtil.h"
#include "prop.h"


//the prop manager is a singleton
#define thePropMgr PropMgr::Instance()

class CShader;

class PropMgr
{
private: //private methods
	PropMgr(){}
	PropMgr(const PropMgr&);
	PropMgr* operator=(PropMgr&);

	void LoadTextures();
	void UnloadTextures();

	bool SetUniqueFXVariables(Prop* prop, CShader* fx);

	Model* GetPropModel(PropType type);
	IDirect3DTexture9* PropMgr::GetTileTex(TileType type);

	//typedefs
	typedef std::multimap<int, Prop*> PropMap;
	typedef std::multimap<int, CShader*> FXMap;
	typedef std::map<TileType, IDirect3DTexture9*> TexMap;
	typedef std::map<IDirect3DTexture9*, TileType> RevTexMap;
	typedef std::map<std::string, PropType> PTMap;
	typedef std::map<std::string, TileType> TTMap;
	typedef std::vector<std::vector<Tile*>>  TileMap; //[rows][columns]
	
	//private members
	CShader* m_defaultFX;
	CShader* m_selectFX;
	CShader* m_tileFX;

	PropMap	  m_propMap;
	FXMap	  m_fxMap;
	TileMap	  m_tileMap;
	TexMap    m_texMap;

	RevTexMap m_revTexMap;
	PTMap m_propTypeMap;
	TTMap m_tileTypeMap;
	
	int m_maxRows;
	int m_maxCols;
	
	D3DXVECTOR3 m_lightPos;

	IDirect3DTexture9* default_tex;
	IDirect3DTexture9* select_tex;
	IDirect3DTexture9* zbase_tex;
	IDirect3DTexture9* graveyard_tex;

	LPDIRECT3DDEVICE9 theDevice;

	int m_NextID;

public: //public methods
	~PropMgr();
	static PropMgr* Instance();

	void Initialize(LPDIRECT3DDEVICE9 device);

	FXMap*     GetFXMap();	   // returns pointer to the fx map: map<int(id), CShader*>
	TexMap*	   GetTexMap();    // returns pointer to the texture map: map<TileType, IDirect3DTexture9*>
	RevTexMap* GetRevTexMap(); // returns pointer to the reverse texture map: map<IDirect3DTexture9*, TileType>
	PropMap*   GetPropMap(){return &m_propMap;}   // returns pointer to the prop map: <int(id), Prop*>

	//========================
	// prop specific methods
	//

	int GetNumProps(); // returns current number of props
	
	Prop*    GetProp(int id); // returns pointer to a prop
	AABB	 GetAABB(int id); // returns the aabb for a prop
	AABB     GetUTAABB(int id); // returns the untransformed aabb
	CShader* GetFX(int id);	  // returns pointer to the shader being used by this id
	int		 GetMaxRows();
	int      GetMaxCols();

	void ChangePropFX(int id, CShader &fx);  // change the fx applied to this prop
	void ChangePropFX(Prop* p, CShader &fx); // change the fx applied to this prop

	D3DXMATRIX* GetPropWorld(int id);  // returns the world matrix for this prop
	D3DXMATRIX* GetPropWorld(Prop* p); // returns the world matrix for this prop

	int  GetNextID(){return m_NextID;}
	int  GetLastID(){return m_NextID - 1;}

	void AddProp(int id, PropType type, D3DXVECTOR3 position, CShader &fx);
	void AddProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, CShader &fx);
	void AddMyProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 XYZrotation, CShader &fx); // order is m = x*y*z
	void AddProp(int id, PropType type, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 rotationVec, float rotationAmt, CShader &fx);// order is m = x*y*z
	void AddProp(int id, PropType type, D3DXMATRIX toWorld, CShader &fx); //this one is dangerous, the prop will be left without position/rotation/scale knowledge
	void RemoveProp(int id);  // remove this prop from manager by id
	void RemoveProp(Prop* p); // remove this prop from manager
	void RemoveAllProps();    // clears the manager of all props

	void TransformProp(int id, D3DXMATRIX toWorld);   // replaces prop's world matrix with this one
	void TransformProp(Prop* p, D3DXMATRIX toWorld);  // replaces prop's world matrix with this one
	void RotateProp(int id, float angle);			  // rotates prop about y-axis, recalculates world matrix
	void TranslateProp(int id, D3DXVECTOR3 position); // give a new position for a prop

	D3DXMATRIX MakeMatrix(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 rotation);
	
	void DrawProp(Prop* prop); // draws this prop

	D3DXVECTOR3 TileToWorld(int row, int col);	  // returns the world position for a given tile row and column

	//========================
	// tile specific methods
	//

	void AddTile(int row, int col,  D3DXMATRIX toWorld, TileType type); // scale, rotate, offset, whatever
	void AddTile(int row, int col, float rot, TileType type); // add with rotation
	void AddTile(int row, int col, TileType type); // standard add tile
	void RemoveTile(int row, int col, TileType type); //removes the last tile of this type
	void RemoveAllTilesTyped(TileType type); // removes all tiles of this type
	void RemoveLastTile(int row, int col); // removes the last texture added to this position
	void SetBaseTile(TileType type); // sets this type as the base for entire tile map
	void RotateLastTile(int row, int col, float rot); // rotates the topmost tile
	void RemoveAllThisTile(int row, int col); // remove every texture from this tile position

	void BuildTileMap(int maxrow, int maxcol); // sets base to default_tex
	void BuildTileMap(int maxrow, int maxcol, IDirect3DTexture9* baseTex); // baseTex will be the bottom texture for entire map
	void UnloadTileMap(); // clears theTileMap of all tiles
	void DrawTiles(); // draws all tiles in theTileMap
	void DrawTile(Tile* t); // draws the given tile
	
	void Draw(); // draws all tiles and props currently in prop manager

	void		SetDefaultFX(CShader* defaultFX); // sets the default shader to be used
	CShader*	GetDefaultFX();
	void		SetSelectFX(CShader* selectFX); //  sets the shader for selected objects
	CShader*	GetSelectFX();
	void		SetTileFX(CShader* tileFX); // sets the shader to be used on all tiles
	CShader*	GetTileFX();

	void		SetLightPos(D3DXVECTOR3 light); // set the light position for shader/drawing info
	D3DXVECTOR3 GetLightPos();

	void		GetRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir); // simple raycast for level editor
	int			GetIDFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir); // returns the prop id for given ray
	int			GetIDFromRayIntersect(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir);
	Prop*		GetPropFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir); // returns prop pointer for given ray
	D3DXVECTOR3 GetPosFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir);  // doesn't do anything yet...
	Tile*		GetTileFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir); // returns tile pointer for given ray
	void		GetIDFromRay(D3DXVECTOR3 &orig, D3DXVECTOR3 &dir, int &row, int &col); // fills in row/col for given ray
};

#endif