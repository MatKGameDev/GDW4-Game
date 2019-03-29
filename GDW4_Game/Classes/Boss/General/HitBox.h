#pragma once

#include "cocos2d.h"

class HitBox
{
	//Private data members
	float height, width;
	cocos2d::DrawNode *hitBoxShape;
	cocos2d::Scene *scene;
	
public:
	//Public data member
	cocos2d::Rect hitBox;

	//Constructors and Destructor
	HitBox(cocos2d::Scene* aScene, float aHeight, float aWidth);
	~HitBox();

	//Member functions
	void updateHitBox(const cocos2d::Vec2 &newPosition);

	//Setters
	void setNewSize(const float& newWidth, const float& newHeight);
};