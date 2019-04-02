#pragma once
#include "cocos2d.h"
class HudObject
{
	public:

	HudObject(std::string filePath, cocos2d::Vec2 position);
	~HudObject();
	
	cocos2d::Sprite* sprite;
	
	static std::vector<HudObject*> HudList;

	static void deleteAllInstances();
	
	void update(float dt);

};

