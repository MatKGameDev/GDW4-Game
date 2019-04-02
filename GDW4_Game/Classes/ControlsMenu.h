#pragma once
#ifndef CONTROLSMENU_H
#define CONTROLSMENU_H

#include "cocos2d.h"
#include "ControllerInput.h"

using namespace cocos2d;

class ControlsMenu : public cocos2d::Scene
{
public:
	CREATE_FUNC(ControlsMenu);
	static Scene* createScene();

	bool init();
	void initUI();
	void initAnimations();
	void initMusic();

	void initMouseListener();
	void initControllerListener();

	void update(float dt);

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);

	//controller callbacks
	void buttonPressCallback(Controller* controller, int keyCode, Event* event);

private:
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerController* controllerListener;

	Vec2 cursorPos;

	Sprite* controlsList;

	Sprite* backText;

	Rect backRect;
};
#endif