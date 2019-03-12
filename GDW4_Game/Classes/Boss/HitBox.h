#pragma once
#include "cocos2d.h"


class HitBox
{
	float height, width;
	cocos2d::DrawNode *hitBoxShape;
	cocos2d::Scene *scene;
public:
	//Member functions
	cocos2d::Rect hitBox;

	HitBox(cocos2d::Scene* aScene, float aHeight, float aWidth);
	~HitBox();
	void updateHitBox(const cocos2d::Vec2 &newPosition);
};

