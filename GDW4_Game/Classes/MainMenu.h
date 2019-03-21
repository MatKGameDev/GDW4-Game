#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h";

using namespace cocos2d;

class MainMenu : public cocos2d::Scene
{
public:
	CREATE_FUNC(MainMenu);
	static Scene* createScene();

	bool init();
	void initUI();
	void initAnimations();
	void update(float dt);

private:
	Director* director;

	Sprite* background;

	bool isDone;
};
#endif