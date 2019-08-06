#include "dxUtil.h"
#include "dxInput.h"
#include "dxApp.h"

DirectInput* theGlobalInput = 0;

DirectInput::DirectInput(DWORD keyboardFlags, DWORD mouseFlags)
{
	ZeroMemory(&theKeyboardState, sizeof(theKeyboardState));
	ZeroMemory(&theMouseState, sizeof(theMouseState));

	DirectInput8Create(theApp->getAppInstance(),
						DIRECTINPUT_VERSION,
						IID_IDirectInput8,
						(void**)&theInput, 0);
	
	//create keyboard device
	theInput->CreateDevice(GUID_SysKeyboard, &theKeyboard, 0);
	theKeyboard->SetDataFormat(&c_dfDIKeyboard);
	theKeyboard->SetCooperativeLevel(theApp->getMainWindow(), keyboardFlags);
	theKeyboard->Acquire();
	//create mouse device
	theInput->CreateDevice(GUID_SysMouse, &theMouse, 0);
	theMouse->SetDataFormat(&c_dfDIMouse2);
	theMouse->SetCooperativeLevel(theApp->getMainWindow(), mouseFlags);
	theMouse->Acquire();
	
	iskey = true;
}

DirectInput::~DirectInput()
{
	ReleaseCOM(theInput);

	theKeyboard->Unacquire();
	ReleaseCOM(theKeyboard);
	theMouse->Unacquire();
	ReleaseCOM(theMouse);
}

void DirectInput::poll()
{
	//check keyboard..
	HRESULT hr = theKeyboard->GetDeviceState(sizeof(theKeyboardState),
											(void**)&theKeyboardState);
	if(FAILED(hr))
	{
		//zero out keyboard memory
		ZeroMemory(theKeyboardState, sizeof(theKeyboardState));
		//try for next time
		hr = theKeyboard->Acquire();
	}

	//check mouse..
	hr = theMouse->GetDeviceState(sizeof(DIMOUSESTATE2),
								  (void**)&theMouseState);
	if(FAILED(hr))
	{
		//zero our mouse memory
		ZeroMemory(&theMouseState, sizeof(theMouseState));
		//try to acquire for next time
		hr = theMouse->Acquire();
	}
	
	//float w = (float)theD3DPP.BackBufferWidth;
	//float h = (float)theD3DPP.BackBufferHeight;

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(theApp->getMainWindow(), &p);
	mouseX = (float)p.x;
	mouseY = (float)p.y;
}
float DirectInput::mx()
{
	return mouseX;
}

float DirectInput::my()
{
	return mouseY;
}

bool DirectInput::keyDown(char key)
{ 
	return (theKeyboardState[key] & 0x80) != 0;
}

bool DirectInput::keyUp(char key)
{
	return (theKeyboardState[key] & 0x80) == 0;
}

bool DirectInput::getR(){return iskey;}

bool DirectInput::mouseButtonDown(int button)
{
	return (theMouseState.rgbButtons[button] & 0x80) !=0;
}

float DirectInput::mouse_x()
{
	return (float)theMouseState.lX;
}

float DirectInput::mouse_y()
{
	return (float)theMouseState.lY;
}
float DirectInput::mouse_z()
{
	return (float)theMouseState.lZ;
}
