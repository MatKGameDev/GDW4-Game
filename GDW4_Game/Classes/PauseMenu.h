#pragma once
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "cocos2d.h"
#include "ControllerInput.h"

using namespace cocos2d;

class PauseMenu : public cocos2d::Scene
{
public:
	enum MenuOptions
	{
		nothing,
		resume,
		controls,
		exit
	};

	CREATE_FUNC(PauseMenu);
	static Scene* createScene();

	bool init();
	void initUI();
	void initAnimations();

	void initMouseListener();
	void initControllerListener();

	void moveToNextMenuItem();
	void moveToPreviousMenuItem();

	void update(float dt);

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);

	//controller callbacks
	void buttonPressCallback(Controller* controller, int keyCode, Event* event);
	void buttonReleaseCallback(Controller* controller, int keyCode, Event* event);
	void axisEventCallback(Controller* controller, int keyCode, Event* event);
private:
	MenuOptions currentSelection;

	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerController* controllerListener;

	Vec2 cursorPos;

	Sprite* resumeText;
	Sprite* controlsText;
	Sprite* exitText;

	Rect resumeRect;
	Rect controlsRect;
	Rect exitRect;
};
#endif