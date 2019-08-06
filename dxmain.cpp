#include "dxApp.h"
#include "dxInput.h"
#include <tchar.h>
#include "appStats.h"
#include <strsafe.h>
#include "dxCamera.h"
#include "dxVertex.h"
#include "dxUtil.h"

#include "CShader.h"

#include "ui/uiManager.h"

//the only header needed for main...
#include "prop_mgr.h"

class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance,
		std::string winCaption,
		D3DDEVTYPE devType,
		DWORD requestedVP);
	~Game();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();
	void buildEffects();

	LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	//AppStats* theStats;
	GuiMgr* theGui;
	MouseResource theMouse;
};


//win main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   LPSTR lpCmdLine, int showCmd)
{
	Camera cam;
	theCamera = &cam;

	Game app(hInstance, "dmonty", D3DDEVTYPE_HAL,
			 D3DCREATE_HARDWARE_VERTEXPROCESSING);
	theApp = &app;

	DirectInput di(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
				   DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	theGlobalInput = &di;

	return theApp->run();
}

Game::Game(HINSTANCE hInstance, std::string winCaption,
		   D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	if(!checkDeviceCaps())
	{
		MessageBox(0,"checkDeviceCaps() - FAILED",0,0);
		PostQuitMessage(0);
	}
	InitVertexDeclarations();

	//theStats = new AppStats();

	theCamera->setCamera(1);
	theCamera->setFree(false);
	theCamera->setSpeed(500.0f);	

	theGui = new GuiMgr();
	theGui->Initialize(gDevice, &theMouse, NULL);

	thePropMgr->Initialize(gDevice);
	thePropMgr->BuildTileMap(30, 30);

	onResetDevice();
}

Game::~Game()
{
	delete theGui;
	DestroyVertexDeclarations();
}

bool Game::checkDeviceCaps()
{
	D3DCAPS9 caps;
	gDevice->GetDeviceCaps(&caps);

	if(caps.VertexShaderVersion < D3DVS_VERSION(2, 0))
		return false;
	if(caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
		return false;

	return true;
}

void Game::onLostDevice()
{
	//theStats->onLostDevice();
	theGui->OnLost();
}

void Game::onResetDevice()
{
	//theStats->onResetDevice();
	theGui->OnReset();
	
	float w = (float)theD3DPP.BackBufferWidth;
	float h = (float)theD3DPP.BackBufferHeight;
	theCamera->setLens(D3DX_PI * 0.25f, w/h, 1.0f, 1000.0f);
}

void Game::updateScene(float dt)
{	
	theGlobalInput->poll();
	theCamera->update(dt);
	//theStats->update(dt);

	theGui->Update(dt);

	theMouse.m_absoluteXY.x = theGlobalInput->mx();
	theMouse.m_absoluteXY.y = theGlobalInput->my();
}

void Game::drawScene()
{
	gDevice->Clear(0, 0,
					 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					 BLACK,1.0f, 0);
	gDevice->BeginScene();
	//.....start draw......//
	thePropMgr->Draw();
	
	theGui->Draw();
	//......end draw.......//
	//theStats->display();
	gDevice->EndScene();
	gDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::buildEffects()
{
}

LRESULT Game::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
static bool isMinOrMax = false;

	RECT clientRect = {0,0,0,0};
	switch(msg)
	{
	case WM_LBUTTONUP:
		theGui->SendToGui(GCMT_LBUTTONUP, NULL);
		return 0;

	case WM_LBUTTONDOWN:
		theGui->SendToGui(GCMT_LBUTTONDOWN, NULL);
		return 0;

	case WM_MOUSEMOVE:
		theGui->SendToGui(GCMT_MOUSEMOVE, NULL);
		return 0;

	case WM_KEYDOWN:
		//theCamera->
		return 0;

	case WM_KEYUP:
		return 0;

	case WM_ACTIVATE: //sent when the window is activated or deactivated
		if(LOWORD(wParam) == WA_INACTIVE)
			isPaused = true;
		else
			isPaused = false;
		return 0;

	case WM_SIZE: //sent when user resizes window
		if(gDevice)
		{
			theD3DPP.BackBufferWidth = LOWORD(lParam);
			theD3DPP.BackBufferHeight = HIWORD(lParam);

			if(wParam == SIZE_MINIMIZED)
			{
				isPaused = true;
				isMinOrMax = true;
			}
			else if(wParam == SIZE_MAXIMIZED)
			{
				isPaused = false;
				isMinOrMax = true;
				onLostDevice();
				gDevice->Reset(&theD3DPP);
				onResetDevice();
			}
			else if(wParam == SIZE_RESTORED)
			{
				isPaused = false;

				//only if not restoring to fullscreen
				if(isMinOrMax && theD3DPP.Windowed)
				{
					onLostDevice();
					gDevice->Reset(&theD3DPP);
					onResetDevice();
				}
				isMinOrMax = false;
			}
		}
		return 0;

	case WM_EXITSIZEMOVE: //when user is done resizing
		GetClientRect(theMainWindow, &clientRect);
		theD3DPP.BackBufferWidth = clientRect.right;
		theD3DPP.BackBufferHeight = clientRect.bottom;
		onLostDevice();
		gDevice->Reset(&theD3DPP);
		onResetDevice();

		return 0;

	case WM_CLOSE:
		DestroyWindow(theMainWindow);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}//end switch
	return DefWindowProc(theMainWindow, msg, wParam, lParam);
}