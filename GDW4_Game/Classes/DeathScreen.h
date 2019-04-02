#pragma once
#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H

#include "cocos2d.h"

using namespace cocos2d;

class DeathScreen : public cocos2d::Scene
{
public:
	enum MenuOptions
	{
		nothing,
		tryAgain,
		mainMenu,
		exit
	};

	CREATE_FUNC(DeathScreen);
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

	Sprite* background;
	Sprite* textOverlay;

	Sprite* tryAgainText;
	Sprite* mainMenuText;
	Sprite* exitText;

	Rect tryAgainRect;
	Rect mainMenuRect;
	Rect exitRect;

	bool isTransitioning;
};
#endif