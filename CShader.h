#ifndef H_SHADER
#define H_SHADER

#include "dxUtil.h"
#include <fstream>

// --------------------------------------------------------------
// Name: Handle Information
// Desc: Provides information about a handle used for a vector
// --------------------------------------------------------------
struct HandleInfo
{
	std::string	name;
	D3DXHANDLE	handle;
};

// --------------------------------------------------------------------------
// Name: CShader
// Desc: A basic class for creation of shaders and managing of handles. The
//       constructor will read through the class and create the handles for
//       all externs and techniques.
// --------------------------------------------------------------------------
class CShader
{
public:
	// Loads the Effect file and creates all handles
	CShader(char* filename, LPDIRECT3DDEVICE9 d3ddev);
	// Calls the Release method
	~CShader(){Release();}

	void OnLost();
	void OnReset();
	// Releases the Effect and all handles
	void Release();

	// Sets the matrix of a handle
	void SetMatrix(std::string name, D3DXMATRIX mat);
	// Sets the texture of a handle
	void SetTexture(std::string name, IDirect3DTexture9* tex);
	// Sets the technique to be used
	void SetTechnique(std::string name);
	// Sets the value of a float
	void SetFloat(std::string name, float val);
	// Sets the value of a float2
	void SetFloat2(std::string name, D3DXVECTOR2 val);
	// Sets the value of a float3
	void SetFloat3(std::string name, D3DXVECTOR3 val);
	// Commits changes made
	void CommitChanges();

	// Begins the shader
	void Begin(UINT numPasses);
	// Begins a pass
	void BeginPass(UINT pass);
	// Ends a pass
	void EndPass();
	// Ends the shader
	void End();

	// Sets the type for the effect
	void SetType(FXType type);
	// Returns the type for the effect
	FXType GetType();
	// Sets the number of passes needed for this effect
	void SetNumPasses(UINT numPasses);
	// Returns the number of passes needed
	UINT GetNumPasses();
	
private:
	// Main ID3DXEffect pointer
	ID3DXEffect*			m_pFX;
	// Vector of all handles created
	std::vector<HandleInfo>	m_handles;
	// Type associated with this effect
	FXType					m_type;
	// Number of passes this effect needs
	UINT					m_numPasses;
};

#endif