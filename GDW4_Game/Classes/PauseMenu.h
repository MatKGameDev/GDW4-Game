#pragma once
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "cocos2d.h"
using namespace cocos2d;

class PauseMenu : public cocos2d::Scene
{
public:
	CREATE_FUNC(PauseMenu);
	static Scene* createScene();

	bool init();
	void initUI();
	void initAnimations();
	void initMouseListener();

	void update(float dt);

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);

private:
	Director* director;
	EventListenerMouse* mouseListener;
	Vec2 cursorPos;

	Sprite* resumeText;
	Sprite* controlsText;
	Sprite* exitText;

	Rect resumeRect;
	Rect controlsRect;
	Rect exitRect;
};
#endif