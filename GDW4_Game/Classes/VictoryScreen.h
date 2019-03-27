#pragma once
#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H

#include "cocos2d.h"

using namespace cocos2d;

class VictoryScreen : public cocos2d::Scene
{
public:
	CREATE_FUNC(VictoryScreen);
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

	Sprite* background;

	Sprite* mainMenuText;
	Sprite* exitText;

	Rect mainMenuRect;
	Rect exitRect;

	bool isTransitioning;
};
#endif