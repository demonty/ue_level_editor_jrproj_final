#include "dxApp.h"

D3DApp* theApp = 0;
IDirect3DDevice9* gDevice = 0;

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//don't process until app has been created
	if(theApp != 0)
		return theApp->msgProc(msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance, std::string winCaption,
			   D3DDEVTYPE devType, DWORD requestedVP)
{
	theWindowCaption = winCaption;
	theDevType = devType;
	theRequestedVP = requestedVP;
	theAppInstance = hInstance;
	theMainWindow = 0;
	theD3DObject = 0;
	isPaused = false;
	ZeroMemory(&theD3DPP, sizeof(theD3DPP));

	initMainWindow();
	initDirect3D();
}

D3DApp::~D3DApp()
{
	ReleaseCOM(theD3DObject);
	ReleaseCOM(gDevice);
}

HINSTANCE D3DApp::getAppInstance()
{
	return theAppInstance;
}

HWND D3DApp::getMainWindow()
{
	return theMainWindow;
}

void D3DApp::initMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = theAppInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "D3DWndClassName";

	if(!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass - FAILED",0,0);
		PostQuitMessage(0);
	}

	//default to 800x600 window
	RECT R = {0,0,1280,800};
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	theMainWindow = CreateWindow("D3DWndClassName",
								theWindowCaption.c_str(),
								WS_OVERLAPPEDWINDOW,
								100, 100,
								R.right,
								R.bottom,
								0, 0,
								theAppInstance,
								0);
	if(!theMainWindow)
	{
		MessageBox(0, "CreateWindow - FAILED",0,0);
		PostQuitMessage(0);
	}

	ShowWindow(theMainWindow, SW_SHOW);
	UpdateWindow(theMainWindow);
}

void D3DApp::initDirect3D()
{
	//step1 - create the IDirect3D9 object..
	theD3DObject = Direct3DCreate9(D3D_SDK_VERSION);
	if(!theD3DObject)
	{
		MessageBox(0, "Direct3DCreate9 - FAILED",0,0);
		PostQuitMessage(0);
	}

	//step2 - verify hardware support
	D3DDISPLAYMODE mode;
	theD3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	theD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT,
								  theDevType,
								  mode.Format,
								  mode.Format,
								  true);
	theD3DObject->CheckDeviceType(D3DADAPTER_DEFAULT,
								  theDevType,
								  D3DFMT_X8R8G8B8,
								  D3DFMT_X8R8G8B8,
								  false);

	//step3 - check for required vertex processing & pure device
	D3DCAPS9 caps;
	theD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, theDevType, &caps);

	DWORD deviceFlags = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		deviceFlags |= theRequestedVP;
	else
		deviceFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//if pure device and HW T&L supported
	if(caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		deviceFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceFlags |= D3DCREATE_PUREDEVICE;
	}

	//step4 - fill out the D3DPRESENT_PARAMETERS struct

	theD3DPP.BackBufferWidth = 0;
	theD3DPP.BackBufferHeight = 0;
	theD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	theD3DPP.BackBufferCount = 1;
	theD3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	theD3DPP.MultiSampleQuality = 0;
	theD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	theD3DPP.hDeviceWindow = theMainWindow;
	theD3DPP.Windowed = true;
	theD3DPP.EnableAutoDepthStencil = true;
	theD3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	theD3DPP.Flags = 0;
	theD3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	theD3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//step5 - create the device..
	theD3DObject->CreateDevice(
				D3DADAPTER_DEFAULT, //primary adapter
				theDevType,			//device type
				theMainWindow,		//associated window
				deviceFlags,		//vertex processing
				&theD3DPP,			//present parameters
				&gDevice);		// return created device
}

int D3DApp::run()
{
	MSG msg;
	msg.message = WM_NULL;

	__int64 cntsPerSecond = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSecond);
	float secondsPerCnt = 1.0f / (float)cntsPerSecond;

	__int64 previousTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&previousTimeStamp);

	while(msg.message != WM_QUIT)
	{
		//process any window messages..
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //do game stuff..
		{
			//if paused, free up the CPU
			if(isPaused)
			{
				Sleep(20);
				continue;
			}

			if(!isDeviceLost())
			{
				__int64 currentTimeStamp = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currentTimeStamp);
				float dt = (currentTimeStamp - previousTimeStamp)*secondsPerCnt;

				updateScene(dt);
				drawScene();

				//set previous for next iteration
				previousTimeStamp = currentTimeStamp;
			}
		}
	}//end while
	return (int)msg.wParam;
}

LRESULT D3DApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool isMinOrMax = false;

	RECT clientRect = {0,0,0,0};
	switch(msg)
	{
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

void D3DApp::enableFullScreen(bool enable)
{
	if(enable)
	{
		if(!theD3DPP.Windowed)
			return;

		//int width = GetSystemMetrics(SM_CXFULLSCREEN);
		//int height = GetSystemMetrics(SM_CYFULLSCREEN);

		theD3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		theD3DPP.BackBufferWidth = 1280;
		theD3DPP.BackBufferHeight = 800;
		theD3DPP.Windowed = false;

		SetWindowLongPtr(theMainWindow, GWL_STYLE, WS_POPUP);
		SetWindowPos(theMainWindow, HWND_TOP,
					0, 0,
					1280,
					800,
					SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else //switch to windowed mode
	{
		if(theD3DPP.Windowed)
			return;

		RECT R = {0, 0, 1280, 800};
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		theD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
		theD3DPP.BackBufferWidth = 1280;
		theD3DPP.BackBufferHeight = 800;
		theD3DPP.Windowed = true;

		SetWindowLongPtr(theMainWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(theMainWindow,
					 HWND_TOP,
					 100,
					 100,
					 R.right,
					 R.bottom,
					 SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	onLostDevice();
	gDevice->Reset(&theD3DPP);
	onResetDevice();
}

bool D3DApp::isDeviceLost()
{
	HRESULT hr = gDevice->TestCooperativeLevel();

	if(hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if(hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, "Internal Driver Error.. Exiting", 0,0);
		PostQuitMessage(0);
		return true;
	}
	else if(hr == D3DERR_DEVICENOTRESET)
	{
		onLostDevice();
		gDevice->Reset(&theD3DPP);
		onResetDevice();
		return false;
	}
	else
		return false;
}