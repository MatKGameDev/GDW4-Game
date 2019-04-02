#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h";
#include "ControllerInput.h"

using namespace cocos2d;

class MainMenu : public cocos2d::Scene
{
public:
	enum MenuOptions
	{
		nothing,
		start,
		controls,
		exit
	};

	CREATE_FUNC(MainMenu);
	static Scene* createScene();

	bool init();
	void initUI();
	void initAnimations();
	void initMusic();

	void initMouseListener();
	void initControllerListener();

	void moveToNextMenuItem();
	void moveToPreviousMenuItem();

	void update(float dt);
	void transitionScene();

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

	Sprite* Logo;

	Sprite* startText;
	Sprite* controlsText;
	Sprite* exitText;

	Rect startRect;
	Rect controlsRect;
	Rect exitRect;

	bool isTransitioning;
};
#endif