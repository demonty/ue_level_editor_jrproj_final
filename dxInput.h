#ifndef DXINPUT_H
#define DXINPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class DirectInput
{
private:
	IDirectInput8* theInput;
	IDirectInputDevice8* theKeyboard;
	char theKeyboardState[256];

	IDirectInputDevice8* theMouse;
	DIMOUSESTATE2 theMouseState;

	float mouseX;
	float mouseY;
	bool  iskey;

public:
	DirectInput(DWORD keyboardFlags, DWORD mouseFlags);
	~DirectInput();

	void poll();
	bool keyDown(char key);
	bool keyUp(char key);
	bool mouseButtonDown(int button);
	float mouse_x();
	float mouse_y();
	float mouse_z();
	float my();
	float mx();
	bool getR();

private:
	DirectInput(const DirectInput& did);
	DirectInput& operator=(const DirectInput& did);
};

extern DirectInput* theGlobalInput;

#endif //dxinput.h