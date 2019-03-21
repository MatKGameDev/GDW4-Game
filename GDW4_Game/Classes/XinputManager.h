#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <cmath>

#pragma comment(lib,"Xinput.lib")

//Buttons used for the controllers
enum CONTROLLER_INPUT_BUTTONS
{
	DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
	DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	THUMB_LEFT = XINPUT_GAMEPAD_LEFT_THUMB,
	THUMB_RIGHT = XINPUT_GAMEPAD_RIGHT_THUMB,
	SELECT = XINPUT_GAMEPAD_BACK,
	START = XINPUT_GAMEPAD_START
};

enum STICK_NAMES
{
	LS,
	RS
};

enum TRIGGER_NAMES
{
	LT,
	RT
};

//The X & Y input of the controller given as a float value from -1 -> 1 
struct Stick
{
	float x, y;
};

//The left and right trigger values that are  given as a float value from 0 -> 1
struct Triggers
{
	float LT, RT;
};

class XinputController
{
public:
	//...
	void setControllerIndex(int index)
	{
		this->index = index;
	}

	void update()
	{
		if (index >= 0 && index < 4)
			XInputGetState(index, &info);
	}

	void deadZoneSticks(float dz)
	{
		deadZoneStick = dz;
	}

	void deadZoneTriggers(float dz)
	{
		deadZoneTrigger = dz;
	}

	bool isButtonPressed(int button)
	{
		return button & info.Gamepad.wButtons;
	}

	bool isButtonReleased(int button)
	{
		return !isButtonPressed(button);
	}

	void getSticks(Stick sticks[2])
	{
		//left stick
		float x = (float)info.Gamepad.sThumbLX / 32768;
		float y = (float)info.Gamepad.sThumbLY / 32768;

		if (sqrt(x*x + y*y) > deadZoneStick)
		{
			if (info.Gamepad.sThumbLX < 0)
				sticks[0].x = (float)info.Gamepad.sThumbLX / 32768; //convert to a float from -1 -> 1
			else
				sticks[0].x = (float)info.Gamepad.sThumbLX / 32767; //convert to a float from -1 -> 1

			if (info.Gamepad.sThumbLY < 0)
				sticks[0].y = (float)info.Gamepad.sThumbLY / 32768; //convert to a float from -1 -> 1
			else
				sticks[0].y = (float)info.Gamepad.sThumbLY / 32767; //convert to a float from -1 -> 1
		}
		else
			sticks[0] = { 0,0 };

		//right stick

		x = (float)info.Gamepad.sThumbRX / 32768;
		y = (float)info.Gamepad.sThumbRY / 32768;

		if (sqrt(x*x + y*y) > deadZoneStick)
		{
			if (info.Gamepad.sThumbRX < 0)
				sticks[1].x = (float)info.Gamepad.sThumbRX / 32768; //convert to a float from -1 -> 1
			else
				sticks[1].x = (float)info.Gamepad.sThumbRX / 32767; //convert to a float from -1 -> 1

			if (info.Gamepad.sThumbRY < 0)
				sticks[1].y = (float)info.Gamepad.sThumbRY / 32768; //convert to a float from -1 -> 1
			else
				sticks[1].y = (float)info.Gamepad.sThumbRY / 32767; //convert to a float from -1 -> 1
		}
		else
			sticks[1] = { 0,0 };
	}

	void getTriggers(Triggers &triggers)
	{
		float l = (float)info.Gamepad.bLeftTrigger / 255;
		float r = (float)info.Gamepad.bRightTrigger / 255;
		triggers = Triggers{ l<deadZoneTrigger ? 0 : l , r < deadZoneTrigger ? 0 : r};
	}

private:
	//...
	int index = -1;
	XINPUT_STATE info;
	float deadZoneStick;
	float deadZoneTrigger;
};

class XinputManager
{
public:
	 //...
	bool create();
	static XinputManager* instance;

	static bool controllerConnected(int index);
	static XinputController* getController(int index);

	static void update();

private:
	//...
	XinputManager();
	static XinputController controllers[4];
};