#pragma once
#ifndef PRETTYPICTURESCENE_H
#define PRETTYPICTURESCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class PrettyPictureScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(PrettyPictureScene);
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