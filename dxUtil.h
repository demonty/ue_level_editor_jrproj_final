#ifndef DXUTIL_H
#define DXUTIL_H

//#pragma warning (push, 4)
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxerr.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <tchar.h>
#include <fstream>

class D3DApp;
extern D3DApp* theApp;
extern IDirect3DDevice9* gDevice;
class Camera;
extern Camera* theCamera;

#define ReleaseCOM(x) {if(x){x->Release(); x=0;}}
#define SAFE_DELETE(x) {if(x){delete x; x=NULL;}}
#define SHOWERROR(s,f,l) char buf[1024]; sprintf_s(buf, "File : %s\nLine: %d\n\n%s",f,l,s); MessageBox(0,buf,"Error",0);
#define SAFE_RELEASE(x) {if(x){x->Release(); x=NULL;}}

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 0.5f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR GREY(0.6f, 0.6f, 0.6f, 1.0f);
const D3DXCOLOR DGREY(0.4f, 0.4f, 0.4f, 1.0f);
const D3DXCOLOR BROWN(0.514f, 0.278f, 0.0f, 1.0f);

const D3DXVECTOR3 XAXIS(1.0f, 0.0f, 0.0f);
const D3DXVECTOR3 YAXIS(0.0f, 1.0f, 0.0f); 
const D3DXVECTOR3 ZAXIS(0.0f, 0.0f, 1.0f);
const D3DXVECTOR3 VEC3_ZERO(0.0f, 0.0f, 0.0f);

enum PropType
{
	INVALID_PROP,

	PROP_AXIS,
	PROP_FENCE,
	PROP_CHAIN_FENCE,
	PROP_GATE,
	PROP_ROCK01,
	PROP_ROCK02,
	PROP_ROCK03,
	PROP_TOMBSTONE01,
	PROP_TOMBSTONE02,
	PROP_DESTROYED_WALL_01,
	PROP_PIPE_STRAIGHT,
	PROP_PIPE_ELBOW,
	PROP_PIPE_CROSS,
	
	BUILDING_SP_BASE,
	BUILDING_Z_BASE,
	BUILDING_COAL_MINE,
	BUILDING_GRAVEYARD,

	UNIT_SP_GROUND,
	UNIT_Z_GROUND,

	//BUILDING_UPGRAYEDD,
	//BUILDING_GUNIT,
};

enum TileType{DEFAULT, SELECT,};

enum FXType{DEFAULT_FX, TOON_FX, SELECT_FX};

enum GraphicsCoreMessageType
{
	//GCMT_DEFAULT = GRAPHICSCOREMSG_START,
	GCMT_LBUTTONDOWN,
	GCMT_LBUTTONUP,
	GCMT_MOUSEMOVE,
};

enum UserInterfaceMessageType
{
	// Menu Messages
	UIMT_NEW_GAME,
	UIMT_SAVE_GAME,
	UIMT_SAVE_WITH_NAV,
	UIMT_LOAD_GAME,
	UIMT_QUIT_GAME,
	UIMT_FULLSCREEN,
	UIMT_CLEAR_SCENE,

	UIMT_SET_AS_DLG,
	UIMT_CLOSE_SET_DLG,
	UIMT_SET_AS_SCALE,
	UIMT_SET_AS_ROT,
	
	UIMT_RESET_AMT,

	UIMT_UP_TOOL,
	UIMT_DOWN_TOOL,
	UIMT_LEFT_TOOL,
	UIMT_RIGHT_TOOL,
	UIMT_MOVE_TOOL,
	UIMT_SCALE_TOOL,
	UIMT_SCALE_UNIFORM,
	UIMT_ROTATE_TOOL,
	UIMT_XZ_AXIS,
	UIMT_XY_AXIS,
	UIMT_YZ_AXIS,
	UIMT_CHANGE_SPOT,
	UIMT_ADD_AMT,
	UIMT_REM_AMT,
	UIMT_CLR_AMT,

	UIMT_PICK_PROP,
	UIMT_PICK_TILE,
	UIMT_PICK_UNIT,

	UIMT_ADD_ASSET,
	UIMT_REMOVE_ASSET,

	UIMT_NEXT_ASSET,
	UIMT_PREV_ASSET,

	UIMT_ASSET_PROP,
	UIMT_ASSET_UNIT,
	UIMT_ASSET_RESOURCE,
	
	UIMT_CAM_NORMAL,
	UIMT_CAM_XY,
	UIMT_CAM_XZ,
	UIMT_CAM_YZ,
	UIMT_CAM_FLIP,

	UIMT_SHOW_TOOL,
	UIMT_HIDE_TOOL,

	//
	UIMT_NOTHING,
};

enum ToolType
{
	MOVE_TOOL,
	SCALE_TOOL,
	ROTATE_TOOL,

	PICK_PROP,
	PICK_TILE,
	PICK_UNIT,

	ASSET_PROP,
	ASSET_UNIT,
	ASSET_RESOURCE,
};

enum ManagerType
{
	M_PARENT,
	M_TOOLBAR,
	M_TOPMENU,
	M_UTILBAR,
	M_STATUSBAR,
};

struct MouseResource
{
public:
	// The absolute x and y position of the mouse on the screen.
	D3DXVECTOR2 m_absoluteXY;

	// The relative x and y position of the mouse on the screen, and z: the amount that the
	// mouse has scrolled since the last update.
	D3DXVECTOR3 m_relativeXYZ;
};


struct Mtrl
{
	Mtrl()
		:ambient(WHITE), diffuse(WHITE), spec(WHITE), specPower(8.0f)
	{
	}
	Mtrl(const D3DXCOLOR& a, const D3DXCOLOR& d, 
		 const D3DXCOLOR& s, float power)
		:ambient(a), diffuse(d), spec(s), specPower(power)
	{
	}

	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR spec;
	float specPower;
};



void LoadXFile(const std::string& filename,
			   ID3DXMesh** meshOut,
			   std::vector<Mtrl>& materials,
			   std::vector<IDirect3DTexture9*>& textures);

const float INFIN = FLT_MAX;
const float EPSILON  = 0.001f;

struct AABB 
{
	// Initialize to an infinitely small bounding box.
	AABB()
		: minPt(INFIN, INFIN, INFIN),
		  maxPt(-INFIN, -INFIN, -INFIN){}

    D3DXVECTOR3 center()const
	{
		return (minPt+maxPt)*0.5f;
	}

	D3DXVECTOR3 extent()const
	{
		return (maxPt-minPt)*0.5f;
	}

	void xform(const D3DXMATRIX& M, AABB& out)
	{
		// Convert to center/extent representation.
		D3DXVECTOR3 c = center();
		D3DXVECTOR3 e = extent();

		// Transform center in usual way.
		D3DXVec3TransformCoord(&c, &c, &M);

		// Transform extent.
		D3DXMATRIX absM;
		D3DXMatrixIdentity(&absM);
		absM(0,0) = fabsf(M(0,0)); absM(0,1) = fabsf(M(0,1)); absM(0,2) = fabsf(M(0,2));
		absM(1,0) = fabsf(M(1,0)); absM(1,1) = fabsf(M(1,1)); absM(1,2) = fabsf(M(1,2));
		absM(2,0) = fabsf(M(2,0)); absM(2,1) = fabsf(M(2,1)); absM(2,2) = fabsf(M(2,2));
		D3DXVec3TransformNormal(&e, &e, &absM);

		// Convert back to AABB representation.
		out.minPt = c - e;
		out.maxPt = c + e;
	}

	D3DXVECTOR3 minPt;
	D3DXVECTOR3 maxPt;
};

#endif //dxutil.h

