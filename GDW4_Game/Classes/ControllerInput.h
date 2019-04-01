#pragma once
#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

//I had to make this class because cocos controller key processing SUCKS and controller keycodes being passed around are way different from their enums

class ControllerInput
{
public:
	enum Buttons
	{
		A,
		B,
		X,
		Y,
		LeftBumper,
		RightBumper,
		Back,
		Start,
		LeftAnalogPress,
		RightAnalogPress,
		DPadUp,
		DPadRight,
		DPadDown,
		DPadLeft,
		A_Release,
		B_Release,
		X_Release,
		Y_Release,
		LeftBumper_Release,
		RightBumper_Release,
		Back_Release,
		Start_Release,
		LeftAnalog_Release,
		RightAnalog_Release,
		DPadUp_Release,
		DPadDown_Release,
		DPadLeft_Release
	};

	enum Axis
	{
		leftStickX,
		leftStickY,
		rightStickX,
		rightStickY,
		leftTrigger,
		rightTrigger
	};

	static bool isLeftTriggerReset;
	static bool isRightTriggerReset;
	static bool isLeftStickReset;

	static bool isLeftStickIdle;

	static bool isControllerUsed;
};
#endif