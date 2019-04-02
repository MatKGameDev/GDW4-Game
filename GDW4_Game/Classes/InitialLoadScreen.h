#pragma once
#ifndef INITIALLOADSCENE_H
#define INITIALLOADSCENE_H

#include "cocos2d.h"
using namespace cocos2d;

class InitialLoadScreen : public cocos2d::Scene
{
public:
	CREATE_FUNC(InitialLoadScreen);
	static Scene* createScene();

	bool init();
	void preloadAnimations();
	void update(float dt);

private:
	Director* director;
	Sprite* image;

	bool isDone;
	float timer;
};
#endif