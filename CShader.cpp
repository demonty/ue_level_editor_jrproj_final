#include "CShader.h"
#include <tchar.h>

// Loads the Effect file and creates all handles
CShader::CShader(char* filename, LPDIRECT3DDEVICE9 d3ddev)
{
	// Locate and open the file
	std::ifstream file;
	file.open(filename);
	if(file.bad())
	{
		SHOWERROR("Unable to locate .fx file.", __FILE__, __LINE__ );
		return;
	}

	// Load the FX file
	ID3DXBuffer* errors = 0;
	D3DXCreateEffectFromFile(d3ddev,filename,0,0,0,0,&m_pFX,&errors);
	if(errors)
	{
		SHOWERROR((char*)errors->GetBufferPointer(), __FILE__, __LINE__ );
		return;
	}

	// Start reading in line by line to check for externs
	char buffer[256];
	std::string word;
	while(!file.eof())
	{
		file.getline(buffer, 256);
		// Read in the first 'word'
		int i = 0;
		word = "";
		while(i < 256)
		{
			// If it is a space, return as we have our word
			if(buffer[i] == ' ')
				break;
			// Else, add it onto the end of our 'word'
			word += buffer[i];
			++i;
		}

		// Check if this is a 'uniform extern' line
		if(word.compare("uniform") == 0)
		{
			while(true)
			{
				// Now get the variable name and create a handle to it
				if(buffer[i] == 'g')
				{
					word = "";
					while(true)
					{
						if(buffer[i] == ';')
							break;
						word += buffer[i];
						++i;
					}
					
					HandleInfo h;
					h.name = word;
					h.handle = m_pFX->GetParameterByName(0, _T(word.c_str()));
					m_handles.push_back(h);
					break;
				}
				++i;
			}
		}
		// Check if this is a technique
		else if(word.compare("technique") == 0)
		{
			++i;
			word = "";
			// Create a handle to the name
			while(true)
			{
				if(buffer[i] == NULL)
					break;
				word += buffer[i];
				++i;
			}

			HandleInfo h;
			h.name = word;
			h.handle = m_pFX->GetTechniqueByName(word.c_str());
			m_handles.push_back(h);
		}
	}
	
	file.close();
}

// Releases the Effect and all handles
void CShader::Release()
{
	// Release effect and handles
	SAFE_RELEASE(m_pFX);
	m_handles.clear();
}

void CShader::OnLost()
{
	m_pFX->OnLostDevice();
}

void CShader::OnReset()
{
	m_pFX->OnResetDevice();
}

// Sets the matrix of a handle
void CShader::SetMatrix(std::string name, D3DXMATRIX mat)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetMatrix(m_handles[i].handle, &mat);
			return;
		}
	}
}

// Sets the texture of a handle
void CShader::SetTexture(std::string name, IDirect3DTexture9* tex)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetTexture(m_handles[i].handle, tex);
			return;
		}
	}
}

// Sets the technique to be used
void CShader::SetTechnique(std::string name)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetTechnique(m_handles[i].handle);
			return;
		}
	}
}

// Sets the value of a float
void CShader::SetFloat(std::string name, float val)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetFloat(name.c_str(), val);
			return;
		}
	}
}

// Sets the value of a float2
void CShader::SetFloat2(std::string name, D3DXVECTOR2 val)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetValue(m_handles[i].handle, val, sizeof(D3DXVECTOR2));
			return;
		}
	}
}

// Sets the value of a float3
void CShader::SetFloat3(std::string name, D3DXVECTOR3 val)
{
	// Locate the handle with the specified name
	for(UINT i = 0; i < m_handles.size(); ++i)
	{
		if(m_handles[i].name.compare(name) == 0)
		{
			m_pFX->SetValue(m_handles[i].handle, val, sizeof(D3DXVECTOR3));
			return;
		}
	}
}

// Commits changes made
void CShader::CommitChanges()
{
	m_pFX->CommitChanges();
}

// Begins the shader
void CShader::Begin(UINT numPasses)
{
	m_pFX->Begin(&numPasses, 0);
}

// Begins a pass
void CShader::BeginPass(UINT pass)
{
	m_pFX->BeginPass(pass);
}

// Ends a pass
void CShader::EndPass()
{
	m_pFX->EndPass();
}

// Ends the shader
void CShader::End()
{
	m_pFX->End();
}

// Sets the type
void CShader::SetType(FXType type)
{
	m_type = type;
}

// Returns the type
FXType CShader::GetType()
{
	return m_type;
}

// Sets the num passes
void CShader::SetNumPasses(UINT numPasses)
{
	m_numPasses = numPasses;
}

UINT CShader::GetNumPasses()
{
	return m_numPasses;
}